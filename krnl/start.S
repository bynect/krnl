	.code32
	.section .text.prologue
	.globl	_start
_start:
	cli
	call	main
	hlt
