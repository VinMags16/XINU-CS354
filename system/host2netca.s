	.file	"host2netca.c"
	.text
	.globl	host2netca
	.type	host2netca, @function
host2netca:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$32, %esp
	movl	8(%ebp), %eax
	sall	$24, %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	andl	$65280, %eax
	sall	$8, %eax
	movl	%eax, -8(%ebp)
	movl	8(%ebp), %eax
	andl	$16711680, %eax
	sarl	$8, %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	shrl	$24, %eax
	movl	%eax, -16(%ebp)
	movl	-4(%ebp), %eax
	orl	-8(%ebp), %eax
	orl	-12(%ebp), %eax
	orl	-16(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	host2netca, .-host2netca
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.6) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
