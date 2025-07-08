	global _start
	extern kernel_main

;; kernel entrypoint
_start:
	;; call kernel_main and halt
	call kernel_main
	cli
	hlt
