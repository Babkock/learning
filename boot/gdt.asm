; This is 5 files put together
; Enter 32-bit protected mode and print string
; in video memory
; Compile with:
;    nasm gdt.asm -f bin -o gdt.bin
; Run with:
;    qemu-system-i386 -hda gdt.bin
[org 0x7c00]
	mov bp, STACK	; set the stack
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print

	call switch_pm	; switch to protected mode
	jmp $

print:
	pusha

start:
	mov al, [bx]	; BX <- base address of string
	cmp al, 0
	je done

	mov ah, 0x0e	; print with BIOS interrupt
	int 0x10		; AL contains the char
	
	add bx, 1		; increment pointer and continue
	jmp start

done:
	popa
	ret

print_nl:
	pusha
	mov ah, 0x0e
	mov al, 0x0a	; newline character
	int 0x10
	mov al, 0x0d	; carriage return
	int 0x10

	popa
	ret

; include this file from somewhere else
gdt_start:
	; the GDT starts with null 8-byte
	dd 0x0
	dd 0x0

; GDT for code segment. base = 0x00000000, length = 0xffffff
gdt_code:
	dw 0xffff		; segment length, bits 0-15
	dw 0x0			; segment base, bits 0-15
	db 0x0			; segment base, bits 16-23
	db 10011010b	; flags (8 bits)
	db 11001111b	; flags (4 bits) + segment length, bits 16-19
	db 0x0			; segment base, bits 24-31

; GDT for data segment. base and length identical to code segment
gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

gdt_end:

gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

; 32bit-print
[bits 32]
print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY

print_string_pm_loop:
	mov al, [ebx]	; [ebx] = address of the character
	mov ah, RED_ON_BLACK ; text attribute
	cmp al, 0		; check if end of string
	je print_string_pm_done

	mov [edx], ax	; store character in video memory
	add ebx, 1		; next character
	add edx, 2		; next video memory position
	jmp print_string_pm_loop

print_string_pm_done:
	popa
	ret

; 32bit-switch
[bits 16]
switch_pm:
	cli				; disable interrupts
	lgdt [gdt_descriptor] ; load GDT descriptor
	mov eax, cr0
	or eax, 0x1		; set 32-bit mode bit in cr0
	mov cr0, eax
	jmp CODE_SEG:init_pm

[bits 32]
init_pm:			; now using 32-bit instructions
	mov ax, DATA_SEG ; update segment registers
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000 ; update the stack to the top of free space
	mov esp, ebp
	
	mov ebx, MSG_PROT_MODE
	call print_string_pm

	jmp $

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
STACK equ 0x9000
VIDEO_MEMORY equ 0xb8000
RED_ON_BLACK equ 0x0c
MSG_RED:
	db "Here's another message", 0
MSG_REAL_MODE:
	db "Started in 16-bit real mode", 0
MSG_PROT_MODE:
	db "Loaded 32-bit protected mode", 0

times 510 - ($ - $$) db 0
dw 0xaa55

