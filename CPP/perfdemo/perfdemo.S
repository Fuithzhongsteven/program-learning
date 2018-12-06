	.cpu generic+fp+simd
	.file	"perfdemo.c"
	.local	spi_send_len
	.comm	spi_send_len,4,4
	.local	p_tx_buf
	.comm	p_tx_buf,8,8
	.local	p_spi_send_buf
	.comm	p_spi_send_buf,8,8
	.text
	.align	2
	.type	fill_header_withnop, %function
fill_header_withnop:
	sub	sp, sp, #48
	str	w0, [sp,12]
	str	w1, [sp,8]
	str	x2, [sp]
	add	x0, sp, 12
	str	x0, [sp,40]
	add	x0, sp, 12
	str	x0, [sp,32]
	ldr	x0, [sp]
	str	x0, [sp,24]
	ldr	x0, [sp,24]
	ldr	x1, [x0]
	mov	x0, 22273
	movk	x0, 0x400, lsl 16
	movk	x0, 0x1008, lsl 32
	movk	x0, 0xaa0, lsl 48
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp,24]
	ldr	x1, [x0]
	ldr	x0, [sp,40]
	add	x0, x0, 3
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x2, x0, 46
	ldr	x0, [sp,40]
	add	x0, x0, 2
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 37
	orr	x2, x2, x0
	ldr	x0, [sp,40]
	add	x0, x0, 1
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 28
	orr	x2, x2, x0
	ldr	x0, [sp,40]
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 19
	orr	x2, x2, x0
	ldr	x0, [sp,32]
	add	x0, x0, 3
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 1
	orr	x0, x2, x0
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	lsl	x1, x0, 56
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 65280
	lsl	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 16711680
	lsl	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 4278190080
	lsl	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 1095216660480
	lsr	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 280375465082880
	lsr	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 71776119061217280
	lsr	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	lsr	x0, x0, 56
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp]
	add	x0, x0, 8
	ldr	x1, [sp,32]
	ldrb	w1, [x1,2]
	strb	w1, [x0]
	ldr	x0, [sp]
	add	x0, x0, 9
	str	x0, [sp,24]
	ldr	x0, [sp,24]
	ldr	x1, [x0]
	mov	x0, 4620693217682128896
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp,24]
	ldr	x1, [x0]
	ldr	x0, [sp,32]
	add	x0, x0, 1
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x2, x0, 55
	ldr	x0, [sp,32]
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 46
	orr	x0, x2, x0
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	lsl	x1, x0, 56
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 65280
	lsl	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 16711680
	lsl	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 4278190080
	lsl	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 1095216660480
	lsr	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 280375465082880
	lsr	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 71776119061217280
	lsr	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	lsr	x0, x0, 56
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp]
	add	x0, x0, 17
	mov	w1, 44
	strb	w1, [x0]
	add	sp, sp, 48
	ret
	.size	fill_header_withnop, .-fill_header_withnop
	.align	2
	.type	fill_data_withnop, %function
fill_data_withnop:
	sub	sp, sp, #32
	str	x0, [sp,8]
	str	x1, [sp]
	ldr	x0, [sp]
	str	x0, [sp,24]
	ldr	x0, [sp,8]
	str	x0, [sp,16]
	ldr	x0, [sp,24]
	ldr	x1, [x0]
	mov	x0, 257
	movk	x0, 0x402, lsl 16
	movk	x0, 0x1008, lsl 32
	movk	x0, 0x4020, lsl 48
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp,24]
	ldr	x1, [x0]
	ldr	x0, [sp,16]
	add	x0, x0, 1
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x2, x0, 55
	ldr	x0, [sp,16]
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 46
	orr	x2, x2, x0
	ldr	x0, [sp,16]
	add	x0, x0, 3
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 37
	orr	x2, x2, x0
	ldr	x0, [sp,16]
	add	x0, x0, 2
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 28
	orr	x2, x2, x0
	ldr	x0, [sp,16]
	add	x0, x0, 5
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 19
	orr	x2, x2, x0
	ldr	x0, [sp,16]
	add	x0, x0, 4
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 10
	orr	x2, x2, x0
	ldr	x0, [sp,16]
	add	x0, x0, 7
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 1
	orr	x0, x2, x0
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	lsl	x1, x0, 56
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 65280
	lsl	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 16711680
	lsl	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 4278190080
	lsl	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 1095216660480
	lsr	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 280375465082880
	lsr	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	and	x0, x0, 71776119061217280
	lsr	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	ldr	x0, [x0]
	lsr	x0, x0, 56
	orr	x1, x1, x0
	ldr	x0, [sp,24]
	str	x1, [x0]
	ldr	x0, [sp]
	add	x0, x0, 8
	ldr	x1, [sp,16]
	ldrb	w1, [x1,6]
	strb	w1, [x0]
	add	sp, sp, 32
	ret
	.size	fill_data_withnop, .-fill_data_withnop
	.align	2
	.type	filling_spi_send_display_data1, %function
