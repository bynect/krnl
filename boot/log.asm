;; print message and header string
log_string:
	pusha

	mov ah, 0x0e

	mov al, '['
	int 0x10

	push bx
	mov bx, dx
	call print_string
	pop bx

	mov al, ']'
	int 0x10

	mov al, ' '
	int 0x10

	call print_string

	popa
	ret


;; shortand log with boot header
log_boot:
	pusha

	mov dx, log_boot_string
	call log_string

	popa
	ret


;; shortand log with disk header
log_disk:
	pusha

	mov dx, log_disk_string
	call log_string

	popa
	ret


;; shortand log with the cpuid header
log_mem:
	pusha

	mov dx, log_mem_string
	call log_string

	popa
	ret


;; log header string
log_boot_string:	db 'BOOT', 0
log_disk_string:	db 'DISK', 0
log_mem_string:		db ' MEM', 0
