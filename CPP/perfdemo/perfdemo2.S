	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"perfdemo.c"
	.local	spi_send_len
	.comm	spi_send_len,4,4
	.local	p_tx_buf
	.comm	p_tx_buf,4,4
	.local	p_spi_send_buf
	.comm	p_spi_send_buf,4,4
	.text
	.align	2
	.type	fill_header_withnop, %function
fill_header_withnop:
	@ args = 0, pretend = 0, frame = 192
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp}
	add	fp, sp, #24
	sub	sp, sp, #196
	str	r0, [fp, #-48]
	str	r1, [fp, #-52]
	str	r2, [fp, #-56]
	sub	r3, fp, #48
	str	r3, [fp, #-32]
	sub	r3, fp, #48
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-56]
	str	r3, [fp, #-40]
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	ldr	r2, .L2
	ldr	r3, .L2+4
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-40]
	strd	r0, [r3]
	ldr	r3, [fp, #-40]
	ldrd	r2, [r3]
	strd	r2, [fp, #-220]
	ldr	r3, [fp, #-32]
	add	r3, r3, #3
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #14
	str	r3, [fp, #-120]
	mov	r3, #0
	str	r3, [fp, #-124]
	ldr	r3, [fp, #-32]
	add	r3, r3, #2
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #5
	str	r3, [fp, #-128]
	mov	r3, #0
	str	r3, [fp, #-132]
	ldrd	r0, [fp, #-124]
	ldrd	r2, [fp, #-132]
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-32]
	add	r3, r3, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r5, r3, asl #28
	orr	r5, r5, r2, lsr #4
	mov	r4, r2, asl #28
	orr	r0, r0, r4
	orr	r1, r1, r5
	ldr	r3, [fp, #-32]
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r7, r3, asl #19
	orr	r7, r7, r2, lsr #13
	mov	r6, r2, asl #19
	orr	r0, r0, r6
	orr	r1, r1, r7
	ldr	r3, [fp, #-36]
	add	r3, r3, #3
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	adds	r2, r2, r2
	adc	r3, r3, r3
	orr	r2, r2, r0
	orr	r3, r3, r1
	ldrd	r0, [fp, #-220]
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-40]
	strd	r0, [r3]
	ldr	r3, [fp, #-40]
	ldrd	r2, [r3]
	mov	r3, r2, asl #24
	str	r3, [fp, #-136]
	mov	r3, #0
	str	r3, [fp, #-140]
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #65280
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r3, r2, asl #8
	str	r3, [fp, #-144]
	mov	r3, #0
	str	r3, [fp, #-148]
	ldrd	r4, [fp, #-140]
	ldrd	r2, [fp, #-148]
	orr	r4, r4, r2
	orr	r5, r5, r3
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #16711680
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r9, r3, asl #24
	orr	r9, r9, r2, lsr #8
	mov	r8, r2, asl #24
	orr	r4, r4, r8
	orr	r5, r5, r9
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #-16777216
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r3, asl #8
	str	r1, [fp, #-64]
	ldr	r1, [fp, #-64]
	orr	r1, r1, r2, lsr #24
	str	r1, [fp, #-64]
	mov	r3, r2, asl #8
	str	r3, [fp, #-68]
	ldrd	r2, [fp, #-68]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #0
	mov	r3, #255
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r2, lsr #8
	str	r1, [fp, #-76]
	ldr	r1, [fp, #-76]
	orr	r1, r1, r3, asl #24
	str	r1, [fp, #-76]
	mov	r3, r3, lsr #8
	str	r3, [fp, #-72]
	ldrd	r2, [fp, #-76]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #0
	mov	r3, #65280
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r2, lsr #24
	str	r1, [fp, #-84]
	ldr	r1, [fp, #-84]
	orr	r1, r1, r3, asl #8
	str	r1, [fp, #-84]
	mov	r3, r3, lsr #24
	str	r3, [fp, #-80]
	ldrd	r2, [fp, #-84]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #0
	mov	r3, #16711680
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r3, r3, lsr #8
	str	r3, [fp, #-156]
	mov	r3, #0
	str	r3, [fp, #-152]
	ldrd	r0, [fp, #-156]
	orr	r0, r0, r4
	orr	r1, r1, r5
	ldr	r3, [fp, #-40]
	ldrd	r2, [r3]
	mov	r3, r3, lsr #24
	str	r3, [fp, #-164]
	mov	r3, #0
	str	r3, [fp, #-160]
	ldrd	r2, [fp, #-164]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-40]
	strd	r0, [r3]
	ldr	r3, [fp, #-56]
	add	r2, r3, #8
	ldr	r3, [fp, #-36]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r3, [fp, #-56]
	add	r3, r3, #9
	str	r3, [fp, #-40]
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #0
	ldr	r3, .L2+8
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-40]
	strd	r0, [r3]
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	ldr	r3, [fp, #-36]
	add	r3, r3, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #23
	str	r3, [fp, #-168]
	mov	r3, #0
	str	r3, [fp, #-172]
	ldr	r3, [fp, #-36]
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #14
	str	r3, [fp, #-176]
	mov	r3, #0
	str	r3, [fp, #-180]
	ldrd	r2, [fp, #-172]
	ldrd	r4, [fp, #-180]
	orr	r2, r2, r4
	orr	r3, r3, r5
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-40]
	strd	r0, [r3]
	ldr	r3, [fp, #-40]
	ldrd	r2, [r3]
	mov	r3, r2, asl #24
	str	r3, [fp, #-184]
	mov	r3, #0
	str	r3, [fp, #-188]
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #65280
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r3, r2, asl #8
	str	r3, [fp, #-192]
	mov	r3, #0
	str	r3, [fp, #-196]
	ldrd	r4, [fp, #-188]
	ldrd	r2, [fp, #-196]
	orr	r4, r4, r2
	orr	r5, r5, r3
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #16711680
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r3, asl #24
	str	r1, [fp, #-88]
	ldr	r1, [fp, #-88]
	orr	r1, r1, r2, lsr #8
	str	r1, [fp, #-88]
	mov	r3, r2, asl #24
	str	r3, [fp, #-92]
	ldrd	r2, [fp, #-92]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldr	r3, [fp, #-40]
	ldrd	r0, [r3]
	mov	r2, #-16777216
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r3, asl #8
	str	r1, [fp, #-96]
	ldr	r1, [fp, #-96]
	orr	r1, r1, r2, lsr #24
	str	r1, [fp, #-96]
	mov	r3, r2, asl #8
	str	r3, [fp, #-100]
	ldrd	r0, [fp, #-100]
	orr	r0, r0, r4
	orr	r1, r1, r5
	ldr	r3, [fp, #-40]
	ldrd	r2, [r3]
	mov	r4, #0
	mov	r5, #255
	and	r2, r2, r4
	and	r3, r3, r5
	mov	ip, r2, lsr #8
	str	ip, [fp, #-108]
	ldr	ip, [fp, #-108]
	orr	ip, ip, r3, asl #24
	str	ip, [fp, #-108]
	mov	r3, r3, lsr #8
	str	r3, [fp, #-104]
	ldrd	r2, [fp, #-108]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-40]
	ldrd	r2, [r3]
	mov	r4, #0
	mov	r5, #65280
	and	r2, r2, r4
	and	r3, r3, r5
	mov	ip, r2, lsr #24
	str	ip, [fp, #-116]
	ldr	ip, [fp, #-116]
	orr	ip, ip, r3, asl #8
	str	ip, [fp, #-116]
	mov	r3, r3, lsr #24
	str	r3, [fp, #-112]
	ldrd	r2, [fp, #-116]
	orr	r2, r2, r0
	orr	r3, r3, r1
	ldr	r1, [fp, #-40]
	ldrd	r0, [r1]
	mov	r4, #0
	mov	r5, #16711680
	and	r0, r0, r4
	and	r1, r1, r5
	mov	r1, r1, lsr #8
	str	r1, [fp, #-204]
	mov	r1, #0
	str	r1, [fp, #-200]
	ldrd	r0, [fp, #-204]
	orr	r0, r0, r2
	orr	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	ldr	r1, [fp, #-40]
	ldrd	r0, [r1]
	mov	r1, r1, lsr #24
	str	r1, [fp, #-212]
	mov	r1, #0
	str	r1, [fp, #-208]
	ldrd	r0, [fp, #-212]
	orr	r0, r0, r2
	orr	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	ldr	r1, [fp, #-40]
	strd	r2, [r1]
	ldr	r3, [fp, #-56]
	add	r3, r3, #17
	mov	r2, #44
	strb	r2, [r3]
	sub	sp, fp, #24
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, fp}
	bx	lr
.L3:
	.align	2
.L2:
	.word	67131137
	.word	178262024
	.word	1075838976
	.size	fill_header_withnop, .-fill_header_withnop
	.align	2
	.type	fill_data_withnop, %function
fill_data_withnop:
	@ args = 0, pretend = 0, frame = 112
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp}
	add	fp, sp, #24
	sub	sp, sp, #116
	str	r0, [fp, #-40]
	str	r1, [fp, #-44]
	ldr	r3, [fp, #-44]
	str	r3, [fp, #-32]
	ldr	r3, [fp, #-40]
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-32]
	ldrd	r0, [r3]
	ldr	r2, .L5
	ldr	r3, .L5+4
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-32]
	strd	r0, [r3]
	ldr	r3, [fp, #-32]
	ldrd	r2, [r3]
	strd	r2, [fp, #-140]
	ldr	r3, [fp, #-36]
	add	r3, r3, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #23
	str	r3, [fp, #-80]
	mov	r3, #0
	str	r3, [fp, #-84]
	ldr	r3, [fp, #-36]
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #14
	str	r3, [fp, #-88]
	mov	r3, #0
	str	r3, [fp, #-92]
	ldrd	r0, [fp, #-84]
	ldrd	r2, [fp, #-92]
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-36]
	add	r3, r3, #3
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #5
	str	r3, [fp, #-96]
	mov	r3, #0
	str	r3, [fp, #-100]
	ldrd	r2, [fp, #-100]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-36]
	add	r3, r3, #2
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r5, r3, asl #28
	orr	r5, r5, r2, lsr #4
	mov	r4, r2, asl #28
	orr	r0, r0, r4
	orr	r1, r1, r5
	ldr	r3, [fp, #-36]
	add	r3, r3, #5
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r7, r3, asl #19
	orr	r7, r7, r2, lsr #13
	mov	r6, r2, asl #19
	orr	r0, r0, r6
	orr	r1, r1, r7
	ldr	r3, [fp, #-36]
	add	r3, r3, #4
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r9, r3, asl #10
	orr	r9, r9, r2, lsr #22
	mov	r8, r2, asl #10
	orr	r0, r0, r8
	orr	r1, r1, r9
	ldr	r3, [fp, #-36]
	add	r3, r3, #7
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	adds	r2, r2, r2
	adc	r3, r3, r3
	orr	r2, r2, r0
	orr	r3, r3, r1
	ldrd	r0, [fp, #-140]
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-32]
	strd	r0, [r3]
	ldr	r3, [fp, #-32]
	ldrd	r2, [r3]
	mov	r3, r2, asl #24
	str	r3, [fp, #-104]
	mov	r3, #0
	str	r3, [fp, #-108]
	ldr	r3, [fp, #-32]
	ldrd	r0, [r3]
	mov	r2, #65280
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r3, r2, asl #8
	str	r3, [fp, #-112]
	mov	r3, #0
	str	r3, [fp, #-116]
	ldrd	r4, [fp, #-108]
	ldrd	r2, [fp, #-116]
	orr	r4, r4, r2
	orr	r5, r5, r3
	ldr	r3, [fp, #-32]
	ldrd	r0, [r3]
	mov	r2, #16711680
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r3, asl #24
	str	r1, [fp, #-48]
	ldr	r1, [fp, #-48]
	orr	r1, r1, r2, lsr #8
	str	r1, [fp, #-48]
	mov	r3, r2, asl #24
	str	r3, [fp, #-52]
	ldrd	r2, [fp, #-52]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldr	r3, [fp, #-32]
	ldrd	r0, [r3]
	mov	r2, #-16777216
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r3, asl #8
	str	r1, [fp, #-56]
	ldr	r1, [fp, #-56]
	orr	r1, r1, r2, lsr #24
	str	r1, [fp, #-56]
	mov	r3, r2, asl #8
	str	r3, [fp, #-60]
	ldrd	r0, [fp, #-60]
	orr	r0, r0, r4
	orr	r1, r1, r5
	ldr	r3, [fp, #-32]
	ldrd	r2, [r3]
	mov	r4, #0
	mov	r5, #255
	and	r2, r2, r4
	and	r3, r3, r5
	mov	ip, r2, lsr #8
	str	ip, [fp, #-68]
	ldr	ip, [fp, #-68]
	orr	ip, ip, r3, asl #24
	str	ip, [fp, #-68]
	mov	r3, r3, lsr #8
	str	r3, [fp, #-64]
	ldrd	r2, [fp, #-68]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-32]
	ldrd	r2, [r3]
	mov	r4, #0
	mov	r5, #65280
	and	r2, r2, r4
	and	r3, r3, r5
	mov	ip, r2, lsr #24
	str	ip, [fp, #-76]
	ldr	ip, [fp, #-76]
	orr	ip, ip, r3, asl #8
	str	ip, [fp, #-76]
	mov	r3, r3, lsr #24
	str	r3, [fp, #-72]
	ldrd	r2, [fp, #-76]
	orr	r2, r2, r0
	orr	r3, r3, r1
	ldr	r1, [fp, #-32]
	ldrd	r0, [r1]
	mov	r4, #0
	mov	r5, #16711680
	and	r0, r0, r4
	and	r1, r1, r5
	mov	r1, r1, lsr #8
	str	r1, [fp, #-124]
	mov	r1, #0
	str	r1, [fp, #-120]
	ldrd	r0, [fp, #-124]
	orr	r0, r0, r2
	orr	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	ldr	r1, [fp, #-32]
	ldrd	r0, [r1]
	mov	r1, r1, lsr #24
	str	r1, [fp, #-132]
	mov	r1, #0
	str	r1, [fp, #-128]
	ldrd	r0, [fp, #-132]
	orr	r0, r0, r2
	orr	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	ldr	r1, [fp, #-32]
	strd	r2, [r1]
	ldr	r3, [fp, #-44]
	add	r3, r3, #8
	ldr	r2, [fp, #-36]
	ldrb	r2, [r2, #6]	@ zero_extendqisi2
	strb	r2, [r3]
	sub	sp, fp, #24
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, fp}
	bx	lr
.L6:
	.align	2
.L5:
	.word	67240193
	.word	1075843080
	.size	fill_data_withnop, .-fill_data_withnop
	.align	2
	.type	filling_spi_send_display_data1, %function
filling_spi_send_display_data1:
	@ args = 0, pretend = 0, frame = 136
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, lr}
	add	fp, sp, #28
	sub	sp, sp, #136
	str	r0, [fp, #-56]
	str	r1, [fp, #-60]
	str	r2, [fp, #-64]
	str	r3, [fp, #-68]
	ldr	r3, [fp, #-56]
	str	r3, [fp, #-36]
	ldr	r3, .L15
.LPIC0:
	add	r3, pc, r3
	ldr	r3, [r3]
	str	r3, [fp, #-40]
	ldr	r3, [fp, #-40]
	str	r3, [fp, #-44]
	ldr	r2, [fp, #-60]
	mov	r3, r2
	mov	r3, r3, asl #3
	add	r3, r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, #216
	str	r3, [fp, #-32]
	ldr	r3, [fp, #-32]
	and	r3, r3, #7
	cmp	r3, #0
	beq	.L8
	ldr	r3, [fp, #-32]
	mov	r3, r3, lsr #3
	add	r2, r3, #1
	b	.L9
.L8:
	ldr	r3, [fp, #-32]
	mov	r2, r3, lsr #3
.L9:
	ldr	r3, .L15+4
.LPIC1:
	add	r3, pc, r3
	str	r2, [r3]
	ldr	r3, .L15+8
.LPIC2:
	add	r3, pc, r3
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L10
	ldr	r3, .L15+12
.LPIC3:
	add	r3, pc, r3
	ldr	r2, [r3]
	ldr	r3, .L15+16
	cmp	r2, r3
	bls	.L11
.L10:
	mvn	r3, #0
	b	.L12
.L11:
	ldr	r3, .L15+20
.LPIC4:
	add	r3, pc, r3
	ldr	r3, [r3]
	str	r3, [fp, #-40]
	ldr	r0, [fp, #-64]
	ldr	r1, [fp, #-68]
	ldr	r2, [fp, #-40]
	bl	fill_header_withnop(PLT)
	ldr	r3, [fp, #-40]
	add	r3, r3, #18
	str	r3, [fp, #-40]
	mov	r3, #0
	str	r3, [fp, #-32]
	b	.L13
.L14:
	ldr	r3, [fp, #-44]
	ldrd	r0, [r3]
	ldr	r2, .L15+24
	ldr	r3, .L15+28
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-44]
	strd	r0, [r3]
	ldr	r3, [fp, #-44]
	ldrd	r4, [r3]
	ldr	r3, [fp, #-36]
	add	r3, r3, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #23
	str	r3, [fp, #-112]
	mov	r3, #0
	str	r3, [fp, #-116]
	ldr	r3, [fp, #-36]
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #14
	str	r3, [fp, #-120]
	mov	r3, #0
	str	r3, [fp, #-124]
	ldrd	r0, [fp, #-116]
	ldrd	r2, [fp, #-124]
	orr	r0, r0, r2
	orr	r1, r1, r3
	ldr	r3, [fp, #-36]
	add	r3, r3, #3
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	r3, r2, asl #5
	str	r3, [fp, #-128]
	mov	r3, #0
	str	r3, [fp, #-132]
	ldrd	r2, [fp, #-132]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-36]
	add	r3, r3, #2
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	ip, r3, asl #28
	str	ip, [fp, #-72]
	ldr	ip, [fp, #-72]
	orr	ip, ip, r2, lsr #4
	str	ip, [fp, #-72]
	mov	r3, r2, asl #28
	str	r3, [fp, #-76]
	ldrd	r2, [fp, #-76]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-36]
	add	r3, r3, #5
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	ip, r3, asl #19
	str	ip, [fp, #-80]
	ldr	ip, [fp, #-80]
	orr	ip, ip, r2, lsr #13
	str	ip, [fp, #-80]
	mov	r3, r2, asl #19
	str	r3, [fp, #-84]
	ldrd	r2, [fp, #-84]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-36]
	add	r3, r3, #4
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	mov	ip, r3, asl #10
	str	ip, [fp, #-88]
	ldr	ip, [fp, #-88]
	orr	ip, ip, r2, lsr #22
	str	ip, [fp, #-88]
	mov	r3, r2, asl #10
	str	r3, [fp, #-92]
	ldrd	r2, [fp, #-92]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-36]
	add	r3, r3, #7
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #255
	mov	r3, #0
	adds	r2, r2, r2
	adc	r3, r3, r3
	orr	r2, r2, r0
	orr	r3, r3, r1
	orr	r0, r4, r2
	orr	r1, r5, r3
	ldr	r3, [fp, #-44]
	strd	r0, [r3]
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r2, [r3]
	mov	r3, r2, asl #24
	str	r3, [fp, #-136]
	mov	r3, #0
	str	r3, [fp, #-140]
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r0, [r3]
	mov	r2, #65280
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r3, r2, asl #8
	str	r3, [fp, #-144]
	mov	r3, #0
	str	r3, [fp, #-148]
	ldrd	r4, [fp, #-140]
	ldrd	r2, [fp, #-148]
	orr	r4, r4, r2
	orr	r5, r5, r3
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r0, [r3]
	mov	r2, #16711680
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r3, asl #24
	str	r1, [fp, #-96]
	ldr	r1, [fp, #-96]
	orr	r1, r1, r2, lsr #8
	str	r1, [fp, #-96]
	mov	r3, r2, asl #24
	str	r3, [fp, #-100]
	ldrd	r2, [fp, #-100]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r0, [r3]
	mov	r2, #-16777216
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r1, r3, asl #8
	str	r1, [fp, #-104]
	ldr	r1, [fp, #-104]
	orr	r1, r1, r2, lsr #24
	str	r1, [fp, #-104]
	mov	r3, r2, asl #8
	str	r3, [fp, #-108]
	ldrd	r2, [fp, #-108]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r0, [r3]
	mov	r2, #0
	mov	r3, #255
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r8, r2, lsr #8
	orr	r8, r8, r3, asl #24
	mov	r9, r3, lsr #8
	orr	r4, r4, r8
	orr	r5, r5, r9
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r0, [r3]
	mov	r2, #0
	mov	r3, #65280
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r6, r2, lsr #24
	orr	r6, r6, r3, asl #8
	mov	r7, r3, lsr #24
	orr	r4, r4, r6
	orr	r5, r5, r7
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r0, [r3]
	mov	r2, #0
	mov	r3, #16711680
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r3, r3, lsr #8
	str	r3, [fp, #-156]
	mov	r3, #0
	str	r3, [fp, #-152]
	ldrd	r0, [fp, #-156]
	orr	r0, r0, r4
	orr	r1, r1, r5
	ldr	r3, [fp, #-32]
	mov	r2, r3, asl #3
	ldr	r3, [fp, #-44]
	add	r3, r3, r2
	ldrd	r2, [r3]
	mov	r3, r3, lsr #24
	str	r3, [fp, #-164]
	mov	r3, #0
	str	r3, [fp, #-160]
	ldrd	r2, [fp, #-164]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldr	r3, [fp, #-44]
	strd	r0, [r3]
	ldr	r3, [fp, #-40]
	add	r2, r3, #8
	ldr	r3, [fp, #-36]
	ldrb	r3, [r3, #6]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r3, [fp, #-36]
	add	r3, r3, #8
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-40]
	add	r3, r3, #9
	str	r3, [fp, #-40]
	ldr	r3, [fp, #-40]
	str	r3, [fp, #-44]
	ldr	r3, [fp, #-32]
	add	r3, r3, #1
	str	r3, [fp, #-32]
.L13:
	ldr	r3, [fp, #-60]
	mov	r2, r3, lsr #1
	ldr	r3, [fp, #-32]
	cmp	r2, r3
	bhi	.L14
	ldr	r3, [fp, #-48]
.L12:
	mov	r0, r3
	sub	sp, fp, #28
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, pc}
.L16:
	.align	2
.L15:
	.word	p_spi_send_buf-(.LPIC0+8)
	.word	spi_send_len-(.LPIC1+8)
	.word	spi_send_len-(.LPIC2+8)
	.word	spi_send_len-(.LPIC3+8)
	.word	345728
	.word	p_spi_send_buf-(.LPIC4+8)
	.word	67240193
	.word	1075843080
	.size	filling_spi_send_display_data1, .-filling_spi_send_display_data1
	.align	2
	.type	get_u8_from_u32, %function
get_u8_from_u32:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r3, [fp, #-12]
	mov	r3, r3, lsr #24
	and	r2, r3, #255
	ldr	r3, [fp, #-8]
	strb	r2, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	ldr	r2, [fp, #-12]
	mov	r2, r2, lsr #16
	and	r2, r2, #255
	strb	r2, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #2
	ldr	r2, [fp, #-12]
	mov	r2, r2, lsr #8
	and	r2, r2, #255
	strb	r2, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #3
	ldr	r2, [fp, #-12]
	and	r2, r2, #255
	strb	r2, [r3]
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	get_u8_from_u32, .-get_u8_from_u32
	.align	2
	.type	write_lcm_command, %function
write_lcm_command:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	mov	r3, r0
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	strb	r3, [fp, #-13]
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	mov	r3, r3, lsr #3
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	and	r3, r3, #7
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	and	r3, r3, #7
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	cmp	r3, #0
	bne	.L19
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldrb	r2, [fp, #-13]
	strb	r2, [r3]
	b	.L20
.L19:
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldr	r1, [fp, #-20]
	ldr	r2, [fp, #-8]
	add	r2, r1, r2
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldrb	r0, [fp, #-13]	@ zero_extendqisi2
	ldr	r2, [fp, #-12]
	mov	r2, r0, asr r2
	and	r2, r2, #255
	orr	r2, r1, r2
	and	r2, r2, #255
	strb	r2, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldr	r1, [fp, #-20]
	ldr	r2, [fp, #-8]
	add	r2, r1, r2
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldrb	r2, [fp, #-13]	@ zero_extendqisi2
	ldr	r0, [fp, #-12]
	rsb	r0, r0, #8
	mov	r2, r2, asl r0
	and	r2, r2, #255
	orr	r2, r1, r2
	and	r2, r2, #255
	strb	r2, [r3]
.L20:
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	add	r2, r3, #9
	ldr	r3, [fp, #-24]
	str	r2, [r3]
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	write_lcm_command, .-write_lcm_command
	.align	2
	.type	write_lcm_data, %function
write_lcm_data:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #28
	mov	r3, r0
	str	r1, [fp, #-20]
	str	r2, [fp, #-24]
	strb	r3, [fp, #-13]
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	mov	r3, r3, lsr #3
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	and	r3, r3, #7
	str	r3, [fp, #-12]
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldr	r1, [fp, #-20]
	ldr	r2, [fp, #-8]
	add	r2, r1, r2
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	r2, [fp, #-12]
	mov	r0, #128
	mov	r2, r0, asr r2
	and	r2, r2, #255
	orr	r2, r1, r2
	and	r2, r2, #255
	strb	r2, [r3]
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	and	r3, r3, #7
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	cmp	r3, #0
	bne	.L22
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldrb	r2, [fp, #-13]
	strb	r2, [r3]
	b	.L23
.L22:
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldr	r1, [fp, #-20]
	ldr	r2, [fp, #-8]
	add	r2, r1, r2
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldrb	r0, [fp, #-13]	@ zero_extendqisi2
	ldr	r2, [fp, #-12]
	mov	r2, r0, asr r2
	and	r2, r2, #255
	orr	r2, r1, r2
	and	r2, r2, #255
	strb	r2, [r3]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldr	r1, [fp, #-20]
	ldr	r2, [fp, #-8]
	add	r2, r1, r2
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldrb	r2, [fp, #-13]	@ zero_extendqisi2
	ldr	r0, [fp, #-12]
	rsb	r0, r0, #8
	mov	r2, r2, asl r0
	and	r2, r2, #255
	orr	r2, r1, r2
	and	r2, r2, #255
	strb	r2, [r3]
.L23:
	ldr	r3, [fp, #-24]
	ldr	r3, [r3]
	add	r2, r3, #9
	ldr	r3, [fp, #-24]
	str	r2, [r3]
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	write_lcm_data, .-write_lcm_data
	.align	2
	.type	filling_spi_send_display_data, %function
filling_spi_send_display_data:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #48
	str	r0, [fp, #-40]
	str	r1, [fp, #-44]
	str	r2, [fp, #-48]
	str	r3, [fp, #-52]
	ldr	r3, [fp, #-40]
	str	r3, [fp, #-12]
	mov	r3, #0
	str	r3, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-28]
	ldr	r3, .L37
.LPIC5:
	add	r3, pc, r3
	ldr	r3, [r3]
	str	r3, [fp, #-20]
	ldr	r2, [fp, #-44]
	mov	r3, r2
	mov	r3, r3, asl #3
	add	r3, r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, #108
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-8]
	and	r3, r3, #7
	cmp	r3, #0
	beq	.L25
	ldr	r3, [fp, #-8]
	mov	r3, r3, lsr #3
	add	r3, r3, #1
	b	.L26
.L25:
	ldr	r3, [fp, #-8]
	mov	r3, r3, lsr #3
.L26:
	ldr	r2, .L37+4
.LPIC6:
	add	r2, pc, r2
	str	r3, [r2]
	ldr	r3, .L37+8
.LPIC7:
	add	r3, pc, r3
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L27
	ldr	r3, .L37+12
.LPIC8:
	add	r3, pc, r3
	ldr	r3, [r3]
	ldr	r2, .L37+16
	cmp	r3, r2
	bls	.L28
.L27:
	mvn	r3, #0
	b	.L36
.L28:
	sub	r3, fp, #28
	mov	r0, #42
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_command(PLT)
	sub	r3, fp, #32
	mov	r0, r3
	ldr	r1, [fp, #-48]
	bl	get_u8_from_u32(PLT)
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L30
.L31:
	sub	r2, fp, #32
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	r3, fp, #28
	mov	r0, r2
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_data(PLT)
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L30:
	ldr	r3, [fp, #-8]
	cmp	r3, #3
	bls	.L31
	sub	r3, fp, #28
	mov	r0, #43
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_command(PLT)
	sub	r3, fp, #32
	mov	r0, r3
	ldr	r1, [fp, #-52]
	bl	get_u8_from_u32(PLT)
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L32
.L33:
	sub	r2, fp, #32
	ldr	r3, [fp, #-8]
	add	r3, r2, r3
	ldrb	r2, [r3]	@ zero_extendqisi2
	sub	r3, fp, #28
	mov	r0, r2
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_data(PLT)
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L32:
	ldr	r3, [fp, #-8]
	cmp	r3, #3
	bls	.L33
	sub	r3, fp, #28
	mov	r0, #44
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_command(PLT)
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L34
.L35:
	ldr	r3, [fp, #-8]
	mov	r3, r3, asl #2
	ldr	r2, [fp, #-12]
	add	r3, r2, r3
	ldr	r3, [r3]
	sub	r2, fp, #32
	mov	r0, r2
	mov	r1, r3
	bl	get_u8_from_u32(PLT)
	ldrb	r2, [fp, #-30]	@ zero_extendqisi2
	sub	r3, fp, #28
	mov	r0, r2
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_data(PLT)
	ldrb	r2, [fp, #-29]	@ zero_extendqisi2
	sub	r3, fp, #28
	mov	r0, r2
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_data(PLT)
	ldrb	r2, [fp, #-32]	@ zero_extendqisi2
	sub	r3, fp, #28
	mov	r0, r2
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_data(PLT)
	ldrb	r2, [fp, #-31]	@ zero_extendqisi2
	sub	r3, fp, #28
	mov	r0, r2
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_data(PLT)
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L34:
	ldr	r2, [fp, #-8]
	ldr	r3, [fp, #-44]
	cmp	r2, r3
	bcc	.L35
	sub	r3, fp, #28
	mov	r0, #0
	ldr	r1, [fp, #-20]
	mov	r2, r3
	bl	write_lcm_command(PLT)
	ldr	r3, [fp, #-24]
.L36:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L38:
	.align	2
.L37:
	.word	p_spi_send_buf-(.LPIC5+8)
	.word	spi_send_len-(.LPIC6+8)
	.word	spi_send_len-(.LPIC7+8)
	.word	spi_send_len-(.LPIC8+8)
	.word	345728
	.size	filling_spi_send_display_data, .-filling_spi_send_display_data
	.align	2
	.type	isLittleEndian, %function
isLittleEndian:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, #1
	str	r3, [fp, #-8]
	sub	r3, fp, #8
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r0, r3
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	isLittleEndian, .-isLittleEndian
	.align	2
	.type	toBigEndian, %function
toBigEndian:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, lr}
	add	fp, sp, #28
	sub	sp, sp, #48
	strd	r0, [fp, #-36]
	bl	isLittleEndian(PLT)
	mov	r3, r0
	cmp	r3, #0
	beq	.L42
	ldrd	r2, [fp, #-36]
	mov	r3, r2, asl #24
	str	r3, [fp, #-48]
	mov	r3, #0
	str	r3, [fp, #-52]
	ldrd	r0, [fp, #-36]
	mov	r2, #65280
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r3, r2, asl #8
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-60]
	ldrd	r2, [fp, #-52]
	ldrd	r0, [fp, #-60]
	orr	r2, r2, r0
	orr	r3, r3, r1
	strd	r2, [fp, #-52]
	ldrd	r0, [fp, #-36]
	mov	r2, #16711680
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r5, r3, asl #24
	orr	r5, r5, r2, lsr #8
	mov	r4, r2, asl #24
	ldrd	r2, [fp, #-52]
	orr	r2, r2, r4
	orr	r3, r3, r5
	mov	r4, r2
	mov	r5, r3
	ldrd	r0, [fp, #-36]
	mov	r2, #-16777216
	mov	r3, #0
	and	r2, r2, r0
	and	r3, r3, r1
	mov	r7, r3, asl #8
	orr	r7, r7, r2, lsr #24
	mov	r6, r2, asl #8
	orr	r0, r4, r6
	orr	r1, r5, r7
	ldrd	r2, [fp, #-36]
	mov	r4, #0
	mov	r5, #255
	and	r2, r2, r4
	and	r3, r3, r5
	mov	ip, r2, lsr #8
	str	ip, [fp, #-44]
	ldr	ip, [fp, #-44]
	orr	ip, ip, r3, asl #24
	str	ip, [fp, #-44]
	mov	r3, r3, lsr #8
	str	r3, [fp, #-40]
	ldrd	r2, [fp, #-44]
	orr	r2, r2, r0
	orr	r3, r3, r1
	mov	r0, r2
	mov	r1, r3
	ldrd	r2, [fp, #-36]
	mov	r4, #0
	mov	r5, #65280
	and	r2, r2, r4
	and	r3, r3, r5
	mov	r8, r2, lsr #24
	orr	r8, r8, r3, asl #8
	mov	r9, r3, lsr #24
	orr	r2, r0, r8
	orr	r3, r1, r9
	ldrd	r0, [fp, #-36]
	mov	r4, #0
	mov	r5, #16711680
	and	r0, r0, r4
	and	r1, r1, r5
	mov	r1, r1, lsr #8
	str	r1, [fp, #-68]
	mov	r1, #0
	str	r1, [fp, #-64]
	ldrd	r0, [fp, #-68]
	orr	r0, r0, r2
	orr	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	ldrd	r0, [fp, #-36]
	mov	r1, r1, lsr #24
	str	r1, [fp, #-76]
	mov	r1, #0
	str	r1, [fp, #-72]
	ldrd	r0, [fp, #-76]
	orr	r0, r0, r2
	orr	r1, r1, r3
	mov	r2, r0
	mov	r3, r1
	b	.L43
.L42:
	ldrd	r2, [fp, #-36]
.L43:
	mov	r0, r2
	mov	r1, r3
	sub	sp, fp, #28
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, pc}
	.size	toBigEndian, .-toBigEndian
	.global	FrameBuff
	.data
	.align	2
	.type	FrameBuff, %object
	.size	FrameBuff, 153600
FrameBuff:
	.word	305419896
	.space	153596
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #12
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	ldr	r4, .L46
.LPIC9:
	add	r4, pc, r4
	ldr	r3, .L46+4
	ldr	r3, [r4, r3]
	mov	r0, r3
	mov	r1, #38400
	mov	r2, #239
	ldr	r3, .L46+8
	bl	filling_spi_send_display_data(PLT)
	ldr	r3, .L46+4
	ldr	r3, [r4, r3]
	mov	r0, r3
	mov	r1, #38400
	mov	r2, #239
	ldr	r3, .L46+8
	bl	filling_spi_send_display_data1(PLT)
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #8
	@ sp needed
	ldmfd	sp!, {r4, fp, pc}
.L47:
	.align	2
.L46:
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC9+8)
	.word	FrameBuff(GOT)
	.word	319
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9 20150123 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
