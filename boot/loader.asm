	;; first stage bootloader

	bits 16
	org 0x7c00

tty_setup:
	;; set tty video mode
	mov dx, VIDEO_80X25
	call set_video_mode

	;; log tty video mode
	mov bx, video_mode_string
	call log_boot

	mov bx, dx
	call print_hex
	call print_newline

	;; set tty color
	mov dx, COLOR_BLACK
	call set_color

	;; log tty color
	mov bx, color_string
	call log_boot

	mov bx, dx
	call print_hex
	call print_newline


stack_setup:
	;; set up stack
	mov bp, 0x7c00
	mov sp, bp

	;; log stack
	mov bx, stack_string
	call log_boot
	call print_newline


disk_setup:
	;; read from disk
	mov dh, 0x40		; 64 sectors
	mov dl, 0x00		; disk 0
	call read_disk

	;; log disk
	mov bx, disk_string
	call log_disk
	call print_newline


	;; jump to expanded space
	jmp EXPANDED_SPACE


;; 16b includes
%include "boot/print.asm"
%include "boot/tty.asm"
%include "boot/log.asm"
%include "boot/disk.asm"


;; strings
video_mode_string:	db 'Video mode set to ', 0
color_string:		db 'Color set to ', 0
stack_string:		db 'Stack setted up', 0
disk_string:		db 'Successfully read from disk', 0


	;; bootsector
	times 510-($-$$) db 0		; zero padding
	dw 0xaa55			; magic number
