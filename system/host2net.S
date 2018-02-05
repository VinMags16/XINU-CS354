.long	result

.text
	.globl	host2net

host2net:
	push	ebp		# Push base pointer to stack
	mov	ebp, esp	# Set stack frame to new base pointer
	mov	eax, [ebp+8]	# eax now holds argument passed into function
	rol	eax, 8		# rotate left one byte
	xchg	al, ah		# swap end 2 bytes
	ror	eax, 8		# roate back to start
	pop	ebp		# Pop base pointer since we are ending function
	ret
