;; tty video modes 16bit wide
VIDEO_40X25	equ 0x0001
VIDEO_80X25	equ 0x0003


;; set tty video mode
set_video_mode:
	pusha

	mov ah, 0x00
	mov al, dl
	int 0x10

	popa
	ret


;; tty colors 16bit wide
COLOR_BLACK	equ 0x0000
COLOR_BLUE	equ 0x0001
COLOR_GREEN	equ 0x0002
COLOR_CYAN	equ 0x0003
COLOR_RED	equ 0x0004
COLOR_MAGENTA	equ 0x0005
COLOR_BROWN	equ 0x0006
COLOR_LGRAY	equ 0x0007
COLOR_DGRAY	equ 0x0008
COLOR_LBLUE	equ 0x0009
COLOR_LGREEN	equ 0x000a
COLOR_LCYAN	equ 0x000b
COLOR_LRED	equ 0x000c
COLOR_LMAGENTA	equ 0x000d
COLOR_YELLOW	equ 0x000e
COLOR_WHITE	equ 0x000f


;; set tty color
set_color:
	pusha

	mov ah, 0x0b
	mov bh, 0x00
	mov bl, dl
	int 0x10

	popa
	ret
