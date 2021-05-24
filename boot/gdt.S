	.align	16
gdt_start:
gdt_null:
	.quad	0
gdt_codeseg:
	.word	0xFFFF
	.word	0x0000
	.byte	0x00
	.byte	0b10011010
	.byte	0b11001111
	.byte	0x00
gdt_dataseg:
	.word	0xFFFF
	.word	0x0000
	.byte	0x00
	.byte	0b10010010
	.byte	0b11001111
	.byte	0x00
gdt_end:
gdt_desc:
	.word	gdt_end - gdt_start - 1
	.long	gdt_null
