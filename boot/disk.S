disk_read:
	movb	$8, %ah
	movb	xdrive, %dl
	int		$0x13

	movb	%dh, xheads
	andb	$0x3f, %cl
	movb	%cl, track_sectors

	/* kernel offset = 0x10000 (segment 0x1000) */
	movw	$0x40, %cx
	movw	$0x1000, segment
	movw	$0x0000, offset
	movw	$1, sector
	movw	$2, chs_sector

sector_loop:
	push	%cx

	/* extended read */
	movb	$0x42, %ah
	movb	xdrive, %dl
	movw	$disk_packet, %si
	int		$0x13
	jnc		disk_success

	/* chs read */
	movb	$0x02, %ah
	movb	$1, %al
	movb	chs_cylinder, %ch
	movb	chs_sector, %cl
	movb	xdrive, %dl
	movb	chs_head, %dh
	movw	segment, %es
	movw	offset, %bx
	int		$0x13
	jc		disk_error

disk_success:
	add		$1, sector
	add		$1, chs_sector

	movb	track_sectors, %al
	cmp		%al, chs_sector
	jna		sector_head

	movb	$1, chs_sector
	addb	$1, chs_head
	movb	xheads, %al
	cmpb	%al, chs_head
	jna		sector_head

	movb	$0, chs_head
	addb	$1, chs_cylinder

sector_head:
	addw	$0x200, offset
	jnc		sector_seg
	addw	$0x1000, segment
	movw	$0x0000, offset

sector_seg:
	pop		%cx
	loop	sector_loop

	printz	$succ_message
	cli

	/* A20 line */
	call	enable_a20_wait0
	movb	$0xD0, %al
	outb	$0x64
	call	enable_a20_wait1
	xorw	%ax, %ax
	inb		$0x60

	pushw	%ax
	call	enable_a20_wait0
	movb	$0xD1, %al
	outb	$0x64
	call	enable_a20_wait0
	popw	%ax
	orw		$0x2, %ax
	outb	$0x60

	movl	%cr0, %eax
	orl		$0x1, %eax
	movl	%eax, %cr0

	jmp		enable_protected

disk_error:
	printz	$err_message
	jmp		.

chs_sector:
	.byte 0x01

chs_cylinder:
	.byte 0x00

chs_head:
	.byte 0x00

xdrive:
	.byte 0x00

xheads:
	.byte 0x00

track_sectors:
	.byte 0x00

disk_packet:
	.byte 0x10
	.byte 0x00

xsectors:
	.word 0x0001

offset:
	.word 0x0000

segment:
	.word 0x0000

sector:
	.quad 0x00000000
