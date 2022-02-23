; 16-bit mode bootloader with disk, in 4 parts
; This file is 4 files put together
; Compile with:
;    nasm disk.asm -f bin -o disk.bin
; And try:
;    xxd disk.bin
; Should print '0xDADA' '0xFACE'
[org 0x7c00]		; BIOS executes instructions at 0x7c00
	mov bp, 0x8000	; make sure the stack is away
	mov sp, bp

	mov bx, 0x9000	; es:bx = 0x0000:0x9000 = 0x09000
	mov dh, 2		; read 2 sectors
	call disk_load

	mov dx, [0x9000] ; retrieve the first loaded word, 0xdada
	call print_hex

	call print_nl

	mov dx, [0x9000 + 512] ; first word from second sector, 0xface
	call print_hex

	jmp $

; boot_sect_print

print:
	pusha

start:
	mov al, [bx]	; BX <- base address for string
	cmp al, 0
	je done

	; the part where we print with the BIOS help
	mov ah, 0x0e
	int 0x10		; AL contains the char
	; increment pointer
	add bx, 1
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

; boot_sect_print_hex

print_hex:
	pusha

	mov cx, 0		; CX <- index variable

hex_loop:
	cmp cx, 4		; loop 4 times
	je end

	mov ax, dx		; AX is working register
	and ax, 0x000f	; 0x1234 -> 0x0004 by masking first three to zeros
	add al, 0x30	; add 0x30 to N to convert it to ASCII "N"
	cmp al, 0x39
	jle step2
	add al, 7

step2:
	; BX <- base address + string length - index of char
	mov bx, HEX_OUT + 5
	sub bx, cx		; CX <- index variable
	mov [bx], al
	ror dx, 4

	add cx, 1
	jmp hex_loop

end:
	; prepare the parameter and call the function
	; remember that print receives parameters in BX
	mov bx, HEX_OUT
	call print
	
	popa
	ret

; boot_sect_disk

disk_load:
	pusha
	; reading from disk requires setting specific values in all registers
	; so we will overwrite our input parameters from DX. Let's save it in
	; the stack
	push dx

	mov ah, 0x02	; AH <- interrupt function
	mov al, dh		; AL <- number of sectors to read 01 - 80
	mov cl, 0x02	; CL <- sector (01 - 11)
					; 0x01 is boot sector, 0x02 is first available
	mov ch, 0x00	; CH <- cylinder (0x0 .. 0xff, upper 2 bits in CL)
	; DL <- drive number
	; 0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2
	mov dh, 0x00	; DH <- head number (0 - F)
	
	; [es:bx] <- pointer to buffer where the data will be stored
	; caller sets it up for us
	int 0x13		; BIOS interrupt
	jc disk_error	; if error

	pop dx
	cmp al, dh		; BIOS sets AL to the number of sectors read
	jne sectors_error
	popa
	ret

disk_error:
	mov bx, DISK_ERROR
	call print
	call print_nl
	mov dh, ah		; AH = error code, DL = disk drive that dropped error
	call print_hex
	jmp disk_loop

sectors_error:
	mov bx, SECTORS_ERROR
	call print

disk_loop:
	jmp $			; hangs

HEX_OUT: db '0x0000', 0
DISK_ERROR: db "Disk read error", 0
SECTORS_ERROR: db "Incorrect number of sectors read", 0

; magic number
times 510 - ($ - $$) db 0
dw 0xaa55

; from this point on is sector 2.
; data to be read:
times 256 dw 0xdada	; sector 2 is 512 bytes
times 256 dw 0xface	; sector 3 is 512 bytes

