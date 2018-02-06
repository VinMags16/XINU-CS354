.text
	.globl	host2net

host2net:
	push	%ebp		# Push base pointer to stack
	movl	%esp, %ebp	# Set stack frame to new base pointer
	movl	8(%ebp), %eax	# eax now holds argument passed into function
	rol	$8, %eax		# rotate left one byte
	xchg	%al, %ah	# swap end 2 bytes
	ror	$8, %eax		# roate back to start
	pop	%ebp		# Pop base pointer since we are ending function
	ret
