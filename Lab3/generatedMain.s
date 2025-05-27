	.cpu cortex-m4
	.text
	.align	2
	.global	main
	.syntax unified
	.thumb
	.thumb_func

main:
	// args = 0, pretend = 0, frame = 72
	// frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, r7, r8, r9, r10, fp, lr}
	sub	sp, sp, #72
	add	r7, sp, #0
	movs	r3, #0
	str	r3, [r7, #68]
	ldr	r1, .L9
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r1]
	ldr	r1, .L9+4
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r1]
	ldr	r3, .L9+8
	ldrd	r2, [r3]
	ldr	r1, .L9+8
	bic	r4, r2, #2
	mov	r5, r3
	strd	r4, [r1]
	ldr	r3, .L9+12
	ldrd	r2, [r3]
	ldr	r1, .L9+12
	orr	r8, r2, #2
	mov	r9, r3
	strd	r8, [r1]
	ldr	r3, .L9+16
	ldrd	r2, [r3]
	ldr	r1, .L9+16
	orr	r10, r2, #2
	mov	fp, r3
	strd	r10, [r1]
	ldr	r1, .L9+20
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r1]
	ldr	r1, .L9+24
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r1]
	ldr	r3, .L9+28
	ldrd	r2, [r3]
	ldr	r1, .L9+28
	orr	r0, r2, #7
	str	r0, [r7, #56]
	str	r3, [r7, #60]
	ldrd	r3, [r7, #56]
	strd	r3, [r1]
	ldr	r3, .L9+32
	ldrd	r2, [r3]
	ldr	r1, .L9+32
	bic	r0, r2, #7
	str	r0, [r7, #48]
	str	r3, [r7, #52]
	ldrd	r3, [r7, #48]
	strd	r3, [r1]
.L8:
	bl	debounceButton1
	mov	r3, r0
	cmp	r3, #0
	beq	.L2
	ldr	r3, [r7, #68]
	adds	r3, r3, #1
	str	r3, [r7, #68]
	ldr	r3, [r7, #68]
	cmp	r3, #4
	beq	.L3
	ldr	r3, [r7, #68]
	b	.L4
.L3:
	movs	r3, #1
.L4:
	str	r3, [r7, #68]
.L2:
	ldr	r3, [r7, #68]
	cmp	r3, #1
	bne	.L5
	ldr	r3, .L9+32
	ldrd	r2, [r3]
	ldr	r1, .L9+32
	bic	r0, r2, #4
	str	r0, [r7, #40]
	str	r3, [r7, #44]
	ldrd	r3, [r7, #40]
	strd	r3, [r1]
	ldr	r3, .L9+32
	ldrd	r2, [r3]
	ldr	r1, .L9+32
	orr	r0, r2, #1
	str	r0, [r7, #32]
	str	r3, [r7, #36]
	ldrd	r3, [r7, #32]
	strd	r3, [r1]
.L5:
	ldr	r3, [r7, #68]
	cmp	r3, #2
	bne	.L6
	ldr	r3, .L9+32
	ldrd	r2, [r3]
	ldr	r1, .L9+32
	bic	r0, r2, #1
	str	r0, [r7, #24]
	str	r3, [r7, #28]
	ldrd	r3, [r7, #24]
	strd	r3, [r1]
	ldr	r3, .L9+32
	ldrd	r2, [r3]
	ldr	r1, .L9+32
	orr	r0, r2, #2
	str	r0, [r7, #16]
	str	r3, [r7, #20]
	ldrd	r3, [r7, #16]
	strd	r3, [r1]
.L6:
	ldr	r3, [r7, #68]
	cmp	r3, #3
	bne	.L8
	ldr	r3, .L9+32
	ldrd	r2, [r3]
	ldr	r1, .L9+32
	bic	r0, r2, #2
	str	r0, [r7, #8]
	str	r3, [r7, #12]
	ldrd	r3, [r7, #8]
	strd	r3, [r1]
	ldr	r3, .L9+32
	ldrd	r2, [r3]
	ldr	r1, .L9+32
	orr	r0, r2, #4
	str	r0, [r7]
	str	r3, [r7, #4]
	ldrd	r3, [r7]
	strd	r3, [r1]
	b	.L8
.L10:
	.align	2
.L9:
	.word	1073761290
	.word	1073761292
	.word	1073761284
	.word	1073761282
	.word	1073761286
	.word	1073761291
	.word	1073761293
	.word	1073761285
	.word	1073761283
	.size	main, .-main
	.align	1
	.global	debounceButton1
	.syntax unified
	.thumb
	.thumb_func
	.type	debounceButton1, %function
debounceButton1:
	// args = 0, pretend = 0, frame = 0
	// frame_needed = 1, uses_anonymous_args = 0
	// link register save eliminated.
	push	{r4, r7}
	add	r7, sp, #0
	ldr	r1, .L14
	ldrh	r1, [r1]
	sxth	r1, r1
	lsls	r1, r1, #1
	sxth	r4, r1
	ldr	r1, .L14+4
	ldrd	r0, [r1]
	and	r2, r0, #2
	movs	r3, #0
	orrs	r3, r3, r2
	ite	eq
	moveq	r3, #1
	movne	r3, #0
	uxtb	r3, r3
	sxth	r3, r3
	orrs	r3, r3, r4
	sxth	r3, r3
	mvn	r3, r3, lsl #19
	mvn	r3, r3, lsr #19
	sxth	r3, r3
	uxth	r2, r3
	ldr	r3, .L14
	strh	r2, [r3]	// movhi
	ldr	r3, .L14
	ldrh	r3, [r3]
	cmp	r3, #61440
	bne	.L12
	movs	r3, #1
	b	.L13
.L12:
	movs	r3, #0
.L13:
	mov	r0, r3
	mov	sp, r7
	// sp needed
	pop	{r4, r7}
	bx	lr
.L15:
	.align	2
.L14:
	.word	lBounceState.0
	.word	1073761280
	.size	debounceButton1, .-debounceButton1
	.bss
	.align	1
lBounceState.0:
	.space	2
	.size	lBounceState.0, 2
	.ident	"GCC: (15:13.2.rel1-2) 13.2.1 20231009"
