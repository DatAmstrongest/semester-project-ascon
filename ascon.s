	.cpu cortex-m4
	.arch armv7e-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"ascon.c"
	.text
	.align	1
	.p2align 2,,3
	.global	ascon_p
	.syntax unified
	.thumb
	.thumb_func
	.type	ascon_p, %function
ascon_p:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	rsb	r3, r1, #12
	cmp	r3, #11
	bgt	.L6
	push	{r4, r5, r6, r7, r8, r9, r10, fp, lr}
	ldr	r3, .L10
	rsb	r8, r1, #536870912
	mov	fp, r0
	ldrd	r9, r5, [r0]
	sub	sp, sp, #12
	add	r8, r8, #11
	ldrd	r6, ip, [r0, #12]
	ldrd	r2, r7, [r0, #20]
	ldr	r1, [r0, #8]
	str	fp, [sp, #4]
	add	r8, r3, r8, lsl #3
	ldrd	r4, r0, [r0, #28]
	adds	r3, r3, #88
	str	r3, [sp]
	ldr	r3, [fp, #36]
	mov	lr, r9
.L3:
	ldr	r9, [r8, #8]!
	eor	ip, ip, r9
	ldr	r9, [r8, #4]
	eor	r9, r2, r9
	eor	r2, lr, r0
	eor	lr, lr, r1
	eors	r0, r0, r7
	eor	r1, ip, r1
	eor	r7, ip, r7
	orn	r10, r2, r0
	eor	ip, r5, r3
	orn	r2, lr, r2
	eors	r5, r5, r6
	eors	r3, r3, r4
	eor	r6, r9, r6
	orn	lr, r1, lr
	eor	r9, r9, r4
	orn	r1, r7, r1
	orn	r0, r0, r7
	orn	fp, ip, r3
	eor	r7, lr, r2
	eors	r0, r0, r1
	mvns	r4, r1
	eor	r2, r2, r10
	orn	r1, r9, r6
	orn	ip, r5, ip
	orn	r3, r3, r9
	orn	r5, r6, r5
	eor	r6, r5, ip
	eors	r3, r3, r1
	mvn	r9, r1
	eor	ip, ip, fp
	lsrs	r1, r2, #19
	lsr	lr, r2, #28
	orr	lr, lr, ip, lsl #4
	orr	r1, r1, ip, lsl #13
	eor	r1, r1, lr
	lsr	r5, ip, #19
	eor	lr, r2, r1
	lsr	r1, ip, #28
	orr	r1, r1, r2, lsl #4
	orr	r5, r5, r2, lsl #13
	eors	r5, r5, r1
	eor	r5, ip, r5
	lsls	r1, r7, #3
	lsl	ip, r7, #25
	orr	ip, ip, r6, lsr #7
	orr	r1, r1, r6, lsr #29
	lsls	r2, r6, #3
	eor	r1, r1, ip
	lsl	ip, r6, #25
	orr	ip, ip, r7, lsr #7
	orr	r2, r2, r7, lsr #29
	eor	r2, r2, ip
	eors	r1, r1, r7
	lsr	ip, r4, #1
	lsrs	r7, r4, #6
	orr	r7, r7, r9, lsl #26
	orr	ip, ip, r9, lsl #31
	eor	ip, ip, r7
	eors	r6, r6, r2
	lsr	r7, r9, #6
	lsr	r2, r9, #1
	orr	r7, r7, r4, lsl #26
	orr	r2, r2, r4, lsl #31
	eors	r2, r2, r7
	eor	r2, r9, r2
	lsrs	r7, r0, #10
	lsr	r9, r0, #17
	orr	r9, r9, r3, lsl #15
	orr	r7, r7, r3, lsl #22
	eor	r7, r7, r9
	eor	ip, r4, ip
	lsr	r9, r3, #17
	lsrs	r4, r3, #10
	orr	r9, r9, r0, lsl #15
	orr	r4, r4, r0, lsl #22
	eor	r4, r4, r9
	eors	r7, r7, r0
	lsl	r9, r10, #23
	lsr	r0, r10, #7
	orr	r9, r9, fp, lsr #9
	orr	r0, r0, fp, lsl #25
	eor	r0, r0, r9
	eors	r4, r4, r3
	lsl	r9, fp, #23
	lsr	r3, fp, #7
	orr	r9, r9, r10, lsr #9
	orr	r3, r3, r10, lsl #25
	eor	r3, r3, r9
	ldr	r9, [sp]
	cmp	r9, r8
	eor	r0, r0, r10
	eor	r3, r3, fp
	bne	.L3
	ldr	fp, [sp, #4]
	strd	lr, r5, [fp]
	strd	r1, r6, [fp, #8]
	strd	ip, r2, [fp, #16]
	strd	r7, r4, [fp, #24]
	strd	r0, r3, [fp, #32]
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L6:
	bx	lr
.L11:
	.align	2
.L10:
	.word	.LANCHOR0
	.size	ascon_p, .-ascon_p
	.align	1
	.p2align 2,,3
	.global	ascon_init
	.syntax unified
	.thumb
	.thumb_func
	.type	ascon_init, %function
ascon_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	adr	r7, .L26
	ldrd	r6, [r7]
	strd	r6, [r0]
	subs	r6, r1, #1
	movs	r7, #0
	mov	r5, r1
	mov	r4, r0
	mov	r8, r6
	movs	r3, #56
	mov	r1, r7
.L13:
	ldrb	ip, [r8, #1]!	@ zero_extendqisi2
	sub	r0, r3, #32
	rsb	lr, r3, #32
	lsl	r0, ip, r0
	lsr	lr, ip, lr
	lsl	ip, ip, r3
	subs	r3, r3, #8
	orr	r0, r0, lr
	cmn	r3, #8
	orr	r7, ip, r7
	orr	r1, r1, r0
	bne	.L13
	str	r7, [r4, #8]
	adds	r5, r5, #7
	movs	r7, #0
	str	r1, [r4, #12]
	mov	r8, r5
	movs	r3, #56
	mov	lr, r7
.L14:
	ldrb	r0, [r8, #1]!	@ zero_extendqisi2
	sub	r1, r3, #32
	rsb	ip, r3, #32
	lsl	r1, r0, r1
	lsr	ip, r0, ip
	lsls	r0, r0, r3
	subs	r3, r3, #8
	orr	r1, r1, ip
	cmn	r3, #8
	orr	r7, r7, r0
	orr	lr, r1, lr
	bne	.L14
	strd	r7, lr, [r4, #16]
	movs	r7, #0
	add	r8, r2, #-1
	movs	r3, #56
	mov	lr, r7
.L15:
	ldrb	r0, [r8, #1]!	@ zero_extendqisi2
	sub	r1, r3, #32
	rsb	ip, r3, #32
	lsl	r1, r0, r1
	lsr	ip, r0, ip
	lsls	r0, r0, r3
	subs	r3, r3, #8
	orr	r1, r1, ip
	cmn	r3, #8
	orr	r7, r7, r0
	orr	lr, r1, lr
	bne	.L15
	strd	r7, lr, [r4, #24]
	movs	r7, #0
	adds	r2, r2, #7
	movs	r3, #56
	mov	lr, r7
.L16:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	sub	r1, r3, #32
	rsb	ip, r3, #32
	lsl	r1, r0, r1
	lsr	ip, r0, ip
	lsls	r0, r0, r3
	subs	r3, r3, #8
	orr	r1, r1, ip
	cmn	r3, #8
	orr	r7, r7, r0
	orr	lr, r1, lr
	bne	.L16
	strd	r7, lr, [r4, #32]
	movs	r1, #12
	mov	r0, r4
	bl	ascon_p
	mov	ip, #0
	movs	r3, #56
	mov	r7, ip
.L17:
	ldrb	r1, [r6, #1]!	@ zero_extendqisi2
	sub	r2, r3, #32
	rsb	r0, r3, #32
	lsl	r2, r1, r2
	lsr	r0, r1, r0
	lsls	r1, r1, r3
	subs	r3, r3, #8
	orrs	r2, r2, r0
	cmn	r3, #8
	orr	ip, r1, ip
	orr	r7, r7, r2
	bne	.L17
	ldr	r3, [r4, #24]
	ldr	r2, [r4, #28]
	eor	r3, r3, ip
	movs	r0, #0
	eors	r2, r2, r7
	str	r3, [r4, #24]
	str	r2, [r4, #28]
	movs	r3, #56
	mov	r6, r0
.L18:
	ldrb	ip, [r5, #1]!	@ zero_extendqisi2
	sub	r2, r3, #32
	rsb	r1, r3, #32
	lsl	r2, ip, r2
	lsr	r1, ip, r1
	lsl	ip, ip, r3
	subs	r3, r3, #8
	orrs	r2, r2, r1
	cmn	r3, #8
	orr	r0, ip, r0
	orr	r6, r6, r2
	bne	.L18
	ldrd	r2, r3, [r4, #32]
	eors	r2, r2, r0
	eors	r3, r3, r6
	strd	r2, r3, [r4, #32]
	pop	{r4, r5, r6, r7, r8, pc}
.L27:
	.align	3
.L26:
	.word	0
	.word	-2143286266
	.size	ascon_init, .-ascon_init
	.align	1
	.p2align 2,,3
	.global	ascon_state_to_bytes
	.syntax unified
	.thumb
	.thumb_func
	.type	ascon_state_to_bytes, %function
ascon_state_to_bytes:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	ldrd	r6, r5, [r1]
	subs	r4, r0, #1
	movs	r3, #56
.L29:
	rsb	lr, r3, #32
	sub	ip, r3, #32
	lsr	r2, r6, r3
	lsl	lr, r5, lr
	orr	r2, r2, lr
	lsr	ip, r5, ip
	subs	r3, r3, #8
	orr	r2, r2, ip
	cmn	r3, #8
	strb	r2, [r4, #1]!
	bne	.L29
	ldrd	r6, r5, [r1, #8]
	adds	r4, r0, #7
	movs	r3, #56
.L30:
	rsb	lr, r3, #32
	sub	ip, r3, #32
	lsr	r2, r6, r3
	lsl	lr, r5, lr
	orr	r2, r2, lr
	lsr	ip, r5, ip
	subs	r3, r3, #8
	orr	r2, r2, ip
	cmn	r3, #8
	strb	r2, [r4, #1]!
	bne	.L30
	ldrd	r6, r5, [r1, #16]
	add	r4, r0, #15
	movs	r3, #56
.L31:
	rsb	lr, r3, #32
	sub	ip, r3, #32
	lsr	r2, r6, r3
	lsl	lr, r5, lr
	orr	r2, r2, lr
	lsr	ip, r5, ip
	subs	r3, r3, #8
	orr	r2, r2, ip
	cmn	r3, #8
	strb	r2, [r4, #1]!
	bne	.L31
	ldrd	r6, r5, [r1, #24]
	add	r4, r0, #23
	movs	r3, #56
.L32:
	rsb	lr, r3, #32
	sub	ip, r3, #32
	lsr	r2, r6, r3
	lsl	lr, r5, lr
	orr	r2, r2, lr
	lsr	ip, r5, ip
	subs	r3, r3, #8
	orr	r2, r2, ip
	cmn	r3, #8
	strb	r2, [r4, #1]!
	bne	.L32
	ldrd	r5, r4, [r1, #32]
	adds	r0, r0, #31
	movs	r3, #56
.L33:
	rsb	ip, r3, #32
	sub	r1, r3, #32
	lsr	r2, r5, r3
	lsl	ip, r4, ip
	orr	r2, r2, ip
	lsr	r1, r4, r1
	subs	r3, r3, #8
	orrs	r2, r2, r1
	cmn	r3, #8
	strb	r2, [r0, #1]!
	bne	.L33
	pop	{r4, r5, r6, pc}
	.size	ascon_state_to_bytes, .-ascon_state_to_bytes
	.global	ASCON_RC
	.section	.rodata
	.align	3
	.set	.LANCHOR0,. + 0
	.type	ASCON_RC, %object
	.size	ASCON_RC, 96
ASCON_RC:
	.word	240
	.word	0
	.word	225
	.word	0
	.word	210
	.word	0
	.word	195
	.word	0
	.word	180
	.word	0
	.word	165
	.word	0
	.word	150
	.word	0
	.word	135
	.word	0
	.word	120
	.word	0
	.word	105
	.word	0
	.word	90
	.word	0
	.word	75
	.word	0
	.ident	"GCC: (Arm GNU Toolchain 14.3.Rel1 (Build arm-14.174)) 14.3.1 20250623"
