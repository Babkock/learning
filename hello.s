# hello world complex by Tanner Babcock
# December 24, 2010
.globl _main
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$104, (%esp)
	call	_putchar
	movl	$101, (%esp)
	call	_putchar
	movl	$108, (%esp)
	call	_putchar
	movl	$108, (%esp)
	call	_putchar
	movl	$111, (%esp)
	call	_putchar
	movl	$32, (%esp)
	call	_putchar
	movl	$119, (%esp)
	call	_putchar
	movl	$111, (%esp)
	call	_putchar
	movl	$114, (%esp)
	call	_putchar
	movl	$108, (%esp)
	call	_putchar
	movl	$100, (%esp)
	call	_putchar
	movl	$10, (%esp)
	call	_putchar
	xorl	%eax, %eax
	leave
	ret
