; Bootloader and kernel
; This file incorporates most of the code from boot.asm and gdt.asm
; Compile with make
; Run with:
;     make run
[org 0x7c00]
	mov [BOOT_DRIVE], dl
	; BIOS gives us boot drive in DL
	mov bp, 0x9000
	mov sp, bp

	mov bx, MSG_REAL_MODE
	call print
	call print_nl

	call load_kernel ; read kernel from the disk
	call switch_pm   ; disable interrupts, load GDT, 32 bit mode
	jmp $            ; never executed

print:
	pusha

start:
	mov al, [bx]    ; BX <- base address for string
	cmp al, 0
	je done

	; the part where we print with the BIOS help
	mov ah, 0x0e
	int 0x10        ; AL contains the char
	; increment pointer
	inc bx
	jmp start

done:
	popa
	ret

print_nl:
	pusha
	mov ah, 0x0e
	mov al, 0x0a    ; newline character
	int 0x10
	mov al, 0x0d    ; carriage return
	int 0x10

	popa
	ret

print_hex:
	pusha

	mov cx, 0       ; CX <- index variable

hex_loop:
	cmp cx, 4       ; loop 4 times
	je end

	mov ax, dx      ; AX is working register
	and ax, 0x000f  ; 0x1234 -> 0x0004 by masking first three to zeros
	add al, 0x30    ; add 0x30 to N to convert it to ASCII "N"
	cmp al, 0x39
	jle step2
	add al, 7

step2:
	; BX <- base address + string length - index of char
	mov bx, HEX_OUT + 5
	sub bx, cx      ; CX <- index variable
	mov [bx], al
	ror dx, 4

	add cx, 1
	jmp hex_loop

end:
	mov bx, HEX_OUT
	call print
	
	popa
	ret

disk_load:
	pusha
	; reading from disk requires setting specific values in all registers
	; so we will overwrite our input parameters from DX. Let's save it in
	; the stack
	push dx

	mov ah, 0x02    ; AH <- interrupt function
	mov al, dh      ; AL <- number of sectors to read 01 - 80
	mov cl, 0x02    ; CL <- sector (01 - 11)
	                ; 0x01 is boot sector, 0x02 is first available
	mov ch, 0x00    ; CH <- cylinder (0x0 .. 0xff, upper 2 bits in CL)
	; DL <- drive number
	; 0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2
	mov dh, 0x00    ; DH <- head number (0 - F)
	
	; [es:bx] <- pointer to buffer where the data will be stored
	; caller sets it up for us
	int 0x13        ; BIOS interrupt
	jc disk_error   ; if error

	pop dx
	cmp al, dh      ; BIOS sets AL to the number of sectors read
	jne sectors_error
	popa
	ret

disk_error:
	mov bx, DISK_ERROR
	call print
	call print_nl
	mov dh, ah      ; AH = error code, DL = disk drive that dropped error
	call print_hex
	jmp disk_loop

sectors_error:
	mov bx, SECTORS_ERROR
	call print

disk_loop:
	jmp $			; hangs

gdt_start:
	; the GDT starts with null 8-byte
	dd 0x0
	dd 0x0

; GDT for code segment. base = 0x00000000, length = 0xffffff
gdt_code:
	dw 0xffff     ; segment length, bits 0-15
	dw 0x0        ; segment base, bits 0-15
	db 0x0        ; segment base, bits 16-23
	db 10011010b  ; flags (8 bits)
	db 11001111b  ; flags (4 bits) + segment length, bits 16-19
	db 0x0        ; segment base, bits 24-31

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

[bits 32]
print_string_pm:
	pusha
	mov edx, VIDEO_MEMORY

print_string_pm_loop:
	mov al, [ebx]   ; [ebx] = address of the character
	mov ah, RED_ON_BLACK ; text attribute
	cmp al, 0       ; check if end of string
	je print_string_pm_done

	mov [edx], ax   ; store character in video memory
	add ebx, 1      ; next character
	add edx, 2      ; next video memory position
	jmp print_string_pm_loop

print_string_pm_done:
	popa
	ret

[bits 16]
switch_pm:
	cli             ; disable interrupts
	lgdt [gdt_descriptor] ; load GDT
	mov eax, cr0
	or eax, 0x1     ; set 32-bit mode in cr0
	mov cr0, eax
	jmp CODE_SEG:init_pm

[bits 32]
init_pm:            ; now using 32-bit instructions
	mov ax, DATA_SEG ; update segment registers
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000 ; update stack to the top of the free space
	mov esp, ebp

	mov ebx, MSG_PROT_MODE
	call print_string_pm
	call KERNEL_OFFSET ; bootloader control ends, kernel begins
	jmp $            ; execution never gets here

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print
	call print_nl

	mov bx, KERNEL_OFFSET ; read from disk and store in 0x1000
	mov dh, 2
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

; notice how arithmetic is performed with memory addresses
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
; segregate sections of GDT
KERNEL_OFFSET equ 0x1000
STACK equ 0x9000
VIDEO_MEMORY equ 0xb8000
; specific memory locations
RED_ON_BLACK equ 0x0c
BOOT_DRIVE db 0
HEX_OUT: db '0x0000', 0
; strings
DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0
MSG_REAL_MODE: db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE: db "Landed in 32-bit Protected Mode", 0
MSG_LOAD_KERNEL: db "Loading kernel into memory", 0

times 510 - ($ - $$) db 0
dw 0xaa55