filling_spi_send_display_data1:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x0, [x29,40]
	str	w1, [x29,36]
	str	w2, [x29,32]
	str	w3, [x29,28]
	ldr	x0, [x29,40]
	str	x0, [x29,80]
	adrp	x0, p_spi_send_buf
	add	x0, x0, :lo12:p_spi_send_buf
	ldr	x0, [x0]
	str	x0, [x29,72]
	ldr	x0, [x29,72]
	str	x0, [x29,64]
	ldr	w0, [x29,36]
	lsl	w0, w0, 2
	lsl	w1, w0, 3
	add	w0, w0, w1
	add	w0, w0, 216
	str	w0, [x29,92]
	ldr	w0, [x29,92]
	and	w0, w0, 7
	cmp	w0, wzr
	beq	.L4
	ldr	w0, [x29,92]
	lsr	w0, w0, 3
	add	w0, w0, 1
	b	.L5
.L4:
	ldr	w0, [x29,92]
	lsr	w0, w0, 3
.L5:
	adrp	x1, spi_send_len
	add	x1, x1, :lo12:spi_send_len
	str	w0, [x1]
	adrp	x0, spi_send_len
	add	x0, x0, :lo12:spi_send_len
	ldr	w0, [x0]
	cmp	w0, wzr
	beq	.L6
	adrp	x0, spi_send_len
	add	x0, x0, :lo12:spi_send_len
	ldr	w1, [x0]
	mov	w0, 18048
	movk	w0, 0x5, lsl 16
	cmp	w1, w0
	bls	.L7
.L6:
	mov	w0, -1
	b	.L8
.L7:
	adrp	x0, p_spi_send_buf
	add	x0, x0, :lo12:p_spi_send_buf
	ldr	x0, [x0]
	str	x0, [x29,72]
	ldr	w0, [x29,32]
	ldr	w1, [x29,28]
	ldr	x2, [x29,72]
	bl	fill_header_withnop
	ldr	x0, [x29,72]
	add	x0, x0, 18
	str	x0, [x29,72]
	str	wzr, [x29,92]
	b	.L9
