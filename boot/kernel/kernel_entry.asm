[bits 32]
[extern main] ; This must have the same name as kernel.c main()
call main ; The linker will know where this is
jmp $     ; This instruction hangs, the last instruction of boot
	      ; sector also hangs, but execution will end here

