	.text
	.file	"./check/cg_example.c"
	.globl	func1                   # -- Begin function func1
	.p2align	4, 0x90
	.type	func1,@function
func1:                                  # @func1
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi0:
	.cfi_def_cfa_offset 16
.Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	callq	sig_initializer
	movl	$1, -4(%rbp)
	cmpl	$1, SpecificMem
	jne	.LBB0_5
# BB#1:
	cmpl	$1, -4(%rbp)
	jne	.LBB0_3
# BB#2:
	movl	SpecificMem, %eax
	addl	Sum, %eax
	movl	%eax, Sum
	jmp	.LBB0_4
.LBB0_3:
	movl	SpecificMem, %eax
	movl	Sum, %ecx
	subl	%eax, %ecx
	movl	%ecx, Sum
.LBB0_4:
	jmp	.LBB0_5
.LBB0_5:
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	func1, .Lfunc_end0-func1
	.cfi_endproc
                                        # -- End function
	.globl	func2                   # -- Begin function func2
	.p2align	4, 0x90
	.type	func2,@function
func2:                                  # @func2
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi3:
	.cfi_def_cfa_offset 16
.Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	callq	sig_checker
	movl	$1, -4(%rbp)
	cmpl	$1, SpecificMem
	jne	.LBB1_5
# BB#1:
	cmpl	$1, -4(%rbp)
	jne	.LBB1_3
# BB#2:
	movl	SpecificMem, %eax
	addl	Sum, %eax
	movl	%eax, Sum
	jmp	.LBB1_4
.LBB1_3:
	movl	SpecificMem, %eax
	movl	Sum, %ecx
	subl	%eax, %ecx
	movl	%ecx, Sum
.LBB1_4:
	jmp	.LBB1_5
.LBB1_5:
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	func2, .Lfunc_end1-func2
	.cfi_endproc
                                        # -- End function
	.globl	func3                   # -- Begin function func3
	.p2align	4, 0x90
	.type	func3,@function
func3:                                  # @func3
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi6:
	.cfi_def_cfa_offset 16
.Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi8:
	.cfi_def_cfa_register %rbp
	movl	$1, -4(%rbp)
	cmpl	$1, SpecificMem
	jne	.LBB2_5
# BB#1:
	cmpl	$1, -4(%rbp)
	jne	.LBB2_3
# BB#2:
	movl	SpecificMem, %eax
	addl	Sum, %eax
	movl	%eax, Sum
	jmp	.LBB2_4
.LBB2_3:
	movl	SpecificMem, %eax
	movl	Sum, %ecx
	subl	%eax, %ecx
	movl	%ecx, Sum
.LBB2_4:
	jmp	.LBB2_5
.LBB2_5:
	popq	%rbp
	retq
.Lfunc_end2:
	.size	func3, .Lfunc_end2-func3
	.cfi_endproc
                                        # -- End function
	.globl	func4                   # -- Begin function func4
	.p2align	4, 0x90
	.type	func4,@function
func4:                                  # @func4
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi9:
	.cfi_def_cfa_offset 16
.Lcfi10:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi11:
	.cfi_def_cfa_register %rbp
	movl	$1, -4(%rbp)
	cmpl	$1, SpecificMem
	jne	.LBB3_5
# BB#1:
	cmpl	$1, -4(%rbp)
	jne	.LBB3_3
# BB#2:
	movl	SpecificMem, %eax
	addl	Sum, %eax
	movl	%eax, Sum
	jmp	.LBB3_4
.LBB3_3:
	movl	SpecificMem, %eax
	movl	Sum, %ecx
	subl	%eax, %ecx
	movl	%ecx, Sum
.LBB3_4:
	jmp	.LBB3_5
.LBB3_5:
	popq	%rbp
	retq
.Lfunc_end3:
	.size	func4, .Lfunc_end3-func4
	.cfi_endproc
                                        # -- End function
	.globl	func5                   # -- Begin function func5
	.p2align	4, 0x90
	.type	func5,@function
func5:                                  # @func5
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi12:
	.cfi_def_cfa_offset 16
.Lcfi13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi14:
	.cfi_def_cfa_register %rbp
	movl	$1, -4(%rbp)
	cmpl	$1, SpecificMem
	jne	.LBB4_5
# BB#1:
	cmpl	$1, -4(%rbp)
	jne	.LBB4_3
# BB#2:
	movl	SpecificMem, %eax
	addl	Sum, %eax
	movl	%eax, Sum
	jmp	.LBB4_4
.LBB4_3:
	movl	SpecificMem, %eax
	movl	Sum, %ecx
	subl	%eax, %ecx
	movl	%ecx, Sum
.LBB4_4:
	jmp	.LBB4_5
.LBB4_5:
	popq	%rbp
	retq
.Lfunc_end4:
	.size	func5, .Lfunc_end4-func5
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Lcfi15:
	.cfi_def_cfa_offset 16
.Lcfi16:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi17:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$1, SpecificMem
	movl	SpecificMem, %eax
	addl	Sum, %eax
	movl	%eax, Sum
	callq	func1
# BB#1:
	callq	func2
# BB#2:
	callq	func3
# BB#3:
	callq	func4
# BB#4:
	callq	func5
# BB#5:
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end5:
	.size	main, .Lfunc_end5-main
	.cfi_endproc
                                        # -- End function
	.globl	CallcheckerSet          # -- Begin function CallcheckerSet
	.p2align	4, 0x90
	.type	CallcheckerSet,@function
CallcheckerSet:                         # @CallcheckerSet
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Lcfi18:
	.cfi_def_cfa_offset 16
	callq	sig_initializer
	callq	sig_checker
	popq	%rax
	retq
.Lfunc_end6:
	.size	CallcheckerSet, .Lfunc_end6-CallcheckerSet
	.cfi_endproc
                                        # -- End function
	.type	SpecificMem,@object     # @SpecificMem
	.bss
	.globl	SpecificMem
	.p2align	2
SpecificMem:
	.long	0                       # 0x0
	.size	SpecificMem, 4

	.type	Sum,@object             # @Sum
	.globl	Sum
	.p2align	2
Sum:
	.long	0                       # 0x0
	.size	Sum, 4


	.ident	"clang version 5.0.0 (tags/RELEASE_500/final)"
	.section	".note.GNU-stack","",@progbits