.L10:
	ldr	x0, [x29,64]
	ldr	x1, [x0]
	mov	x0, 257
	movk	x0, 0x402, lsl 16
	movk	x0, 0x1008, lsl 32
	movk	x0, 0x4020, lsl 48
	orr	x1, x1, x0
	ldr	x0, [x29,64]
	str	x1, [x0]
	ldr	x0, [x29,64]
	ldr	x1, [x0]
	ldr	x0, [x29,80]
	add	x0, x0, 1
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x2, x0, 55
	ldr	x0, [x29,80]
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 46
	orr	x2, x2, x0
	ldr	x0, [x29,80]
	add	x0, x0, 3
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 37
	orr	x2, x2, x0
	ldr	x0, [x29,80]
	add	x0, x0, 2
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 28
	orr	x2, x2, x0
	ldr	x0, [x29,80]
	add	x0, x0, 5
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 19
	orr	x2, x2, x0
	ldr	x0, [x29,80]
	add	x0, x0, 4
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 10
	orr	x2, x2, x0
	ldr	x0, [x29,80]
	add	x0, x0, 7
	ldrb	w0, [x0]
	uxtb	x0, w0
	lsl	x0, x0, 1
	orr	x0, x2, x0
	orr	x1, x1, x0
	ldr	x0, [x29,64]
	str	x1, [x0]
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x1, [x29,64]
	add	x0, x1, x0
	ldr	x0, [x0]
	lsl	x1, x0, 56
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x2, [x29,64]
	add	x0, x2, x0
	ldr	x0, [x0]
	and	x0, x0, 65280
	lsl	x0, x0, 40
	orr	x1, x1, x0
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x2, [x29,64]
	add	x0, x2, x0
	ldr	x0, [x0]
	and	x0, x0, 16711680
	lsl	x0, x0, 24
	orr	x1, x1, x0
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x2, [x29,64]
	add	x0, x2, x0
	ldr	x0, [x0]
	and	x0, x0, 4278190080
	lsl	x0, x0, 8
	orr	x1, x1, x0
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x2, [x29,64]
	add	x0, x2, x0
	ldr	x0, [x0]
	and	x0, x0, 1095216660480
	lsr	x0, x0, 8
	orr	x1, x1, x0
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x2, [x29,64]
	add	x0, x2, x0
	ldr	x0, [x0]
	and	x0, x0, 280375465082880
	lsr	x0, x0, 24
	orr	x1, x1, x0
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x2, [x29,64]
	add	x0, x2, x0
	ldr	x0, [x0]
	and	x0, x0, 71776119061217280
	lsr	x0, x0, 40
	orr	x1, x1, x0
	ldr	w0, [x29,92]
	lsl	x0, x0, 3
	ldr	x2, [x29,64]
	add	x0, x2, x0
	ldr	x0, [x0]
	lsr	x0, x0, 56
	orr	x1, x1, x0
	ldr	x0, [x29,64]
	str	x1, [x0]
	ldr	x0, [x29,72]
	add	x0, x0, 8
	ldr	x1, [x29,80]
	ldrb	w1, [x1,6]
	strb	w1, [x0]
	ldr	x0, [x29,80]
	add	x0, x0, 8
	str	x0, [x29,80]
	ldr	x0, [x29,72]
	add	x0, x0, 9
	str	x0, [x29,72]
	ldr	x0, [x29,72]
	str	x0, [x29,64]
	ldr	w0, [x29,92]
	add	w0, w0, 1
	str	w0, [x29,92]
.L9:
	ldr	w0, [x29,36]
	lsr	w1, w0, 1
	ldr	w0, [x29,92]
	cmp	w1, w0
	bhi	.L10
	ldr	w0, [x29,60]
.L8:
	ldp	x29, x30, [sp], 96
	ret
	.size	filling_spi_send_display_data1, .-filling_spi_send_display_data1
	.align	2
	.type	get_u8_from_u32, %function
get_u8_from_u32:
	sub	sp, sp, #16
	str	x0, [sp,8]
	str	w1, [sp,4]
	ldr	w0, [sp,4]
	lsr	w0, w0, 24
	uxtb	w1, w0
	ldr	x0, [sp,8]
	strb	w1, [x0]
	ldr	x0, [sp,8]
	add	x0, x0, 1
	ldr	w1, [sp,4]
	lsr	w1, w1, 16
	uxtb	w1, w1
	strb	w1, [x0]
	ldr	x0, [sp,8]
	add	x0, x0, 2
	ldr	w1, [sp,4]
	lsr	w1, w1, 8
	uxtb	w1, w1
	strb	w1, [x0]
	ldr	x0, [sp,8]
	add	x0, x0, 3
	ldr	w1, [sp,4]
	uxtb	w1, w1
	strb	w1, [x0]
	add	sp, sp, 16
	ret
	.size	get_u8_from_u32, .-get_u8_from_u32
	.align	2
	.type	write_lcm_command, %function
