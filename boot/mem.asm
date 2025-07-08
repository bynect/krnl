	global __mem_region_count

__mem_region_count:	db 0


;; set the memory region count
mem_region_setup:
	pusha

	mov ax, 0
	mov es, ax
	mov di, 0x5000
	mov edx, 0x534d4150
	xor ebx, ebx

	.next:
		mov eax, 0xe820
		mov ecx, 24
		int 0x15
		cmp ebx, 0
		je .end
		add di, 24
		inc byte [__mem_region_count]
		jmp .next

	.end:
		mov bx, mem_region_string
		call log_mem

		mov bx, [__mem_region_count]
		call print_hex
		call print_newline

		popa
		ret


mem_region_string:	db 'Detected memory regions ', 0
