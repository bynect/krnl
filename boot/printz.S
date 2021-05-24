_printz:
	movb	$0x0E, %ah
0:
	xorb	%bh, %bh
	lodsb
	cmpb	$0, %al
	je		1f
	int		$0x10
	jmp		0b
1:
	ret