write_lcm_command:
	sub	sp, sp, #48
	strb	w0, [sp,31]
	str	x1, [sp,16]
	str	x2, [sp,8]
	ldr	x0, [sp,8]
	ldr	w0, [x0]
	lsr	w0, w0, 3
	str	w0, [sp,44]
	ldr	x0, [sp,8]
	ldr	w0, [x0]
	and	w0, w0, 7
	str	w0, [sp,40]
	ldr	w0, [sp,40]
	add	w0, w0, 1
	and	w0, w0, 7
	str	w0, [sp,40]
	ldr	w0, [sp,40]
	cmp	w0, wzr
	bne	.L13
	ldr	w0, [sp,44]
	add	w0, w0, 1
	str	w0, [sp,44]
	ldr	w0, [sp,44]
	ldr	x1, [sp,16]
	add	x0, x1, x0
	ldrb	w1, [sp,31]
	strb	w1, [x0]
	b	.L14
.L13:
	ldr	w0, [sp,44]
	ldr	x1, [sp,16]
	add	x0, x1, x0
	ldr	w1, [sp,44]
	ldr	x2, [sp,16]
	add	x1, x2, x1
	ldrb	w2, [x1]
	ldrb	w3, [sp,31]
	ldr	w1, [sp,40]
	asr	w1, w3, w1
	uxtb	w1, w1
	orr	w1, w2, w1
	uxtb	w1, w1
	strb	w1, [x0]
	ldr	w0, [sp,44]
	add	w0, w0, 1
	str	w0, [sp,44]
	ldr	w0, [sp,44]
	ldr	x1, [sp,16]
	add	x0, x1, x0
	ldr	w1, [sp,44]
	ldr	x2, [sp,16]
	add	x1, x2, x1
	ldrb	w2, [x1]
	ldrb	w1, [sp,31]
	mov	w4, 8
	ldr	w3, [sp,40]
	sub	w3, w4, w3
	lsl	w1, w1, w3
	uxtb	w1, w1
	orr	w1, w2, w1
	uxtb	w1, w1
	strb	w1, [x0]
.L14:
	ldr	x0, [sp,8]
	ldr	w0, [x0]
	add	w1, w0, 9
	ldr	x0, [sp,8]
	str	w1, [x0]
	add	sp, sp, 48
	ret
	.size	write_lcm_command, .-write_lcm_command
	.align	2
	.type	write_lcm_data, %function
write_lcm_data:
	sub	sp, sp, #48
	strb	w0, [sp,31]
	str	x1, [sp,16]
	str	x2, [sp,8]
	ldr	x0, [sp,8]
	ldr	w0, [x0]
	lsr	w0, w0, 3
	str	w0, [sp,44]
	ldr	x0, [sp,8]
	ldr	w0, [x0]
	and	w0, w0, 7
	str	w0, [sp,40]
	ldr	w0, [sp,44]
	ldr	x1, [sp,16]
	add	x0, x1, x0
	ldr	w1, [sp,44]
	ldr	x2, [sp,16]
	add	x1, x2, x1
	ldrb	w2, [x1]
	ldr	w1, [sp,40]
	mov	w3, 128
	asr	w1, w3, w1
	uxtb	w1, w1
	orr	w1, w2, w1
	uxtb	w1, w1
	strb	w1, [x0]
	ldr	w0, [sp,40]
	add	w0, w0, 1
	and	w0, w0, 7
	str	w0, [sp,40]
	ldr	w0, [sp,40]
	cmp	w0, wzr
	bne	.L16
	ldr	w0, [sp,44]
	add	w0, w0, 1
	str	w0, [sp,44]
	ldr	w0, [sp,44]
	ldr	x1, [sp,16]
	add	x0, x1, x0
	ldrb	w1, [sp,31]
	strb	w1, [x0]
	b	.L17
