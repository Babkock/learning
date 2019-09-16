section .data
	msg		db "hello world", 0xa
	len		equ $-msg
section .text
global start
start:
	push	dword len
	push	dword msg
	push	dword 1
	
	mov 	eax, 0x4
	sub		esp, 4		; OS X needs extra space
	int		0x80
	
	add		esp, 16		; (3 args * 4 bytes per argument) + 4 bytes extra space
	
	push	dword 69
	mov		eax, 0x1
	sub		esp, 4
	int		0x80
