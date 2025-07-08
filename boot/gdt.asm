CODESEG equ gdt_codedesc - gdt_nulldesc
DATASEG equ gdt_datadesc - gdt_nulldesc


;; gdt null descriptor
gdt_nulldesc:
	dd 0
	dd 0

;; gdt code descriptor
gdt_codedesc:
	dw 0xffff		; limit
	dw 0x0000		; low base
	db 0x00			; medium base
	db 10011010b		; flags
	db 11001111b		; flags and upper limit
	db 0x00			; high base

;; gdt data descriptor
gdt_datadesc:
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 10010010b
	db 11001111b
	db 0x00

;; gdt descriptor end
gdt_end:


;; gdt descriptor
gdt_descriptor:
	gdt_size:
		dw gdt_end - gdt_nulldesc - 1
		dq gdt_nulldesc


	bits 32

;; edit gdt for long mode
gdt_edit:
	mov [gdt_codedesc + 6], byte 10101111b
	mov [gdt_datadesc + 6], byte 10101111b
	ret

	bits 16
