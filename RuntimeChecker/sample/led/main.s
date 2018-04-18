	.text
	.syntax unified
	.eabi_attribute	67, "2.09"	@ Tag_conformance
	.cpu	cortex-m4
	.eabi_attribute	6, 13	@ Tag_CPU_arch
	.eabi_attribute	7, 77	@ Tag_CPU_arch_profile
	.eabi_attribute	8, 0	@ Tag_ARM_ISA_use
	.eabi_attribute	9, 2	@ Tag_THUMB_ISA_use
	.fpu	fpv4-sp-d16
	.eabi_attribute	27, 1	@ Tag_ABI_HardFP_use
	.eabi_attribute	36, 1	@ Tag_FP_HP_extension
	.eabi_attribute	34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute	17, 1	@ Tag_ABI_PCS_GOT_use
	.eabi_attribute	20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute	21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute	23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute	24, 1	@ Tag_ABI_align_needed
	.eabi_attribute	25, 1	@ Tag_ABI_align_preserved
	.eabi_attribute	38, 1	@ Tag_ABI_FP_16bit_format
	.eabi_attribute	18, 4	@ Tag_ABI_PCS_wchar_t
	.eabi_attribute	14, 0	@ Tag_ABI_PCS_R9_use
	.file	"main.cpp"
	.section	.text.startup,"ax",%progbits
	.p2align	1               @ -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,%function
	.code	16                      @ @__cxx_global_var_init
	.thumb_func
__cxx_global_var_init:
	.fnstart
@ BB#0:
	push	{r4, r6, r7, lr}
	add	r7, sp, #8
	movw	r4, :lower16:blinkLeds
	movs	r1, #3
	movs	r2, #12
	movs	r3, #0
	movt	r4, :upper16:blinkLeds
	mov	r0, r4
	bl	_ZN8BlinkLedC1Ejjb
	add.w	r0, r4, #16
	movs	r1, #3
	movs	r2, #13
	movs	r3, #0
	bl	_ZN8BlinkLedC1Ejjb
	add.w	r0, r4, #32
	movs	r1, #3
	movs	r2, #14
	movs	r3, #0
	bl	_ZN8BlinkLedC1Ejjb
	add.w	r0, r4, #48
	movs	r1, #3
	movs	r2, #15
	movs	r3, #0
	bl	_ZN8BlinkLedC1Ejjb
	pop	{r4, r6, r7, pc}
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.fnend
                                        @ -- End function
	.text
	.globl	main                    @ -- Begin function main
	.p2align	1
	.type	main,%function
	.code	16                      @ @main
	.thumb_func
main:
	.fnstart
