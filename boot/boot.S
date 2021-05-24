#include "macro.S"

	.code16
	.org	0
	.text
	.globl	_start
_start:
	cli

	movw	%cs, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss
	movw 	$0x3000, %sp

	mov		%dl, xdrive
	sti

	printz	$info_message
	jmp		disk_read

#include "printz.S"
#include "string.S"
#include "disk.S"
#include "entry.S"

	padmbr	_start