.L16:
	ldr	w0, [sp,44]
	ldr	x1, [sp,16]
	add	x0, x1, x0
	ldr	w1, [sp,44]
	ldr	x2, [sp,16]
	add	x1, x2, x1
	ldrb	w2, [x1]
	ldrb	w3, [sp,31]
	ldr	w1, [sp,40]
	asr	w1, w3, w1
	uxtb	w1, w1
	orr	w1, w2, w1
	uxtb	w1, w1
	strb	w1, [x0]
	ldr	w0, [sp,44]
	add	w0, w0, 1
	str	w0, [sp,44]
	ldr	w0, [sp,44]
	ldr	x1, [sp,16]
	add	x0, x1, x0
	ldr	w1, [sp,44]
	ldr	x2, [sp,16]
	add	x1, x2, x1
	ldrb	w2, [x1]
	ldrb	w1, [sp,31]
	mov	w4, 8
	ldr	w3, [sp,40]
	sub	w3, w4, w3
	lsl	w1, w1, w3
	uxtb	w1, w1
	orr	w1, w2, w1
	uxtb	w1, w1
	strb	w1, [x0]
.L17:
	ldr	x0, [sp,8]
	ldr	w0, [x0]
	add	w1, w0, 9
	ldr	x0, [sp,8]
	str	w1, [x0]
	add	sp, sp, 48
	ret
	.size	write_lcm_data, .-write_lcm_data
	.align	2
	.type	filling_spi_send_display_data, %function
filling_spi_send_display_data:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x0, [x29,40]
	str	w1, [x29,36]
	str	w2, [x29,32]
	str	w3, [x29,28]
	ldr	x0, [x29,40]
	str	x0, [x29,80]
	str	wzr, [x29,76]
	str	wzr, [x29,56]
	adrp	x0, p_spi_send_buf
	add	x0, x0, :lo12:p_spi_send_buf
	ldr	x0, [x0]
	str	x0, [x29,64]
	ldr	w0, [x29,36]
	lsl	w0, w0, 2
	lsl	w1, w0, 3
	add	w0, w0, w1
	add	w0, w0, 108
	str	w0, [x29,92]
	ldr	w0, [x29,92]
	and	w0, w0, 7
	cmp	w0, wzr
	beq	.L19
	ldr	w0, [x29,92]
	lsr	w0, w0, 3
	add	w0, w0, 1
	b	.L20
.L19:
	ldr	w0, [x29,92]
	lsr	w0, w0, 3
.L20:
	adrp	x1, spi_send_len
	add	x1, x1, :lo12:spi_send_len
	str	w0, [x1]
	adrp	x0, spi_send_len
	add	x0, x0, :lo12:spi_send_len
	ldr	w0, [x0]
	cmp	w0, wzr
	beq	.L21
	adrp	x0, spi_send_len
	add	x0, x0, :lo12:spi_send_len
	ldr	w1, [x0]
	mov	w0, 18048
	movk	w0, 0x5, lsl 16
	cmp	w1, w0
	bls	.L22
.L21:
	mov	w0, -1
	b	.L30
.L22:
	add	x2, x29, 56
	mov	w0, 42
	ldr	x1, [x29,64]
	bl	write_lcm_command
	add	x0, x29, 48
	ldr	w1, [x29,32]
	bl	get_u8_from_u32
	str	wzr, [x29,92]
	b	.L24
.L25:
	ldr	w0, [x29,92]
	add	x1, x29, 96
	add	x0, x1, x0
	ldrb	w0, [x0,-48]
	add	x2, x29, 56
	ldr	x1, [x29,64]
	bl	write_lcm_data
	ldr	w0, [x29,92]
	add	w0, w0, 1
	str	w0, [x29,92]
.L24:
	ldr	w0, [x29,92]
	cmp	w0, 3
	bls	.L25
	add	x2, x29, 56
	mov	w0, 43
	ldr	x1, [x29,64]
	bl	write_lcm_command
	add	x0, x29, 48
	ldr	w1, [x29,28]
	bl	get_u8_from_u32
	str	wzr, [x29,92]
	b	.L26
.L27:
	ldr	w0, [x29,92]
	add	x1, x29, 96
	add	x0, x1, x0
	ldrb	w0, [x0,-48]
	add	x2, x29, 56
	ldr	x1, [x29,64]
	bl	write_lcm_data
	ldr	w0, [x29,92]
	add	w0, w0, 1
	str	w0, [x29,92]