@ BB#0:
	push	{r4, r5, r7, lr}
	add	r7, sp, #8
	sub	sp, #72
	movs	r4, #0
	str	r4, [sp, #68]
	str	r0, [sp, #64]
	str	r1, [sp, #56]
	movs	r0, #7
	movs	r1, #5
	bl	_Z5adderii
	str	r0, [sp, #52]
	bl	_Z11sig_checkerv
	ldr	r1, [sp, #52]
	movw	r0, :lower16:.L.str
	movt	r0, :upper16:.L.str
	bl	trace_printf
	movw	r0, :lower16:.L.str.1
	movt	r0, :upper16:.L.str.1
	bl	trace_puts
	movw	r0, :lower16:SystemCoreClock
	movt	r0, :upper16:SystemCoreClock
	ldr	r1, [r0]
	movw	r0, :lower16:.L.str.2
	movt	r0, :upper16:.L.str.2
	bl	trace_printf
	add	r0, sp, #48
	bl	_ZN5Timer5startEv
	str	r4, [sp, #44]
	str	r4, [sp, #40]
	b	.LBB1_1
.LBB1_1:                                @ =>This Inner Loop Header: Depth=1
	ldr	r0, [sp, #40]
	ldr	r1, [sp, #44]
	rsbs.w	r0, r0, #3
	mov.w	r0, #0
	sbcs	r0, r1
	blo	.LBB1_4
	b	.LBB1_2
.LBB1_2:                                @   in Loop: Header=BB1_1 Depth=1
	ldr	r0, [sp, #40]
	movw	r1, :lower16:blinkLeds
	movt	r1, :upper16:blinkLeds
	add.w	r0, r1, r0, lsl #4
	bl	_ZN8BlinkLed7powerUpEv
	b	.LBB1_3
.LBB1_3:                                @   in Loop: Header=BB1_1 Depth=1
	ldr	r0, [sp, #40]
	ldr	r1, [sp, #44]
	adds	r0, #1
	adc	r1, r1, #0
	str	r0, [sp, #40]
	str	r1, [sp, #44]
	b	.LBB1_1
.LBB1_4:
	movs	r0, #0
	str	r0, [sp, #36]
	str	r0, [sp, #28]
	str	r0, [sp, #24]
	b	.LBB1_5
.LBB1_5:                                @ =>This Inner Loop Header: Depth=1
	ldr	r0, [sp, #24]
	ldr	r1, [sp, #28]
	rsbs.w	r0, r0, #3
	mov.w	r0, #0
	sbcs	r0, r1
	blo	.LBB1_8
	b	.LBB1_6
.LBB1_6:                                @   in Loop: Header=BB1_5 Depth=1
	ldr	r0, [sp, #24]
	movw	r1, :lower16:blinkLeds
	movt	r1, :upper16:blinkLeds
	add.w	r0, r1, r0, lsl #4
	bl	_ZN8BlinkLed6turnOnEv
	b	.LBB1_7
.LBB1_7:                                @   in Loop: Header=BB1_5 Depth=1
	ldr	r0, [sp, #24]
	ldr	r1, [sp, #28]
	adds	r0, #1
	adc	r1, r1, #0
	str	r0, [sp, #24]
	str	r1, [sp, #28]
	b	.LBB1_5
.LBB1_8:
	add	r0, sp, #48
	mov.w	r1, #1000
	bl	_ZN5Timer5sleepEm
	movs	r0, #0
	str	r0, [sp, #20]
	str	r0, [sp, #16]
	b	.LBB1_9
.LBB1_9:                                @ =>This Inner Loop Header: Depth=1
	ldr	r0, [sp, #16]
	ldr	r1, [sp, #20]
	rsbs.w	r0, r0, #3
	mov.w	r0, #0
	sbcs	r0, r1
	blo	.LBB1_12
	b	.LBB1_10
.LBB1_10:                               @   in Loop: Header=BB1_9 Depth=1
	ldr	r0, [sp, #16]
	movw	r1, :lower16:blinkLeds
	movt	r1, :upper16:blinkLeds
	add.w	r0, r1, r0, lsl #4
	bl	_ZN8BlinkLed7turnOffEv
	b	.LBB1_11
.LBB1_11:                               @   in Loop: Header=BB1_9 Depth=1
	ldr	r0, [sp, #16]
	ldr	r1, [sp, #20]
	adds	r0, #1
	adc	r1, r1, #0
	str	r0, [sp, #16]
	str	r1, [sp, #20]
	b	.LBB1_9
.LBB1_12:
	add	r0, sp, #48
	movs	r1, #250
	bl	_ZN5Timer5sleepEm
	ldr	r0, [sp, #36]
	adds	r0, #1
	str	r0, [sp, #36]
	ldr	r1, [sp, #36]
	movw	r0, :lower16:.L.str.3
	movt	r0, :upper16:.L.str.3
	bl	trace_printf
	movs	r0, #0
	str	r0, [sp, #12]
	str	r0, [sp, #8]
	b	.LBB1_13
.LBB1_13:                               @ =>This Inner Loop Header: Depth=1
	ldr	r0, [sp, #8]
	ldr	r1, [sp, #12]
	rsbs.w	r0, r0, #3
	mov.w	r0, #0
	sbcs	r0, r1
	blo	.LBB1_16
	b	.LBB1_14
.LBB1_14:                               @   in Loop: Header=BB1_13 Depth=1
	ldr	r0, [sp, #8]
	movw	r5, :lower16:blinkLeds
	movt	r5, :upper16:blinkLeds
	add.w	r0, r5, r0, lsl #4
	bl	_ZN8BlinkLed6turnOnEv
	add	r4, sp, #48
	mov	r0, r4
	movw	r1, #750
	bl	_ZN5Timer5sleepEm
	ldr	r0, [sp, #8]
	add.w	r0, r5, r0, lsl #4
	bl	_ZN8BlinkLed7turnOffEv
	mov	r0, r4
	movs	r1, #250
	bl	_ZN5Timer5sleepEm
	ldr	r0, [sp, #36]
	adds	r0, #1
	str	r0, [sp, #36]
	ldr	r1, [sp, #36]
	movw	r0, :lower16:.L.str.3
	movt	r0, :upper16:.L.str.3
	bl	trace_printf
	b	.LBB1_15
.LBB1_15:                               @   in Loop: Header=BB1_13 Depth=1
	ldr	r0, [sp, #8]
	ldr	r1, [sp, #12]
	adds	r0, #1
	adc	r1, r1, #0
	str	r0, [sp, #8]
	str	r1, [sp, #12]
	b	.LBB1_13
.LBB1_16:
	b	.LBB1_17
.LBB1_17:                               @ =>This Loop Header: Depth=1
                                        @     Child Loop BB1_18 Depth 2
	movs	r0, #0
	str	r0, [sp, #4]
	str	r0, [sp]
	b	.LBB1_18
.LBB1_18:                               @   Parent Loop BB1_17 Depth=1
                                        @ =>  This Inner Loop Header: Depth=2
	ldr	r0, [sp]
	ldr	r1, [sp, #4]
	rsbs.w	r0, r0, #3
	mov.w	r0, #0
	sbcs	r0, r1
	blo	.LBB1_23
	b	.LBB1_19
.LBB1_19:                               @   in Loop: Header=BB1_18 Depth=2
	ldr	r0, [sp]
	movw	r4, :lower16:blinkLeds
	movt	r4, :upper16:blinkLeds
	add.w	r0, r4, r0, lsl #4
	bl	_ZN8BlinkLed6toggleEv
	ldr	r0, [sp]
	add.w	r0, r4, r0, lsl #4
	bl	_ZN8BlinkLed4isOnEv
	cmp	r0, #1
	bne	.LBB1_21
	b	.LBB1_20
.LBB1_20:                               @   in Loop: Header=BB1_17 Depth=1
	b	.LBB1_24
.LBB1_21:                               @   in Loop: Header=BB1_18 Depth=2
	b	.LBB1_22
.LBB1_22:                               @   in Loop: Header=BB1_18 Depth=2
	ldr	r0, [sp]
	ldr	r1, [sp, #4]
	adds	r0, #1
	adc	r1, r1, #0
	str	r0, [sp]
	str	r1, [sp, #4]
	b	.LBB1_18
.LBB1_23:                               @ %.loopexit
                                        @   in Loop: Header=BB1_17 Depth=1
	b	.LBB1_24
.LBB1_24:                               @   in Loop: Header=BB1_17 Depth=1
	add	r0, sp, #48
	mov.w	r1, #1000
	bl	_ZN5Timer5sleepEm
	ldr	r0, [sp, #36]
	adds	r0, #1
	str	r0, [sp, #36]
	ldr	r1, [sp, #36]
	movw	r0, :lower16:.L.str.3
	movt	r0, :upper16:.L.str.3
	bl	trace_printf
	b	.LBB1_17
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.fnend
                                        @ -- End function
	.section	.text._ZN5Timer5startEv,"axG",%progbits,_ZN5Timer5startEv,comdat
	.weak	_ZN5Timer5startEv       @ -- Begin function _ZN5Timer5startEv
	.p2align	1
	.type	_ZN5Timer5startEv,%function
	.code	16                      @ @_ZN5Timer5startEv
	.thumb_func
_ZN5Timer5startEv:
	.fnstart
@ BB#0:
	push	{r7, lr}
	mov	r7, sp
	sub	sp, #8
	str	r0, [sp]
	movw	r0, :lower16:SystemCoreClock
	movt	r0, :upper16:SystemCoreClock
	ldr	r0, [r0]
	movw	r1, #19923
	movt	r1, #4194
	umull	r0, r1, r0, r1
	lsrs	r0, r1, #6
	bl	_ZL14SysTick_Configj
	add	sp, #8
	pop	{r7, pc}
.Lfunc_end2:
	.size	_ZN5Timer5startEv, .Lfunc_end2-_ZN5Timer5startEv
	.fnend
                                        @ -- End function
	.text
	.p2align	1               @ -- Begin function _ZL14SysTick_Configj
	.type	_ZL14SysTick_Configj,%function
	.code	16                      @ @_ZL14SysTick_Configj
	.thumb_func
_ZL14SysTick_Configj:
	.fnstart
@ BB#0:
	push	{r7, lr}
	mov	r7, sp
	sub	sp, #8
	str	r0, [sp]
	ldr	r0, [sp]
	subs	r0, #1
	mov.w	r1, #0
	sbc	r1, r1, #0
	subs.w	r0, r0, #16777216
	sbcs	r0, r1, #0
	blo	.LBB3_2
	b	.LBB3_1
.LBB3_1:
	movs	r0, #1
	str	r0, [sp, #4]
	b	.LBB3_3
.LBB3_2:
	ldr	r0, [sp]
	subs	r0, #1
	movw	r1, #57364
	movt	r1, #57344
	str	r0, [r1]
	mov.w	r0, #-1
	movs	r1, #15
	bl	_ZL16NVIC_SetPriority9IRQn_Typej
	movw	r0, #57368
	movt	r0, #57344
	movs	r1, #0
	str	r1, [r0]
	movw	r0, #57360
	movt	r0, #57344
	movs	r2, #7
	str	r2, [r0]
	str	r1, [sp, #4]
	b	.LBB3_3
.LBB3_3:
	ldr	r0, [sp, #4]
	add	sp, #8
	pop	{r7, pc}
.Lfunc_end3:
	.size	_ZL14SysTick_Configj, .Lfunc_end3-_ZL14SysTick_Configj
	.fnend
                                        @ -- End function
	.p2align	1               @ -- Begin function _ZL16NVIC_SetPriority9IRQn_Typej
	.type	_ZL16NVIC_SetPriority9IRQn_Typej,%function
	.code	16                      @ @_ZL16NVIC_SetPriority9IRQn_Typej
	.thumb_func
_ZL16NVIC_SetPriority9IRQn_Typej:
	.fnstart
@ BB#0:
	sub	sp, #8
	str	r0, [sp, #4]
	str	r1, [sp]
	ldr	r0, [sp, #4]
	cmp.w	r0, #-1
	bgt	.LBB4_2
	b	.LBB4_1
.LBB4_1:
	ldr	r0, [sp]
	lsls	r0, r0, #4
	ldr	r1, [sp, #4]
	and	r1, r1, #15
	movw	r2, #60692
	movt	r2, #57344
	strb	r0, [r1, r2]
	b	.LBB4_3
.LBB4_2:
	ldr	r0, [sp]
	lsls	r0, r0, #4
	ldr	r1, [sp, #4]
	movw	r2, #58368
	movt	r2, #57344
	strb	r0, [r1, r2]
	b	.LBB4_3
.LBB4_3:
	add	sp, #8
	bx	lr
.Lfunc_end4:
	.size	_ZL16NVIC_SetPriority9IRQn_Typej, .Lfunc_end4-_ZL16NVIC_SetPriority9IRQn_Typej
	.fnend
                                        @ -- End function
	.section	.text.startup,"ax",%progbits
	.p2align	1               @ -- Begin function _GLOBAL__sub_I_main.cpp
	.type	_GLOBAL__sub_I_main.cpp,%function
	.code	16                      @ @_GLOBAL__sub_I_main.cpp
	.thumb_func
_GLOBAL__sub_I_main.cpp:
	.fnstart
@ BB#0:
	push	{r7, lr}
	mov	r7, sp
	bl	__cxx_global_var_init
	pop	{r7, pc}
.Lfunc_end5:
	.size	_GLOBAL__sub_I_main.cpp, .Lfunc_end5-_GLOBAL__sub_I_main.cpp
	.fnend
                                        @ -- End function
	.type	blinkLeds,%object       @ @blinkLeds
	.bss
	.globl	blinkLeds
	.p2align	4
blinkLeds:
	.zero	64
	.size	blinkLeds, 64

	.type	.L.str,%object          @ @.str
	.section	.rodata.str1.1,"aMS",%progbits,1
.L.str:
	.asciz	"result: %d\n"
	.size	.L.str, 12

	.type	.L.str.1,%object        @ @.str.1
.L.str.1:
	.asciz	"Hello ARM World!"
	.size	.L.str.1, 17

	.type	.L.str.2,%object        @ @.str.2
.L.str.2:
	.asciz	"System clock: %u Hz\n"
	.size	.L.str.2, 21

	.type	.L.str.3,%object        @ @.str.3
.L.str.3:
	.asciz	"Second %u\n"
	.size	.L.str.3, 11

	.section	.init_array,"aw",%init_array
	.p2align	2
	.long	_GLOBAL__sub_I_main.cpp(target1)

	.ident	"clang version 5.0.0 (tags/RELEASE_500/final)"
	.section	".note.GNU-stack","",%progbits
