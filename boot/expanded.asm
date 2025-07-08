	;; second stage bootloader

	bits 16

	jmp protected_mode_setup


;; 16b includes
%include "boot/gdt.asm"
%include "boot/print.asm"
%include "boot/log.asm"
%include "boot/mem.asm"


protected_mode_setup:
	call mem_region_setup
	call a20_line_setup

	;; log gdt
	mov bx, lgdt_string
	call log_boot
	call print_newline

	cli
	lgdt [gdt_descriptor]		; load gdt
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp CODESEG:protected_mode_start


a20_line_setup:
	;; activate a20 line
	in al, 0x92
	or al, 2
	out 0x92, al

	;; log a20 activation
	mov bx, a20_string
	call log_boot
	call print_newline
	ret


;; strings
a20_string:	db 'A20 line activated', 0
lgdt_string:	db 'Loading GDT', 0


	bits 32

;; 32b includes
%include "boot/cpuid.asm"
%include "boot/paging.asm"


protected_mode_start:
	;; reset registers
	mov ax, DATASEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call get_cpuid		; get cpuid
	call get_long_mode	; get long mode support

	call paging_setup	; set up page table
	call gdt_edit

	;; increment stack size
	mov ebp, 0x80000
	mov esp, ebp

	jmp CODESEG:long_mode_start


	bits 64
	extern _start

long_mode_start:
	;; set up fp number
	call sse_setup

	;; jump to entrypoint
	jmp _start


sse_setup:
	mov rax, cr0
	and ax, 0b11111101
	or ax, 0b00000001
	mov cr0, rax

	mov rax, cr4
	or ax, 0b1100000000
	mov cr4, rax

	ret


	times 4096-($-$$) db 0		; zero padding
