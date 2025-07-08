;; detect cpuid
get_cpuid:
	pushfd
	pop eax

	mov ecx, eax
	xor eax, 1 << 21

	push eax
	popfd

	pushfd
	pop eax

	push ecx
	popfd

	xor eax, ecx
	jz cpuid_error
	ret


;; cpuid detection error
cpuid_error:
	cli
	hlt


;; detect long mode
get_long_mode:
	mov eax, 0x80000001
	cpuid

	test edx, 1 << 29
	jz long_mode_error
	ret


;; longmode not supported
long_mode_error:
	cli
	hlt
