;; pusha for 64b registers
%macro pushall 0
	push rax
	push rcx
	push rdx
	push r8
	push r9
	push r10
	push r11
%endmacro


;; popa for 64b registers
%macro popall 0
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdx
	pop rcx
	pop rax
%endmacro


;; isr macro
%macro isr 1
	global isr%1
	extern isr%1_handler

isr%1:
	pushall
	call isr%1_handler
	popall
	iretq
%endmacro


	global idt_setup
	extern _idt


idt_descriptor:
	dw 4095
	dq _idt


;; isr declaration loop
%assign i 0
%rep 2

isr i

%assign i i+1
%endrep


;; load idt descriptor
idt_setup:
	lidt [idt_descriptor]
	sti
	ret
