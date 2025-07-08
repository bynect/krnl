%macro include_bin 2
	section .rodata
	global %1
%1:
	incbin %2
	db 0
	.size: dq .size - %1
%endmacro
