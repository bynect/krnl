#define MBR_MAGIC	0xAA55
#define GDT_SIZE	(gdt_end - gdt_start)

.macro printz string
	movw	\string, %si
	call	_printz
.endm

.macro padmbr start
	.fill	510-(. - \start), 1, 0
	.word	MBR_MAGIC
.endm
