;; print zero-terminated string
print_string:
	pusha

	mov ah, 0x0e

	.next:
		mov al, [bx]
		cmp al, 0
		je .end
		int 0x10
		inc bx
		jmp .next

	.end:
		popa
		ret


;; print hex number
print_hex:
	pusha

	mov cx, 0
	mov dx, bx

	.next:
		cmp cx, 4
		je .end
		mov ax, dx
		and ax, 0x000f
		add al, 0x30
		cmp al, 0x39
		jle .move_bx
		add al, 0x07

	.move_bx:
		mov bx, .hex_string + 5
		sub bx, cx
		mov [bx], al
		ror dx, 4
		inc cx
		jmp .next

	.end:
		mov bx, .hex_string
		call print_string
		popa
		ret

	.hex_string: db '0x0000', 0


;; print newline and carriage return
print_newline:
	pusha

	mov ah, 0x0e

	mov al, 0x0a		; \n
	int 0x10
	mov al, 0x0d		; \r
	int 0x10

	popa
	ret
