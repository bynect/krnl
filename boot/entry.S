	.code32
entry:
	/* jump to kernel */
	movl	$0x10000, %ecx
	jmpl	*%ecx

	.code16
enable_protected:
	lidt	idt
	lgdt	gdt_desc

	movw	$(gdt_dataseg - gdt_start), %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %es
	movw	%ax, %fs
	movw	%ax, %gs
	movw	%ax, %ss

	/* bootdesc */
	movl	$0x3000, %esp
	andl	$-16, %esp
	movl	$bootdesc, %eax
	pushl	%esp
	pushl	%eax

	ljmp	$0x8, $entry

enable_a20_wait0:
	xorw	%ax, %ax
	inb		$0x64
	btw		$1, %ax
	jc		enable_a20_wait0
	ret

enable_a20_wait1:
	xorw	%ax, %ax
	inb		$0x64
	btw		$0, %ax
	jnc		enable_a20_wait1
	ret

#include "gdt.S"
#include "idt.S"
#include "bootdesc.S"