.L26:
	ldr	w0, [x29,92]
	cmp	w0, 3
	bls	.L27
	add	x2, x29, 56
	mov	w0, 44
	ldr	x1, [x29,64]
	bl	write_lcm_command
	str	wzr, [x29,92]
	b	.L28
.L29:
	ldr	w0, [x29,92]
	lsl	x0, x0, 2
	ldr	x1, [x29,80]
	add	x0, x1, x0
	ldr	w1, [x0]
	add	x0, x29, 48
	bl	get_u8_from_u32
	ldrb	w0, [x29,50]
	add	x2, x29, 56
	ldr	x1, [x29,64]
	bl	write_lcm_data
	ldrb	w0, [x29,51]
	add	x2, x29, 56
	ldr	x1, [x29,64]
	bl	write_lcm_data
	ldrb	w0, [x29,48]
	add	x2, x29, 56
	ldr	x1, [x29,64]
	bl	write_lcm_data
	ldrb	w0, [x29,49]
	add	x2, x29, 56
	ldr	x1, [x29,64]
	bl	write_lcm_data
	ldr	w0, [x29,92]
	add	w0, w0, 1
	str	w0, [x29,92]
.L28:
	ldr	w1, [x29,92]
	ldr	w0, [x29,36]
	cmp	w1, w0
	bcc	.L29
	add	x2, x29, 56
	mov	w0, 0
	ldr	x1, [x29,64]
	bl	write_lcm_command
	ldr	w0, [x29,60]
.L30:
	ldp	x29, x30, [sp], 96
	ret
	.size	filling_spi_send_display_data, .-filling_spi_send_display_data
	.align	2
	.type	isLittleEndian, %function
isLittleEndian:
	sub	sp, sp, #16
	mov	w0, 1
	str	w0, [sp,12]
	add	x0, sp, 12
	ldrb	w0, [x0]
	add	sp, sp, 16
	ret
	.size	isLittleEndian, .-isLittleEndian
	.align	2
	.type	toBigEndian, %function
toBigEndian:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x0, [x29,24]
	bl	isLittleEndian
	cmp	w0, wzr
	beq	.L34
	ldr	x0, [x29,24]
	lsl	x1, x0, 56
	ldr	x0, [x29,24]
	and	x0, x0, 65280
	lsl	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [x29,24]
	and	x0, x0, 16711680
	lsl	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [x29,24]
	and	x0, x0, 4278190080
	lsl	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [x29,24]
	and	x0, x0, 1095216660480
	lsr	x0, x0, 8
	orr	x1, x1, x0
	ldr	x0, [x29,24]
	and	x0, x0, 280375465082880
	lsr	x0, x0, 24
	orr	x1, x1, x0
	ldr	x0, [x29,24]
	and	x0, x0, 71776119061217280
	lsr	x0, x0, 40
	orr	x1, x1, x0
	ldr	x0, [x29,24]
	lsr	x0, x0, 56
	orr	x0, x1, x0
	b	.L35
.L34:
	ldr	x0, [x29,24]
.L35:
	ldp	x29, x30, [sp], 32
	ret
	.size	toBigEndian, .-toBigEndian
	.global	FrameBuff
	.data
	.align	3
	.type	FrameBuff, %object
	.size	FrameBuff, 153600
FrameBuff:
	.word	305419896
	.zero	153596
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	w0, [x29,28]
	str	x1, [x29,16]
	adrp	x0, :got:FrameBuff
	ldr	x0, [x0, #:got_lo12:FrameBuff]
	mov	w1, 38400
	mov	w2, 239
	mov	w3, 319
	bl	filling_spi_send_display_data
	adrp	x0, :got:FrameBuff
	ldr	x0, [x0, #:got_lo12:FrameBuff]
	mov	w1, 38400
	mov	w2, 239
	mov	w3, 319
	bl	filling_spi_send_display_data1
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9 20150123 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
