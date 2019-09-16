# print integer by Tanner Babcock
# December 27, 2010
hello:
	.ascii "%d\12\0"
	.text
.globl _main
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$hello, (%esp)
	movl	$60, 4(%esp)
	addl	$9, 4(%esp)
	call	_printf
	xorl	%eax, %eax
	leave
	ret
