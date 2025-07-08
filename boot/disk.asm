EXPANDED_SPACE equ 0x8000


;; read dh sectors from drive dl
read_disk:
	mov ah, 0x02
	mov bx, EXPANDED_SPACE
	mov al, dh
	mov ch, 0x00
	mov dh, 0x00
	mov cl, 0x02

	int 0x13
	jc read_error		; carry flag set
	ret


;; read disk error
read_error:
	mov bx, read_error_string
	call log_disk
	call print_newline

	cli
	hlt


read_error_string:	db 'Could not read the disk', 0
