	.cpu cortex-m4
	.arch armv7e-m
	.fpu fpv4-sp-d16
	.eabi_attribute 27, 1
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 38, 1
	.eabi_attribute 18, 4
	.file	"app_uart_ringbuff.c"
	.text
.Ltext0:
	.global	Buffer
	.section	.bss.Buffer,"aw",%nobits
	.align	2
	.type	Buffer, %object
	.size	Buffer, 1026
Buffer:
	.space	1026
	.global	RingBuffer
	.section	.bss.RingBuffer,"aw",%nobits
	.align	2
	.type	RingBuffer, %object
	.size	RingBuffer, 4
RingBuffer:
	.space	4
	.global	timeout
	.section	.bss.timeout,"aw",%nobits
	.align	1
	.type	timeout, %object
	.size	timeout, 2
timeout:
	.space	2
	.section	.text.app_uart_ringbuffer_init,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_init
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_init, %function
app_uart_ringbuffer_init:
.LFB11:
	.file 1 "F:\\nRF5_SDK_17.1.0_ddde560\\examples\\Myproject\\template_project_combine\\app_uart_ringbuff.c"
	.loc 1 7 1
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 8 15
	ldr	r3, .L2
	ldr	r3, [r3]
	.loc 1 8 22
	movs	r2, #0
	strb	r2, [r3]
	.loc 1 9 15
	ldr	r3, .L2
	ldr	r3, [r3]
	.loc 1 9 22
	movs	r2, #0
	strb	r2, [r3, #1]
	.loc 1 10 16
	ldr	r3, .L2
	ldr	r2, .L2+4
	str	r2, [r3]
	.loc 1 12 1
	nop
	bx	lr
.L3:
	.align	2
.L2:
	.word	RingBuffer
	.word	Buffer
.LFE11:
	.size	app_uart_ringbuffer_init, .-app_uart_ringbuffer_init
	.section	.text.app_uart_ringbuffer_put,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_put
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_put, %function
app_uart_ringbuffer_put:
.LFB12:
	.loc 1 14 43
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	sp, sp, #8
.LCFI0:
	mov	r3, r0
	strb	r3, [sp, #7]
	.loc 1 15 15
	ldr	r3, .L5
	ldr	r3, [r3]
	.loc 1 15 34
	ldr	r2, .L5
	ldr	r2, [r2]
	ldrb	r2, [r2]
	uxtb	r2, r2
	.loc 1 15 41
	add	r3, r3, r2
	ldrb	r2, [sp, #7]
	strb	r2, [r3, #2]
	.loc 1 16 15
	ldr	r3, .L5
	ldr	r3, [r3]
	ldrb	r2, [r3]
	uxtb	r2, r2
	.loc 1 16 21
	adds	r2, r2, #1
	uxtb	r2, r2
	strb	r2, [r3]
	.loc 1 17 18
	ldr	r3, .L5
	ldr	r3, [r3]
	ldrb	r3, [r3]
	.loc 1 21 1
	nop
	add	sp, sp, #8
.LCFI1:
	@ sp needed
	bx	lr
.L6:
	.align	2
.L5:
	.word	RingBuffer
.LFE12:
	.size	app_uart_ringbuffer_put, .-app_uart_ringbuffer_put
	.section	.text.app_uart_ringbuff_data_check,"ax",%progbits
	.align	1
	.global	app_uart_ringbuff_data_check
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuff_data_check, %function
app_uart_ringbuff_data_check:
.LFB13:
	.loc 1 26 1
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	sp, sp, #8
.LCFI2:
	.loc 1 27 15
	movs	r3, #0
	strb	r3, [sp, #7]
	.loc 1 28 48
	ldr	r3, .L10
	ldr	r3, [r3]
	ldrb	r3, [r3]
	uxtb	r3, r3
	uxth	r2, r3
	.loc 1 28 67
	ldr	r3, .L10
	ldr	r3, [r3]
	ldrb	r3, [r3, #1]
	uxtb	r3, r3
	uxth	r3, r3
	.loc 1 28 55
	subs	r3, r2, r3
	uxth	r3, r3
	add	r3, r3, #1024
	uxth	r3, r3
	.loc 1 28 14
	ubfx	r3, r3, #0, #10
	strh	r3, [sp, #4]	@ movhi
	.loc 1 29 7
	ldrh	r3, [sp, #4]
	cmp	r3, #0
	bne	.L8
	.loc 1 31 20
	ldrb	r3, [sp, #7]	@ zero_extendqisi2
	b	.L9
.L8:
	.loc 1 33 19
	movs	r3, #1
	strb	r3, [sp, #7]
	.loc 1 34 20
	ldrb	r3, [sp, #7]	@ zero_extendqisi2
.L9:
	.loc 1 37 1
	mov	r0, r3
	add	sp, sp, #8
.LCFI3:
	@ sp needed
	bx	lr
.L11:
	.align	2
.L10:
	.word	RingBuffer
.LFE13:
	.size	app_uart_ringbuff_data_check, .-app_uart_ringbuff_data_check
	.section	.text.app_uart_ringbuffer_get,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_get
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_get, %function
app_uart_ringbuffer_get:
.LFB14:
	.loc 1 40 1
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	sp, sp, #8
.LCFI4:
	.loc 1 41 30
	ldr	r3, .L14
	ldr	r3, [r3]
	.loc 1 41 49
	ldr	r2, .L14
	ldr	r2, [r2]
	ldrb	r2, [r2, #1]
	uxtb	r2, r2
	.loc 1 41 13
	add	r3, r3, r2
	ldrb	r3, [r3, #2]
	strb	r3, [sp, #7]
	.loc 1 42 15
	ldr	r3, .L14
	ldr	r3, [r3]
	ldrb	r2, [r3, #1]
	uxtb	r2, r2
	.loc 1 42 21
	adds	r2, r2, #1
	uxtb	r2, r2
	strb	r2, [r3, #1]
	.loc 1 43 18
	ldr	r3, .L14
	ldr	r3, [r3]
	ldrb	r3, [r3, #1]
	.loc 1 47 12
	ldrb	r3, [sp, #7]	@ zero_extendqisi2
	.loc 1 48 1
	mov	r0, r3
	add	sp, sp, #8
.LCFI5:
	@ sp needed
	bx	lr
.L15:
	.align	2
.L14:
	.word	RingBuffer
.LFE14:
	.size	app_uart_ringbuffer_get, .-app_uart_ringbuffer_get
	.section	.text.app_uart_ringbuffer_reset,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_reset
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_reset, %function
app_uart_ringbuffer_reset:
.LFB15:
	.loc 1 51 1
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI6:
	.loc 1 52 22
	ldr	r3, .L17
	ldr	r3, [r3]
	adds	r3, r3, #2
	.loc 1 52 5
	mov	r2, #1024
	movs	r1, #0
	mov	r0, r3
	bl	memset
	.loc 1 53 15
	ldr	r3, .L17
	ldr	r3, [r3]
	.loc 1 53 22
	movs	r2, #0
	strb	r2, [r3]
	.loc 1 54 15
	ldr	r3, .L17
	ldr	r3, [r3]
	.loc 1 54 22
	movs	r2, #0
	strb	r2, [r3, #1]
	.loc 1 55 1
	nop
	pop	{r3, pc}
.L18:
	.align	2
.L17:
	.word	RingBuffer
.LFE15:
	.size	app_uart_ringbuffer_reset, .-app_uart_ringbuffer_reset
	.section	.text.app_uart_ringbuffer_peek,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_peek
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_peek, %function
app_uart_ringbuffer_peek:
.LFB16:
	.loc 1 62 1
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 63 18
	ldr	r3, .L22
	ldr	r3, [r3]
	ldrb	r3, [r3, #1]
	uxtb	r2, r3
	.loc 1 63 38
	ldr	r3, .L22
	ldr	r3, [r3]
	ldrb	r3, [r3]
	uxtb	r3, r3
	.loc 1 63 7
	cmp	r2, r3
	bne	.L20
	.loc 1 65 20
	mov	r3, #-1
	b	.L21
.L20:
	.loc 1 67 30
	ldr	r3, .L22
	ldr	r3, [r3]
	.loc 1 67 49
	ldr	r2, .L22
	ldr	r2, [r2]
	ldrb	r2, [r2, #1]
	uxtb	r2, r2
	.loc 1 67 38
	add	r3, r3, r2
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
.L21:
	.loc 1 69 1
	mov	r0, r3
	bx	lr
.L23:
	.align	2
.L22:
	.word	RingBuffer
.LFE16:
	.size	app_uart_ringbuffer_peek, .-app_uart_ringbuffer_peek
	.section	.text.app_uart_ringbuffer_wait_for,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_wait_for
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_wait_for, %function
app_uart_ringbuffer_wait_for:
.LFB17:
	.loc 1 75 1
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{lr}
.LCFI7:
	sub	sp, sp, #20
.LCFI8:
	str	r0, [sp, #4]
	.loc 1 75 15
	ldr	r0, [sp, #4]
	bl	strlen
	mov	r3, r0
	.loc 1 75 9
	str	r3, [sp, #8]
	.loc 1 76 9
	movs	r3, #0
	str	r3, [sp, #12]
.L25:
	.loc 1 79 10
	nop
.L26:
	.loc 1 79 12 discriminator 1
	bl	app_uart_ringbuff_data_check
	mov	r3, r0
	.loc 1 79 42 discriminator 1
	cmp	r3, #1
	bne	.L26
	.loc 1 81 10
	b	.L27
.L30:
	.loc 1 83 26
	ldr	r3, .L38
	ldr	r3, [r3]
	ldrb	r3, [r3, #1]
	uxtb	r2, r3
	.loc 1 83 46
	ldr	r3, .L38
	ldr	r3, [r3]
	ldrb	r3, [r3]
	uxtb	r3, r3
	.loc 1 83 15
	cmp	r2, r3
	beq	.L28
	.loc 1 85 31
	ldr	r3, .L38
	ldr	r3, [r3]
	ldrb	r2, [r3, #1]
	uxtb	r2, r2
	.loc 1 85 37
	adds	r2, r2, #1
	uxtb	r2, r2
	strb	r2, [r3, #1]
	b	.L27
.L28:
	.loc 1 87 28
	movs	r3, #0
	b	.L29
.L27:
	.loc 1 81 11
	bl	app_uart_ringbuffer_peek
	mov	r1, r0
	.loc 1 81 47
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #4]
	add	r3, r3, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 81 38
	cmp	r1, r3
	bne	.L30
	.loc 1 90 10
	b	.L31
.L34:
	.loc 1 92 14
	ldr	r3, [sp, #12]
	adds	r3, r3, #1
	str	r3, [sp, #12]
	.loc 1 93 23
	ldr	r3, .L38
	ldr	r3, [r3]
	ldrb	r2, [r3, #1]
	uxtb	r2, r2
	.loc 1 93 29
	adds	r2, r2, #1
	uxtb	r2, r2
	strb	r2, [r3, #1]
	.loc 1 94 15
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #8]
	cmp	r2, r3
	bne	.L37
	.loc 1 94 33 discriminator 1
	movs	r3, #1
	b	.L29
.L37:
	.loc 1 96 18
	nop
.L33:
	.loc 1 96 19 discriminator 1
	bl	app_uart_ringbuff_data_check
	mov	r3, r0
	.loc 1 96 49 discriminator 1
	cmp	r3, #1
	bne	.L33
.L31:
	.loc 1 90 11
	bl	app_uart_ringbuffer_peek
	mov	r1, r0
	.loc 1 90 47
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #4]
	add	r3, r3, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 90 38
	cmp	r1, r3
	beq	.L34
	.loc 1 99 7
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #8]
	cmp	r2, r3
	beq	.L35
	.loc 1 101 15
	movs	r3, #0
	str	r3, [sp, #12]
	.loc 1 102 13
	b	.L25
.L35:
	.loc 1 104 7
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #8]
	cmp	r2, r3
	bne	.L36
	.loc 1 106 20
	movs	r3, #1
	b	.L29
.L36:
	.loc 1 107 22
	movs	r3, #0
.L29:
	.loc 1 108 1
	mov	r0, r3
	add	sp, sp, #20
.LCFI9:
	@ sp needed
	ldr	pc, [sp], #4
.L39:
	.align	2
.L38:
	.word	RingBuffer
.LFE17:
	.size	app_uart_ringbuffer_wait_for, .-app_uart_ringbuffer_wait_for
	.section	.text.app_uart_ringbuffer_get_after,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_get_after
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_get_after, %function
app_uart_ringbuffer_get_after:
.LFB18:
	.loc 1 116 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI10:
	sub	sp, sp, #24
.LCFI11:
	str	r0, [sp, #12]
	mov	r3, r1
	str	r2, [sp, #4]
	strb	r3, [sp, #11]
.LBB2:
	.loc 1 117 14
	movs	r3, #0
	str	r3, [sp, #20]
	.loc 1 117 5
	b	.L41
.L43:
	.loc 1 120 18
	nop
.L42:
	.loc 1 120 19 discriminator 1
	bl	app_uart_ringbuff_data_check
	mov	r3, r0
	.loc 1 120 49 discriminator 1
	cmp	r3, #1
	bne	.L42
	.loc 1 122 25 discriminator 2
	ldr	r3, [sp, #20]
	ldr	r2, [sp, #4]
	adds	r4, r2, r3
	.loc 1 122 31 discriminator 2
	bl	app_uart_ringbuffer_get
	mov	r3, r0
	.loc 1 122 29 discriminator 2
	strb	r3, [r4]
	.loc 1 117 39 discriminator 2
	ldr	r3, [sp, #20]
	adds	r3, r3, #1
	str	r3, [sp, #20]
.L41:
	.loc 1 117 22 discriminator 1
	ldrb	r3, [sp, #11]	@ zero_extendqisi2
	ldr	r2, [sp, #20]
	cmp	r2, r3
	blt	.L43
.LBE2:
	.loc 1 124 12
	movs	r3, #1
	.loc 1 125 1
	mov	r0, r3
	add	sp, sp, #24
.LCFI12:
	@ sp needed
	pop	{r4, pc}
.LFE18:
	.size	app_uart_ringbuffer_get_after, .-app_uart_ringbuffer_get_after
	.section	.text.app_uart_ringbuffer_GetDataFormBuffer,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_GetDataFormBuffer
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_GetDataFormBuffer, %function
app_uart_ringbuffer_GetDataFormBuffer:
.LFB19:
	.loc 1 133 1
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{lr}
.LCFI13:
	sub	sp, sp, #52
.LCFI14:
	str	r0, [sp, #12]
	str	r1, [sp, #8]
	str	r2, [sp, #4]
	str	r3, [sp]
	.loc 1 134 29
	ldr	r0, [sp, #12]
	bl	strlen
	mov	r3, r0
	.loc 1 134 9
	str	r3, [sp, #32]
	.loc 1 135 27
	ldr	r0, [sp, #8]
	bl	strlen
	mov	r3, r0
	.loc 1 135 9
	str	r3, [sp, #28]
	.loc 1 136 9
	movs	r3, #0
	str	r3, [sp, #44]
	.loc 1 137 9
	movs	r3, #0
	str	r3, [sp, #40]
	.loc 1 138 9
	movs	r3, #0
	str	r3, [sp, #24]
	.loc 1 139 9
	movs	r3, #0
	str	r3, [sp, #20]
.L46:
	.loc 1 143 14
	b	.L47
.L48:
	.loc 1 143 57 discriminator 2
	ldr	r3, [sp, #44]
	adds	r3, r3, #1
	str	r3, [sp, #44]
.L47:
	.loc 1 143 26 discriminator 1
	ldr	r3, [sp, #40]
	ldr	r2, [sp, #12]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 143 47 discriminator 1
	ldr	r3, [sp, #44]
	ldr	r1, [sp, #4]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 143 30 discriminator 1
	cmp	r2, r3
	bne	.L48
	.loc 1 144 23
	ldr	r3, [sp, #40]
	ldr	r2, [sp, #12]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 144 44
	ldr	r3, [sp, #44]
	ldr	r1, [sp, #4]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 144 11
	cmp	r2, r3
	bne	.L49
	.loc 1 146 22
	b	.L50
.L51:
	.loc 1 148 28
	ldr	r3, [sp, #44]
	adds	r3, r3, #1
	str	r3, [sp, #44]
	.loc 1 149 26
	ldr	r3, [sp, #40]
	adds	r3, r3, #1
	str	r3, [sp, #40]
.L50:
	.loc 1 146 34
	ldr	r3, [sp, #40]
	ldr	r2, [sp, #12]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 146 55
	ldr	r3, [sp, #44]
	ldr	r1, [sp, #4]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 146 38
	cmp	r2, r3
	beq	.L51
.L49:
	.loc 1 152 15
	ldr	r3, [sp, #32]
	str	r3, [sp, #40]
	.loc 1 152 11
	ldr	r3, [sp, #40]
	cmp	r3, #0
	beq	.L52
	.loc 1 152 50 discriminator 1
	ldr	r3, [sp, #44]
	str	r3, [sp, #24]
	.loc 1 157 11 discriminator 1
	movs	r3, #0
	str	r3, [sp, #40]
	b	.L55
.L52:
	.loc 1 154 15
	movs	r3, #0
	str	r3, [sp, #40]
	.loc 1 155 13
	b	.L46
.L54:
	.loc 1 159 18
	b	.L55
.L56:
	.loc 1 159 59 discriminator 2
	ldr	r3, [sp, #44]
	adds	r3, r3, #1
	str	r3, [sp, #44]
.L55:
	.loc 1 159 28 discriminator 1
	ldr	r3, [sp, #40]
	ldr	r2, [sp, #8]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 159 49 discriminator 1
	ldr	r3, [sp, #44]
	ldr	r1, [sp, #4]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 159 32 discriminator 1
	cmp	r2, r3
	bne	.L56
	.loc 1 160 25
	ldr	r3, [sp, #40]
	ldr	r2, [sp, #8]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 160 46
	ldr	r3, [sp, #44]
	ldr	r1, [sp, #4]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 160 15
	cmp	r2, r3
	bne	.L57
	.loc 1 162 26
	b	.L58
.L59:
	.loc 1 164 30
	ldr	r3, [sp, #40]
	adds	r3, r3, #1
	str	r3, [sp, #40]
	.loc 1 165 32
	ldr	r3, [sp, #44]
	adds	r3, r3, #1
	str	r3, [sp, #44]
.L58:
	.loc 1 162 37
	ldr	r3, [sp, #40]
	ldr	r2, [sp, #8]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 162 57
	ldr	r3, [sp, #44]
	ldr	r1, [sp, #4]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 162 40
	cmp	r2, r3
	beq	.L59
.L57:
	.loc 1 168 18
	ldr	r3, [sp, #28]
	str	r3, [sp, #40]
	.loc 1 168 15
	ldr	r3, [sp, #40]
	cmp	r3, #0
	beq	.L60
	.loc 1 170 33
	ldr	r2, [sp, #44]
	ldr	r3, [sp, #28]
	subs	r3, r2, r3
	str	r3, [sp, #20]
	.loc 1 176 7
	movs	r3, #0
	str	r3, [sp, #40]
	.loc 1 177 9
	movs	r3, #0
	str	r3, [sp, #44]
.LBB3:
	.loc 1 178 13
	ldr	r3, [sp, #24]
	str	r3, [sp, #36]
	.loc 1 178 5
	b	.L62
.L60:
.LBE3:
	.loc 1 173 23
	movs	r3, #0
	str	r3, [sp, #40]
	.loc 1 174 21
	b	.L54
.L63:
.LBB4:
	.loc 1 180 46 discriminator 3
	ldr	r3, [sp, #36]
	ldr	r2, [sp, #4]
	add	r2, r2, r3
	.loc 1 180 27 discriminator 3
	ldr	r3, [sp, #40]
	ldr	r1, [sp]
	add	r3, r3, r1
	.loc 1 180 46 discriminator 3
	ldrb	r2, [r2]	@ zero_extendqisi2
	.loc 1 180 30 discriminator 3
	strb	r2, [r3]
	.loc 1 181 14 discriminator 3
	ldr	r3, [sp, #40]
	adds	r3, r3, #1
	str	r3, [sp, #40]
	.loc 1 178 49 discriminator 3
	ldr	r3, [sp, #36]
	adds	r3, r3, #1
	str	r3, [sp, #36]
.L62:
	.loc 1 178 34 discriminator 1
	ldr	r2, [sp, #36]
	ldr	r3, [sp, #20]
	cmp	r2, r3
	blt	.L63
.LBE4:
	.loc 1 183 1
	nop
	nop
	add	sp, sp, #52
.LCFI15:
	@ sp needed
	ldr	pc, [sp], #4
.LFE19:
	.size	app_uart_ringbuffer_GetDataFormBuffer, .-app_uart_ringbuffer_GetDataFormBuffer
	.section	.text.app_uart_ringbuffer_copy_upto,"ax",%progbits
	.align	1
	.global	app_uart_ringbuffer_copy_upto
	.syntax unified
	.thumb
	.thumb_func
	.type	app_uart_ringbuffer_copy_upto, %function
app_uart_ringbuffer_copy_upto:
.LFB20:
	.loc 1 196 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI16:
	sub	sp, sp, #24
.LCFI17:
	str	r0, [sp, #4]
	str	r1, [sp]
	.loc 1 197 19
	ldr	r0, [sp, #4]
	bl	strlen
	mov	r3, r0
	.loc 1 197 13
	str	r3, [sp, #12]
	.loc 1 198 13
	movs	r3, #0
	str	r3, [sp, #20]
	.loc 1 199 13
	movs	r3, #0
	str	r3, [sp, #16]
.L65:
	.loc 1 201 14
	b	.L66
.L68:
	.loc 1 203 47
	ldr	r3, .L75
	ldr	r2, [r3]
	.loc 1 203 66
	ldr	r3, .L75
	ldr	r3, [r3]
	ldrb	r3, [r3, #1]
	uxtb	r3, r3
	mov	r0, r3
	.loc 1 203 29
	ldr	r3, [sp, #16]
	ldr	r1, [sp]
	add	r3, r3, r1
	.loc 1 203 55
	add	r2, r2, r0
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	.loc 1 203 35
	strb	r2, [r3]
	.loc 1 204 20
	ldr	r3, [sp, #16]
	adds	r3, r3, #1
	str	r3, [sp, #16]
	.loc 1 205 27
	ldr	r3, .L75
	ldr	r3, [r3]
	ldrb	r2, [r3, #1]
	uxtb	r2, r2
	.loc 1 205 33
	adds	r2, r2, #1
	uxtb	r2, r2
	strb	r2, [r3, #1]
	.loc 1 206 22
	nop
.L67:
	.loc 1 206 24 discriminator 1
	bl	app_uart_ringbuff_data_check
	mov	r3, r0
	.loc 1 206 23 discriminator 1
	cmp	r3, #0
	beq	.L67
.L66:
	.loc 1 201 15
	bl	app_uart_ringbuffer_peek
	mov	r1, r0
	.loc 1 201 51
	ldr	r3, [sp, #20]
	ldr	r2, [sp, #4]
	add	r3, r3, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 201 42
	cmp	r1, r3
	bne	.L68
	.loc 1 208 15
	b	.L69
.L71:
	.loc 1 209 18
	ldr	r3, [sp, #20]
	adds	r3, r3, #1
	str	r3, [sp, #20]
	.loc 1 210 33
	ldr	r3, [sp, #16]
	adds	r2, r3, #1
	str	r2, [sp, #16]
	mov	r2, r3
	.loc 1 210 29
	ldr	r3, [sp]
	adds	r4, r3, r2
	.loc 1 210 39
	bl	app_uart_ringbuffer_get
	mov	r3, r0
	.loc 1 210 37
	strb	r3, [r4]
	.loc 1 212 22
	nop
.L70:
	.loc 1 212 23 discriminator 1
	bl	app_uart_ringbuff_data_check
	mov	r3, r0
	.loc 1 212 53 discriminator 1
	cmp	r3, #1
	bne	.L70
.L69:
	.loc 1 208 16
	bl	app_uart_ringbuffer_peek
	mov	r1, r0
	.loc 1 208 52
	ldr	r3, [sp, #20]
	ldr	r2, [sp, #4]
	add	r3, r3, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 208 43
	cmp	r1, r3
	beq	.L71
	.loc 1 215 7
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #12]
	cmp	r2, r3
	beq	.L72
	.loc 1 217 15
	movs	r3, #0
	str	r3, [sp, #20]
	.loc 1 218 13
	b	.L65
.L72:
	.loc 1 220 7
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #12]
	cmp	r2, r3
	bne	.L73
	.loc 1 222 20
	movs	r3, #1
	b	.L74
.L73:
	.loc 1 223 22
	movs	r3, #0
.L74:
	.loc 1 224 1
	mov	r0, r3
	add	sp, sp, #24
.LCFI18:
	@ sp needed
	pop	{r4, pc}
.L76:
	.align	2
.L75:
	.word	RingBuffer
.LFE20:
	.size	app_uart_ringbuffer_copy_upto, .-app_uart_ringbuffer_copy_upto
	.section	.text.check_for,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	check_for, %function
check_for:
.LFB21:
	.loc 1 228 1
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{lr}
.LCFI19:
	sub	sp, sp, #28
.LCFI20:
	str	r0, [sp, #4]
	str	r1, [sp]
	.loc 1 229 24
	ldr	r0, [sp, #4]
	bl	strlen
	mov	r3, r0
	.loc 1 229 9
	str	r3, [sp, #12]
	.loc 1 230 24
	ldr	r0, [sp]
	bl	strlen
	mov	r3, r0
	.loc 1 230 9
	str	r3, [sp, #8]
	.loc 1 231 9
	movs	r3, #0
	str	r3, [sp, #20]
	.loc 1 232 9
	movs	r3, #0
	str	r3, [sp, #16]
.L78:
	.loc 1 234 14
	b	.L79
.L81:
	.loc 1 236 20
	ldr	r3, [sp, #20]
	adds	r3, r3, #1
	str	r3, [sp, #20]
	.loc 1 237 19
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #8]
	cmp	r2, r3
	ble	.L79
	.loc 1 237 47 discriminator 1
	movs	r3, #0
	b	.L80
.L79:
	.loc 1 234 18
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #4]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 234 41
	ldr	r3, [sp, #20]
	ldr	r1, [sp]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 234 22
	cmp	r2, r3
	bne	.L81
	.loc 1 239 15
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #4]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 239 38
	ldr	r3, [sp, #20]
	ldr	r1, [sp]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 239 11
	cmp	r2, r3
	bne	.L82
	.loc 1 241 22
	b	.L83
.L84:
	.loc 1 243 26
	ldr	r3, [sp, #16]
	adds	r3, r3, #1
	str	r3, [sp, #16]
	.loc 1 244 28
	ldr	r3, [sp, #20]
	adds	r3, r3, #1
	str	r3, [sp, #20]
.L83:
	.loc 1 241 26
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #4]
	add	r3, r3, r2
	ldrb	r2, [r3]	@ zero_extendqisi2
	.loc 1 241 48
	ldr	r3, [sp, #20]
	ldr	r1, [sp]
	add	r3, r3, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 241 29
	cmp	r2, r3
	beq	.L84
.L82:
	.loc 1 247 11
	ldr	r2, [sp, #16]
	ldr	r3, [sp, #12]
	cmp	r2, r3
	bne	.L85
	.loc 1 247 39 discriminator 1
	movs	r3, #1
	b	.L80
.L85:
	.loc 1 249 19
	movs	r3, #0
	str	r3, [sp, #16]
	.loc 1 250 19
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #8]
	cmp	r2, r3
	blt	.L78
	.loc 1 250 48 discriminator 1
	movs	r3, #0
.L80:
	.loc 1 255 1
	mov	r0, r3
	add	sp, sp, #28
.LCFI21:
	@ sp needed
	ldr	pc, [sp], #4
.LFE21:
	.size	check_for, .-check_for
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.align	2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.byte	0x4
	.4byte	.LCFI0-.LFB12
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0
	.align	2
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.byte	0x4
	.4byte	.LCFI2-.LFB13
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0xe
	.uleb128 0
	.align	2
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.byte	0x4
	.4byte	.LCFI4-.LFB14
	.byte	0xe
	.uleb128 0x8
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0xe
	.uleb128 0
	.align	2
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.byte	0x4
	.4byte	.LCFI6-.LFB15
	.byte	0xe
	.uleb128 0x8
	.byte	0x83
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.align	2
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.align	2
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.byte	0x4
	.4byte	.LCFI7-.LFB17
	.byte	0xe
	.uleb128 0x4
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI8-.LCFI7
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.4byte	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0x4
	.align	2
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.byte	0x4
	.4byte	.LCFI10-.LFB18
	.byte	0xe
	.uleb128 0x8
	.byte	0x84
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI11-.LCFI10
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI12-.LCFI11
	.byte	0xe
	.uleb128 0x8
	.align	2
.LEFDE14:
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.byte	0x4
	.4byte	.LCFI13-.LFB19
	.byte	0xe
	.uleb128 0x4
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI14-.LCFI13
	.byte	0xe
	.uleb128 0x38
	.byte	0x4
	.4byte	.LCFI15-.LCFI14
	.byte	0xe
	.uleb128 0x4
	.align	2
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.byte	0x4
	.4byte	.LCFI16-.LFB20
	.byte	0xe
	.uleb128 0x8
	.byte	0x84
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI17-.LCFI16
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI18-.LCFI17
	.byte	0xe
	.uleb128 0x8
	.align	2
.LEFDE18:
.LSFDE20:
	.4byte	.LEFDE20-.LASFDE20
.LASFDE20:
	.4byte	.Lframe0
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.byte	0x4
	.4byte	.LCFI19-.LFB21
	.byte	0xe
	.uleb128 0x4
	.byte	0x8e
	.uleb128 0x1
	.byte	0x4
	.4byte	.LCFI20-.LCFI19
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI21-.LCFI20
	.byte	0xe
	.uleb128 0x4
	.align	2
.LEFDE20:
	.text
.Letext0:
	.file 2 "C:/Program Files/SEGGER/SEGGER Embedded Studio for ARM 6.32a/include/stdio.h"
	.file 3 "C:/Program Files/SEGGER/SEGGER Embedded Studio for ARM 6.32a/include/stdint.h"
	.file 4 "F:\\nRF5_SDK_17.1.0_ddde560\\examples\\Myproject\\template_project_combine\\app_uart_ringbuff.h"
	.file 5 "C:/Program Files/SEGGER/SEGGER Embedded Studio for ARM 6.32a/include/string.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x4d6
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF815
	.byte	0xc
	.4byte	.LASF816
	.4byte	.LASF817
	.4byte	.Ldebug_ranges0+0x18
	.4byte	0
	.4byte	.Ldebug_line0
	.4byte	.Ldebug_macro0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.byte	0x4
	.4byte	0x3d
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF762
	.uleb128 0x5
	.4byte	0x36
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	.LASF763
	.uleb128 0x3
	.byte	0x4
	.4byte	0x36
	.uleb128 0x6
	.4byte	.LASF766
	.byte	0x2
	.byte	0x48
	.byte	0x1d
	.4byte	0x42
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.4byte	.LASF764
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.4byte	.LASF765
	.uleb128 0x6
	.4byte	.LASF767
	.byte	0x3
	.byte	0xd6
	.byte	0x1c
	.4byte	0x7a
	.uleb128 0x7
	.4byte	0x69
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.4byte	.LASF768
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.4byte	.LASF769
	.uleb128 0x6
	.4byte	.LASF770
	.byte	0x3
	.byte	0xd9
	.byte	0x1c
	.4byte	0x99
	.uleb128 0x7
	.4byte	0x88
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.4byte	.LASF771
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.4byte	.LASF772
	.uleb128 0x4
	.byte	0x8
	.byte	0x7
	.4byte	.LASF773
	.uleb128 0x8
	.4byte	.LASF781
	.byte	0x4
	.byte	0xf
	.byte	0x1a
	.4byte	0x94
	.uleb128 0x9
	.byte	0x7
	.byte	0x1
	.4byte	0x7a
	.byte	0x4
	.byte	0x11
	.byte	0xd
	.4byte	0xd5
	.uleb128 0xa
	.4byte	.LASF774
	.byte	0
	.uleb128 0xa
	.4byte	.LASF775
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.4byte	.LASF776
	.byte	0x4
	.byte	0x14
	.byte	0x2
	.4byte	0xba
	.uleb128 0xb
	.2byte	0x402
	.byte	0x4
	.byte	0x16
	.byte	0x9
	.4byte	0x113
	.uleb128 0xc
	.4byte	.LASF777
	.byte	0x4
	.byte	0x17
	.byte	0x16
	.4byte	0x75
	.byte	0
	.uleb128 0xc
	.4byte	.LASF778
	.byte	0x4
	.byte	0x18
	.byte	0x16
	.4byte	0x75
	.byte	0x1
	.uleb128 0xc
	.4byte	.LASF779
	.byte	0x4
	.byte	0x19
	.byte	0xd
	.4byte	0x113
	.byte	0x2
	.byte	0
	.uleb128 0xd
	.4byte	0x69
	.4byte	0x124
	.uleb128 0xe
	.4byte	0x42
	.2byte	0x3ff
	.byte	0
	.uleb128 0x6
	.4byte	.LASF780
	.byte	0x4
	.byte	0x1a
	.byte	0x2
	.4byte	0xe1
	.uleb128 0xf
	.4byte	.LASF779
	.byte	0x1
	.byte	0x2
	.byte	0x11
	.4byte	0x124
	.uleb128 0x5
	.byte	0x3
	.4byte	Buffer
	.uleb128 0xf
	.4byte	.LASF782
	.byte	0x1
	.byte	0x3
	.byte	0x12
	.4byte	0x154
	.uleb128 0x5
	.byte	0x3
	.4byte	RingBuffer
	.uleb128 0x3
	.byte	0x4
	.4byte	0x124
	.uleb128 0x10
	.4byte	0xae
	.byte	0x1
	.byte	0x4
	.byte	0x13
	.uleb128 0x5
	.byte	0x3
	.4byte	timeout
	.uleb128 0x11
	.4byte	.LASF783
	.byte	0x5
	.byte	0x59
	.byte	0xb
	.4byte	0x4f
	.4byte	0x17e
	.uleb128 0x12
	.4byte	0x30
	.byte	0
	.uleb128 0x11
	.4byte	.LASF784
	.byte	0x5
	.byte	0x41
	.byte	0xb
	.4byte	0x19e
	.4byte	0x19e
	.uleb128 0x12
	.4byte	0x19e
	.uleb128 0x12
	.4byte	0x29
	.uleb128 0x12
	.4byte	0x4f
	.byte	0
	.uleb128 0x13
	.byte	0x4
	.uleb128 0x14
	.4byte	.LASF818
	.byte	0x1
	.byte	0xe3
	.byte	0xc
	.4byte	0x29
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x21f
	.uleb128 0x15
	.ascii	"str\000"
	.byte	0x1
	.byte	0xe3
	.byte	0x1d
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x16
	.4byte	.LASF785
	.byte	0x1
	.byte	0xe3
	.byte	0x28
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x17
	.4byte	.LASF786
	.byte	0x1
	.byte	0xe5
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x17
	.4byte	.LASF787
	.byte	0x1
	.byte	0xe6
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x18
	.ascii	"idx\000"
	.byte	0x1
	.byte	0xe7
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.byte	0xe8
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x19
	.4byte	.LASF790
	.byte	0x1
	.byte	0xe9
	.byte	0x5
	.4byte	.L78
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF801
	.byte	0x1
	.byte	0xc3
	.byte	0x5
	.4byte	0x29
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x28f
	.uleb128 0x16
	.4byte	.LASF788
	.byte	0x1
	.byte	0xc3
	.byte	0x29
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x16
	.4byte	.LASF789
	.byte	0x1
	.byte	0xc3
	.byte	0x37
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x18
	.ascii	"len\000"
	.byte	0x1
	.byte	0xc5
	.byte	0xd
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.byte	0xc6
	.byte	0xd
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x18
	.ascii	"idx\000"
	.byte	0x1
	.byte	0xc7
	.byte	0xd
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x19
	.4byte	.LASF790
	.byte	0x1
	.byte	0xc8
	.byte	0x9
	.4byte	.L65
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF811
	.byte	0x1
	.byte	0x84
	.byte	0x6
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x365
	.uleb128 0x16
	.4byte	.LASF791
	.byte	0x1
	.byte	0x84
	.byte	0x32
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x16
	.4byte	.LASF792
	.byte	0x1
	.byte	0x84
	.byte	0x45
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x16
	.4byte	.LASF793
	.byte	0x1
	.byte	0x84
	.byte	0x56
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x16
	.4byte	.LASF794
	.byte	0x1
	.byte	0x84
	.byte	0x6c
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x17
	.4byte	.LASF795
	.byte	0x1
	.byte	0x86
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x17
	.4byte	.LASF796
	.byte	0x1
	.byte	0x87
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x18
	.ascii	"idx\000"
	.byte	0x1
	.byte	0x88
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.byte	0x89
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x17
	.4byte	.LASF797
	.byte	0x1
	.byte	0x8a
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x17
	.4byte	.LASF798
	.byte	0x1
	.byte	0x8b
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x19
	.4byte	.LASF799
	.byte	0x1
	.byte	0x8d
	.byte	0x5
	.4byte	.L46
	.uleb128 0x19
	.4byte	.LASF800
	.byte	0x1
	.byte	0x9e
	.byte	0x9
	.4byte	.L54
	.uleb128 0x1c
	.4byte	.Ldebug_ranges0+0
	.uleb128 0x18
	.ascii	"j\000"
	.byte	0x1
	.byte	0xb2
	.byte	0xd
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF802
	.byte	0x1
	.byte	0x73
	.byte	0x5
	.4byte	0x29
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x3c4
	.uleb128 0x16
	.4byte	.LASF788
	.byte	0x1
	.byte	0x73
	.byte	0x29
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x16
	.4byte	.LASF803
	.byte	0x1
	.byte	0x73
	.byte	0x39
	.4byte	0x69
	.uleb128 0x2
	.byte	0x91
	.sleb128 -21
	.uleb128 0x16
	.4byte	.LASF804
	.byte	0x1
	.byte	0x73
	.byte	0x4d
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x1d
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.byte	0x75
	.byte	0xe
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF805
	.byte	0x1
	.byte	0x4a
	.byte	0x5
	.4byte	0x29
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x416
	.uleb128 0x16
	.4byte	.LASF788
	.byte	0x1
	.byte	0x4a
	.byte	0x28
	.4byte	0x49
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x18
	.ascii	"len\000"
	.byte	0x1
	.byte	0x4b
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x18
	.ascii	"i\000"
	.byte	0x1
	.byte	0x4c
	.byte	0x9
	.4byte	0x29
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x19
	.4byte	.LASF790
	.byte	0x1
	.byte	0x4d
	.byte	0x5
	.4byte	.L25
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF819
	.byte	0x1
	.byte	0x3d
	.byte	0x5
	.4byte	0x29
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1f
	.4byte	.LASF813
	.byte	0x1
	.byte	0x32
	.byte	0x6
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x20
	.4byte	.LASF806
	.byte	0x1
	.byte	0x27
	.byte	0x9
	.4byte	0x69
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x468
	.uleb128 0x17
	.4byte	.LASF807
	.byte	0x1
	.byte	0x29
	.byte	0xd
	.4byte	0x69
	.uleb128 0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0x20
	.4byte	.LASF808
	.byte	0x1
	.byte	0x19
	.byte	0xb
	.4byte	0xd5
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x4a1
	.uleb128 0x17
	.4byte	.LASF809
	.byte	0x1
	.byte	0x1b
	.byte	0xf
	.4byte	0xd5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -1
	.uleb128 0x17
	.4byte	.LASF810
	.byte	0x1
	.byte	0x1c
	.byte	0xe
	.4byte	0x88
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x21
	.4byte	.LASF812
	.byte	0x1
	.byte	0xe
	.byte	0x6
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x4c7
	.uleb128 0x16
	.4byte	.LASF807
	.byte	0x1
	.byte	0xe
	.byte	0x26
	.4byte	0x69
	.uleb128 0x2
	.byte	0x91
	.sleb128 -1
	.byte	0
	.uleb128 0x22
	.4byte	.LASF814
	.byte	0x1
	.byte	0x6
	.byte	0x6
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x2134
	.uleb128 0x19
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.uleb128 0x2119
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_pubnames,"",%progbits
	.4byte	0x1ec
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x4da
	.4byte	0xc8
	.ascii	"DATA_IS_NOT_AVALABLE\000"
	.4byte	0xce
	.ascii	"DATA_IS_AVALABLE\000"
	.4byte	0x130
	.ascii	"Buffer\000"
	.4byte	0x142
	.ascii	"RingBuffer\000"
	.4byte	0x15a
	.ascii	"timeout\000"
	.4byte	0x15a
	.ascii	"timeout\000"
	.4byte	0x130
	.ascii	"Buffer\000"
	.4byte	0x142
	.ascii	"RingBuffer\000"
	.4byte	0x168
	.ascii	"strlen\000"
	.4byte	0x17e
	.ascii	"memset\000"
	.4byte	0x1a0
	.ascii	"check_for\000"
	.4byte	0x21f
	.ascii	"app_uart_ringbuffer_copy_upto\000"
	.4byte	0x28f
	.ascii	"app_uart_ringbuffer_GetDataFormBuffer\000"
	.4byte	0x365
	.ascii	"app_uart_ringbuffer_get_after\000"
	.4byte	0x3c4
	.ascii	"app_uart_ringbuffer_wait_for\000"
	.4byte	0x416
	.ascii	"app_uart_ringbuffer_peek\000"
	.4byte	0x42c
	.ascii	"app_uart_ringbuffer_reset\000"
	.4byte	0x43e
	.ascii	"app_uart_ringbuffer_get\000"
	.4byte	0x468
	.ascii	"app_uart_ringbuff_data_check\000"
	.4byte	0x4a1
	.ascii	"app_uart_ringbuffer_put\000"
	.4byte	0x4c7
	.ascii	"app_uart_ringbuffer_init\000"
	.4byte	0
	.section	.debug_pubtypes,"",%progbits
	.4byte	0xf7
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x4da
	.4byte	0x29
	.ascii	"int\000"
	.4byte	0x36
	.ascii	"char\000"
	.4byte	0x42
	.ascii	"unsigned int\000"
	.4byte	0x4f
	.ascii	"size_t\000"
	.4byte	0x5b
	.ascii	"long int\000"
	.4byte	0x62
	.ascii	"signed char\000"
	.4byte	0x7a
	.ascii	"unsigned char\000"
	.4byte	0x69
	.ascii	"uint8_t\000"
	.4byte	0x81
	.ascii	"short int\000"
	.4byte	0x99
	.ascii	"short unsigned int\000"
	.4byte	0x88
	.ascii	"uint16_t\000"
	.4byte	0xa0
	.ascii	"long long int\000"
	.4byte	0xa7
	.ascii	"long long unsigned int\000"
	.4byte	0xd5
	.ascii	"data_type\000"
	.4byte	0x124
	.ascii	"RingBuffer_type\000"
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x6c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.4byte	.LFB21
	.4byte	.LFE21-.LFB21
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB3
	.4byte	.LBE3
	.4byte	.LBB4
	.4byte	.LBE4
	.4byte	0
	.4byte	0
	.4byte	.LFB11
	.4byte	.LFE11
	.4byte	.LFB12
	.4byte	.LFE12
	.4byte	.LFB13
	.4byte	.LFE13
	.4byte	.LFB14
	.4byte	.LFE14
	.4byte	.LFB15
	.4byte	.LFE15
	.4byte	.LFB16
	.4byte	.LFE16
	.4byte	.LFB17
	.4byte	.LFE17
	.4byte	.LFB18
	.4byte	.LFE18
	.4byte	.LFB19
	.4byte	.LFE19
	.4byte	.LFB20
	.4byte	.LFE20
	.4byte	.LFB21
	.4byte	.LFE21
	.4byte	0
	.4byte	0
	.section	.debug_macro,"",%progbits
.Ldebug_macro0:
	.2byte	0x4
	.byte	0x2
	.4byte	.Ldebug_line0
	.byte	0x7
	.4byte	.Ldebug_macro2
	.byte	0x3
	.uleb128 0
	.uleb128 0x1
	.byte	0x3
	.uleb128 0x1
	.uleb128 0x4
	.byte	0x5
	.uleb128 0x2
	.4byte	.LASF493
	.file 6 "C:/Users/DELL/AppData/Local/SEGGER/SEGGER Embedded Studio/v3/packages/libraries/libcxx/include/stdio.h"
	.byte	0x3
	.uleb128 0x4
	.uleb128 0x6
	.byte	0x5
	.uleb128 0x13
	.4byte	.LASF494
	.file 7 "C:/Users/DELL/AppData/Local/SEGGER/SEGGER Embedded Studio/v3/packages/libraries/libcxx/include/__config"
	.byte	0x3
	.uleb128 0x65
	.uleb128 0x7
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF495
	.byte	0x4
	.byte	0x3
	.uleb128 0x6b
	.uleb128 0x2
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF496
	.file 8 "C:/Program Files/SEGGER/SEGGER Embedded Studio for ARM 6.32a/include/__SEGGER_RTL.h"
	.byte	0x3
	.uleb128 0x14
	.uleb128 0x8
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF497
	.file 9 "C:/Program Files/SEGGER/SEGGER Embedded Studio for ARM 6.32a/include/__SEGGER_RTL_ConfDefaults.h"
	.byte	0x3
	.uleb128 0x11
	.uleb128 0x9
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF498
	.file 10 "C:/Program Files/SEGGER/SEGGER Embedded Studio for ARM 6.32a/include/__SEGGER_RTL_Conf.h"
	.byte	0x3
	.uleb128 0xd
	.uleb128 0xa
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF499
	.file 11 "C:/Program Files/SEGGER/SEGGER Embedded Studio for ARM 6.32a/include/__SEGGER_RTL_Arm_Conf.h"
	.byte	0x3
	.uleb128 0x19
	.uleb128 0xb
	.byte	0x7
	.4byte	.Ldebug_macro3
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro4
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro5
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro6
	.byte	0x4
	.byte	0x4
	.file 12 "C:/Users/DELL/AppData/Local/SEGGER/SEGGER Embedded Studio/v3/packages/libraries/libcxx/include/stdint.h"
	.byte	0x3
	.uleb128 0x5
	.uleb128 0xc
	.byte	0x5
	.uleb128 0xf
	.4byte	.LASF697
	.byte	0x3
	.uleb128 0x7b
	.uleb128 0x3
	.byte	0x7
	.4byte	.Ldebug_macro7
	.byte	0x4
	.byte	0x4
	.file 13 "C:/Users/DELL/AppData/Local/SEGGER/SEGGER Embedded Studio/v3/packages/libraries/libcxx/include/string.h"
	.byte	0x3
	.uleb128 0x6
	.uleb128 0xd
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF758
	.byte	0x3
	.uleb128 0x3c
	.uleb128 0x5
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF759
	.byte	0x4
	.byte	0x4
	.byte	0x7
	.4byte	.Ldebug_macro8
	.byte	0x4
	.byte	0x4
	.byte	0
	.section	.debug_macro,"G",%progbits,wm4.0.399f5b1b8e316d52b9fd22ca2f6077c7,comdat
.Ldebug_macro2:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.uleb128 0
	.4byte	.LASF0
	.byte	0x5
	.uleb128 0
	.4byte	.LASF1
	.byte	0x5
	.uleb128 0
	.4byte	.LASF2
	.byte	0x5
	.uleb128 0
	.4byte	.LASF3
	.byte	0x5
	.uleb128 0
	.4byte	.LASF4
	.byte	0x5
	.uleb128 0
	.4byte	.LASF5
	.byte	0x5
	.uleb128 0
	.4byte	.LASF6
	.byte	0x5
	.uleb128 0
	.4byte	.LASF7
	.byte	0x5
	.uleb128 0
	.4byte	.LASF8
	.byte	0x5
	.uleb128 0
	.4byte	.LASF9
	.byte	0x5
	.uleb128 0
	.4byte	.LASF10
	.byte	0x5
	.uleb128 0
	.4byte	.LASF11
	.byte	0x5
	.uleb128 0
	.4byte	.LASF12
	.byte	0x5
	.uleb128 0
	.4byte	.LASF13
	.byte	0x5
	.uleb128 0
	.4byte	.LASF14
	.byte	0x5
	.uleb128 0
	.4byte	.LASF15
	.byte	0x5
	.uleb128 0
	.4byte	.LASF16
	.byte	0x5
	.uleb128 0
	.4byte	.LASF17
	.byte	0x5
	.uleb128 0
	.4byte	.LASF18
	.byte	0x5
	.uleb128 0
	.4byte	.LASF19
	.byte	0x5
	.uleb128 0
	.4byte	.LASF20
	.byte	0x5
	.uleb128 0
	.4byte	.LASF21
	.byte	0x5
	.uleb128 0
	.4byte	.LASF22
	.byte	0x5
	.uleb128 0
	.4byte	.LASF23
	.byte	0x5
	.uleb128 0
	.4byte	.LASF24
	.byte	0x5
	.uleb128 0
	.4byte	.LASF25
	.byte	0x5
	.uleb128 0
	.4byte	.LASF26
	.byte	0x5
	.uleb128 0
	.4byte	.LASF27
	.byte	0x5
	.uleb128 0
	.4byte	.LASF28
	.byte	0x5
	.uleb128 0
	.4byte	.LASF29
	.byte	0x5
	.uleb128 0
	.4byte	.LASF30
	.byte	0x5
	.uleb128 0
	.4byte	.LASF31
	.byte	0x5
	.uleb128 0
	.4byte	.LASF32
	.byte	0x5
	.uleb128 0
	.4byte	.LASF33
	.byte	0x5
	.uleb128 0
	.4byte	.LASF34
	.byte	0x5
	.uleb128 0
	.4byte	.LASF35
	.byte	0x5
	.uleb128 0
	.4byte	.LASF36
	.byte	0x5
	.uleb128 0
	.4byte	.LASF37
	.byte	0x5
	.uleb128 0
	.4byte	.LASF38
	.byte	0x5
	.uleb128 0
	.4byte	.LASF39
	.byte	0x5
	.uleb128 0
	.4byte	.LASF40
	.byte	0x5
	.uleb128 0
	.4byte	.LASF41
	.byte	0x5
	.uleb128 0
	.4byte	.LASF42
	.byte	0x5
	.uleb128 0
	.4byte	.LASF43
	.byte	0x5
	.uleb128 0
	.4byte	.LASF44
	.byte	0x5
	.uleb128 0
	.4byte	.LASF45
	.byte	0x5
	.uleb128 0
	.4byte	.LASF46
	.byte	0x5
	.uleb128 0
	.4byte	.LASF47
	.byte	0x5
	.uleb128 0
	.4byte	.LASF48
	.byte	0x5
	.uleb128 0
	.4byte	.LASF49
	.byte	0x5
	.uleb128 0
	.4byte	.LASF50
	.byte	0x5
	.uleb128 0
	.4byte	.LASF51
	.byte	0x5
	.uleb128 0
	.4byte	.LASF52
	.byte	0x5
	.uleb128 0
	.4byte	.LASF53
	.byte	0x5
	.uleb128 0
	.4byte	.LASF54
	.byte	0x5
	.uleb128 0
	.4byte	.LASF55
	.byte	0x5
	.uleb128 0
	.4byte	.LASF56
	.byte	0x5
	.uleb128 0
	.4byte	.LASF57
	.byte	0x5
	.uleb128 0
	.4byte	.LASF58
	.byte	0x5
	.uleb128 0
	.4byte	.LASF59
	.byte	0x5
	.uleb128 0
	.4byte	.LASF60
	.byte	0x5
	.uleb128 0
	.4byte	.LASF61
	.byte	0x5
	.uleb128 0
	.4byte	.LASF62
	.byte	0x5
	.uleb128 0
	.4byte	.LASF63
	.byte	0x5
	.uleb128 0
	.4byte	.LASF64
	.byte	0x5
	.uleb128 0
	.4byte	.LASF65
	.byte	0x5
	.uleb128 0
	.4byte	.LASF66
	.byte	0x5
	.uleb128 0
	.4byte	.LASF67
	.byte	0x5
	.uleb128 0
	.4byte	.LASF68
	.byte	0x5
	.uleb128 0
	.4byte	.LASF69
	.byte	0x5
	.uleb128 0
	.4byte	.LASF70
	.byte	0x5
	.uleb128 0
	.4byte	.LASF71
	.byte	0x5
	.uleb128 0
	.4byte	.LASF72
	.byte	0x5
	.uleb128 0
	.4byte	.LASF73
	.byte	0x5
	.uleb128 0
	.4byte	.LASF74
	.byte	0x5
	.uleb128 0
	.4byte	.LASF75
	.byte	0x5
	.uleb128 0
	.4byte	.LASF76
	.byte	0x5
	.uleb128 0
	.4byte	.LASF77
	.byte	0x5
	.uleb128 0
	.4byte	.LASF78
	.byte	0x5
	.uleb128 0
	.4byte	.LASF79
	.byte	0x5
	.uleb128 0
	.4byte	.LASF80
	.byte	0x5
	.uleb128 0
	.4byte	.LASF81
	.byte	0x5
	.uleb128 0
	.4byte	.LASF82
	.byte	0x5
	.uleb128 0
	.4byte	.LASF83
	.byte	0x5
	.uleb128 0
	.4byte	.LASF84
	.byte	0x5
	.uleb128 0
	.4byte	.LASF85
	.byte	0x5
	.uleb128 0
	.4byte	.LASF86
	.byte	0x5
	.uleb128 0
	.4byte	.LASF87
	.byte	0x5
	.uleb128 0
	.4byte	.LASF88
	.byte	0x5
	.uleb128 0
	.4byte	.LASF89
	.byte	0x5
	.uleb128 0
	.4byte	.LASF90
	.byte	0x5
	.uleb128 0
	.4byte	.LASF91
	.byte	0x5
	.uleb128 0
	.4byte	.LASF92
	.byte	0x5
	.uleb128 0
	.4byte	.LASF93
	.byte	0x5
	.uleb128 0
	.4byte	.LASF94
	.byte	0x5
	.uleb128 0
	.4byte	.LASF95
	.byte	0x5
	.uleb128 0
	.4byte	.LASF96
	.byte	0x5
	.uleb128 0
	.4byte	.LASF97
	.byte	0x5
	.uleb128 0
	.4byte	.LASF98
	.byte	0x5
	.uleb128 0
	.4byte	.LASF99
	.byte	0x5
	.uleb128 0
	.4byte	.LASF100
	.byte	0x5
	.uleb128 0
	.4byte	.LASF101
	.byte	0x5
	.uleb128 0
	.4byte	.LASF102
	.byte	0x5
	.uleb128 0
	.4byte	.LASF103
	.byte	0x5
	.uleb128 0
	.4byte	.LASF104
	.byte	0x5
	.uleb128 0
	.4byte	.LASF105
	.byte	0x5
	.uleb128 0
	.4byte	.LASF106
	.byte	0x5
	.uleb128 0
	.4byte	.LASF107
	.byte	0x5
	.uleb128 0
	.4byte	.LASF108
	.byte	0x5
	.uleb128 0
	.4byte	.LASF109
	.byte	0x5
	.uleb128 0
	.4byte	.LASF110
	.byte	0x5
	.uleb128 0
	.4byte	.LASF111
	.byte	0x5
	.uleb128 0
	.4byte	.LASF112
	.byte	0x5
	.uleb128 0
	.4byte	.LASF113
	.byte	0x5
	.uleb128 0
	.4byte	.LASF114
	.byte	0x5
	.uleb128 0
	.4byte	.LASF115
	.byte	0x5
	.uleb128 0
	.4byte	.LASF116
	.byte	0x5
	.uleb128 0
	.4byte	.LASF117
	.byte	0x5
	.uleb128 0
	.4byte	.LASF118
	.byte	0x5
	.uleb128 0
	.4byte	.LASF119
	.byte	0x5
	.uleb128 0
	.4byte	.LASF120
	.byte	0x5
	.uleb128 0
	.4byte	.LASF121
	.byte	0x5
	.uleb128 0
	.4byte	.LASF122
	.byte	0x5
	.uleb128 0
	.4byte	.LASF123
	.byte	0x5
	.uleb128 0
	.4byte	.LASF124
	.byte	0x5
	.uleb128 0
	.4byte	.LASF125
	.byte	0x5
	.uleb128 0
	.4byte	.LASF126
	.byte	0x5
	.uleb128 0
	.4byte	.LASF127
	.byte	0x5
	.uleb128 0
	.4byte	.LASF128
	.byte	0x5
	.uleb128 0
	.4byte	.LASF129
	.byte	0x5
	.uleb128 0
	.4byte	.LASF130
	.byte	0x5
	.uleb128 0
	.4byte	.LASF131
	.byte	0x5
	.uleb128 0
	.4byte	.LASF132
	.byte	0x5
	.uleb128 0
	.4byte	.LASF133
	.byte	0x5
	.uleb128 0
	.4byte	.LASF134
	.byte	0x5
	.uleb128 0
	.4byte	.LASF135
	.byte	0x5
	.uleb128 0
	.4byte	.LASF136
	.byte	0x5
	.uleb128 0
	.4byte	.LASF137
	.byte	0x5
	.uleb128 0
	.4byte	.LASF138
	.byte	0x5
	.uleb128 0
	.4byte	.LASF139
	.byte	0x5
	.uleb128 0
	.4byte	.LASF140
	.byte	0x5
	.uleb128 0
	.4byte	.LASF141
	.byte	0x5
	.uleb128 0
	.4byte	.LASF142
	.byte	0x5
	.uleb128 0
	.4byte	.LASF143
	.byte	0x5
	.uleb128 0
	.4byte	.LASF144
	.byte	0x5
	.uleb128 0
	.4byte	.LASF145
	.byte	0x5
	.uleb128 0
	.4byte	.LASF146
	.byte	0x5
	.uleb128 0
	.4byte	.LASF147
	.byte	0x5
	.uleb128 0
	.4byte	.LASF148
	.byte	0x5
	.uleb128 0
	.4byte	.LASF149
	.byte	0x5
	.uleb128 0
	.4byte	.LASF150
	.byte	0x5
	.uleb128 0
	.4byte	.LASF151
	.byte	0x5
	.uleb128 0
	.4byte	.LASF152
	.byte	0x5
	.uleb128 0
	.4byte	.LASF153
	.byte	0x5
	.uleb128 0
	.4byte	.LASF154
	.byte	0x5
	.uleb128 0
	.4byte	.LASF155
	.byte	0x5
	.uleb128 0
	.4byte	.LASF156
	.byte	0x5
	.uleb128 0
	.4byte	.LASF157
	.byte	0x5
	.uleb128 0
	.4byte	.LASF158
	.byte	0x5
	.uleb128 0
	.4byte	.LASF159
	.byte	0x5
	.uleb128 0
	.4byte	.LASF160
	.byte	0x5
	.uleb128 0
	.4byte	.LASF161
	.byte	0x5
	.uleb128 0
	.4byte	.LASF162
	.byte	0x5
	.uleb128 0
	.4byte	.LASF163
	.byte	0x5
	.uleb128 0
	.4byte	.LASF164
	.byte	0x5
	.uleb128 0
	.4byte	.LASF165
	.byte	0x5
	.uleb128 0
	.4byte	.LASF166
	.byte	0x5
	.uleb128 0
	.4byte	.LASF167
	.byte	0x5
	.uleb128 0
	.4byte	.LASF168
	.byte	0x5
	.uleb128 0
	.4byte	.LASF169
	.byte	0x5
	.uleb128 0
	.4byte	.LASF170
	.byte	0x5
	.uleb128 0
	.4byte	.LASF171
	.byte	0x5
	.uleb128 0
	.4byte	.LASF172
	.byte	0x5
	.uleb128 0
	.4byte	.LASF173
	.byte	0x5
	.uleb128 0
	.4byte	.LASF174
	.byte	0x5
	.uleb128 0
	.4byte	.LASF175
	.byte	0x5
	.uleb128 0
	.4byte	.LASF176
	.byte	0x5
	.uleb128 0
	.4byte	.LASF177
	.byte	0x5
	.uleb128 0
	.4byte	.LASF178
	.byte	0x5
	.uleb128 0
	.4byte	.LASF179
	.byte	0x5
	.uleb128 0
	.4byte	.LASF180
	.byte	0x5
	.uleb128 0
	.4byte	.LASF181
	.byte	0x5
	.uleb128 0
	.4byte	.LASF182
	.byte	0x5
	.uleb128 0
	.4byte	.LASF183
	.byte	0x5
	.uleb128 0
	.4byte	.LASF184
	.byte	0x5
	.uleb128 0
	.4byte	.LASF185
	.byte	0x5
	.uleb128 0
	.4byte	.LASF186
	.byte	0x5
	.uleb128 0
	.4byte	.LASF187
	.byte	0x5
	.uleb128 0
	.4byte	.LASF188
	.byte	0x5
	.uleb128 0
	.4byte	.LASF189
	.byte	0x5
	.uleb128 0
	.4byte	.LASF190
	.byte	0x5
	.uleb128 0
	.4byte	.LASF191
	.byte	0x5
	.uleb128 0
	.4byte	.LASF192
	.byte	0x5
	.uleb128 0
	.4byte	.LASF193
	.byte	0x5
	.uleb128 0
	.4byte	.LASF194
	.byte	0x5
	.uleb128 0
	.4byte	.LASF195
	.byte	0x5
	.uleb128 0
	.4byte	.LASF196
	.byte	0x5
	.uleb128 0
	.4byte	.LASF197
	.byte	0x5
	.uleb128 0
	.4byte	.LASF198
	.byte	0x5
	.uleb128 0
	.4byte	.LASF199
	.byte	0x5
	.uleb128 0
	.4byte	.LASF200
	.byte	0x5
	.uleb128 0
	.4byte	.LASF201
	.byte	0x5
	.uleb128 0
	.4byte	.LASF202
	.byte	0x5
	.uleb128 0
	.4byte	.LASF203
	.byte	0x5
	.uleb128 0
	.4byte	.LASF204
	.byte	0x5
	.uleb128 0
	.4byte	.LASF205
	.byte	0x5
	.uleb128 0
	.4byte	.LASF206
	.byte	0x5
	.uleb128 0
	.4byte	.LASF207
	.byte	0x5
	.uleb128 0
	.4byte	.LASF208
	.byte	0x5
	.uleb128 0
	.4byte	.LASF209
	.byte	0x5
	.uleb128 0
	.4byte	.LASF210
	.byte	0x5
	.uleb128 0
	.4byte	.LASF211
	.byte	0x5
	.uleb128 0
	.4byte	.LASF212
	.byte	0x5
	.uleb128 0
	.4byte	.LASF213
	.byte	0x5
	.uleb128 0
	.4byte	.LASF214
	.byte	0x5
	.uleb128 0
	.4byte	.LASF215
	.byte	0x5
	.uleb128 0
	.4byte	.LASF216
	.byte	0x5
	.uleb128 0
	.4byte	.LASF217
	.byte	0x5
	.uleb128 0
	.4byte	.LASF218
	.byte	0x5
	.uleb128 0
	.4byte	.LASF219
	.byte	0x5
	.uleb128 0
	.4byte	.LASF220
	.byte	0x5
	.uleb128 0
	.4byte	.LASF221
	.byte	0x5
	.uleb128 0
	.4byte	.LASF222
	.byte	0x5
	.uleb128 0
	.4byte	.LASF223
	.byte	0x5
	.uleb128 0
	.4byte	.LASF224
	.byte	0x5
	.uleb128 0
	.4byte	.LASF225
	.byte	0x5
	.uleb128 0
	.4byte	.LASF226
	.byte	0x5
	.uleb128 0
	.4byte	.LASF227
	.byte	0x5
	.uleb128 0
	.4byte	.LASF228
	.byte	0x5
	.uleb128 0
	.4byte	.LASF229
	.byte	0x5
	.uleb128 0
	.4byte	.LASF230
	.byte	0x5
	.uleb128 0
	.4byte	.LASF231
	.byte	0x5
	.uleb128 0
	.4byte	.LASF232
	.byte	0x5
	.uleb128 0
	.4byte	.LASF233
	.byte	0x5
	.uleb128 0
	.4byte	.LASF234
	.byte	0x5
	.uleb128 0
	.4byte	.LASF235
	.byte	0x5
	.uleb128 0
	.4byte	.LASF236
	.byte	0x5
	.uleb128 0
	.4byte	.LASF237
	.byte	0x5
	.uleb128 0
	.4byte	.LASF238
	.byte	0x5
	.uleb128 0
	.4byte	.LASF239
	.byte	0x5
	.uleb128 0
	.4byte	.LASF240
	.byte	0x5
	.uleb128 0
	.4byte	.LASF241
	.byte	0x5
	.uleb128 0
	.4byte	.LASF242
	.byte	0x5
	.uleb128 0
	.4byte	.LASF243
	.byte	0x5
	.uleb128 0
	.4byte	.LASF244
	.byte	0x5
	.uleb128 0
	.4byte	.LASF245
	.byte	0x5
	.uleb128 0
	.4byte	.LASF246
	.byte	0x5
	.uleb128 0
	.4byte	.LASF247
	.byte	0x5
	.uleb128 0
	.4byte	.LASF248
	.byte	0x5
	.uleb128 0
	.4byte	.LASF249
	.byte	0x5
	.uleb128 0
	.4byte	.LASF250
	.byte	0x5
	.uleb128 0
	.4byte	.LASF251
	.byte	0x5
	.uleb128 0
	.4byte	.LASF252
	.byte	0x5
	.uleb128 0
	.4byte	.LASF253
	.byte	0x5
	.uleb128 0
	.4byte	.LASF254
	.byte	0x5
	.uleb128 0
	.4byte	.LASF255
	.byte	0x5
	.uleb128 0
	.4byte	.LASF256
	.byte	0x5
	.uleb128 0
	.4byte	.LASF257
	.byte	0x5
	.uleb128 0
	.4byte	.LASF258
	.byte	0x5
	.uleb128 0
	.4byte	.LASF259
	.byte	0x5
	.uleb128 0
	.4byte	.LASF260
	.byte	0x5
	.uleb128 0
	.4byte	.LASF261
	.byte	0x5
	.uleb128 0
	.4byte	.LASF262
	.byte	0x5
	.uleb128 0
	.4byte	.LASF263
	.byte	0x5
	.uleb128 0
	.4byte	.LASF264
	.byte	0x5
	.uleb128 0
	.4byte	.LASF265
	.byte	0x5
	.uleb128 0
	.4byte	.LASF266
	.byte	0x5
	.uleb128 0
	.4byte	.LASF267
	.byte	0x5
	.uleb128 0
	.4byte	.LASF268
	.byte	0x5
	.uleb128 0
	.4byte	.LASF269
	.byte	0x5
	.uleb128 0
	.4byte	.LASF270
	.byte	0x5
	.uleb128 0
	.4byte	.LASF271
	.byte	0x5
	.uleb128 0
	.4byte	.LASF272
	.byte	0x5
	.uleb128 0
	.4byte	.LASF273
	.byte	0x5
	.uleb128 0
	.4byte	.LASF274
	.byte	0x5
	.uleb128 0
	.4byte	.LASF275
	.byte	0x5
	.uleb128 0
	.4byte	.LASF276
	.byte	0x5
	.uleb128 0
	.4byte	.LASF277
	.byte	0x5
	.uleb128 0
	.4byte	.LASF278
	.byte	0x5
	.uleb128 0
	.4byte	.LASF279
	.byte	0x5
	.uleb128 0
	.4byte	.LASF280
	.byte	0x5
	.uleb128 0
	.4byte	.LASF281
	.byte	0x5
	.uleb128 0
	.4byte	.LASF282
	.byte	0x5
	.uleb128 0
	.4byte	.LASF283
	.byte	0x5
	.uleb128 0
	.4byte	.LASF284
	.byte	0x5
	.uleb128 0
	.4byte	.LASF285
	.byte	0x5
	.uleb128 0
	.4byte	.LASF286
	.byte	0x5
	.uleb128 0
	.4byte	.LASF287
	.byte	0x5
	.uleb128 0
	.4byte	.LASF288
	.byte	0x5
	.uleb128 0
	.4byte	.LASF289
	.byte	0x5
	.uleb128 0
	.4byte	.LASF290
	.byte	0x5
	.uleb128 0
	.4byte	.LASF291
	.byte	0x5
	.uleb128 0
	.4byte	.LASF292
	.byte	0x5
	.uleb128 0
	.4byte	.LASF293
	.byte	0x5
	.uleb128 0
	.4byte	.LASF294
	.byte	0x5
	.uleb128 0
	.4byte	.LASF295
	.byte	0x5
	.uleb128 0
	.4byte	.LASF296
	.byte	0x5
	.uleb128 0
	.4byte	.LASF297
	.byte	0x5
	.uleb128 0
	.4byte	.LASF298
	.byte	0x5
	.uleb128 0
	.4byte	.LASF299
	.byte	0x5
	.uleb128 0
	.4byte	.LASF300
	.byte	0x5
	.uleb128 0
	.4byte	.LASF301
	.byte	0x5
	.uleb128 0
	.4byte	.LASF302
	.byte	0x5
	.uleb128 0
	.4byte	.LASF303
	.byte	0x5
	.uleb128 0
	.4byte	.LASF304
	.byte	0x5
	.uleb128 0
	.4byte	.LASF305
	.byte	0x5
	.uleb128 0
	.4byte	.LASF306
	.byte	0x5
	.uleb128 0
	.4byte	.LASF307
	.byte	0x5
	.uleb128 0
	.4byte	.LASF308
	.byte	0x5
	.uleb128 0
	.4byte	.LASF309
	.byte	0x5
	.uleb128 0
	.4byte	.LASF310
	.byte	0x5
	.uleb128 0
	.4byte	.LASF311
	.byte	0x5
	.uleb128 0
	.4byte	.LASF312
	.byte	0x5
	.uleb128 0
	.4byte	.LASF313
	.byte	0x5
	.uleb128 0
	.4byte	.LASF314
	.byte	0x5
	.uleb128 0
	.4byte	.LASF315
	.byte	0x5
	.uleb128 0
	.4byte	.LASF316
	.byte	0x5
	.uleb128 0
	.4byte	.LASF317
	.byte	0x5
	.uleb128 0
	.4byte	.LASF318
	.byte	0x5
	.uleb128 0
	.4byte	.LASF319
	.byte	0x5
	.uleb128 0
	.4byte	.LASF320
	.byte	0x5
	.uleb128 0
	.4byte	.LASF321
	.byte	0x5
	.uleb128 0
	.4byte	.LASF322
	.byte	0x5
	.uleb128 0
	.4byte	.LASF323
	.byte	0x5
	.uleb128 0
	.4byte	.LASF324
	.byte	0x5
	.uleb128 0
	.4byte	.LASF325
	.byte	0x5
	.uleb128 0
	.4byte	.LASF326
	.byte	0x5
	.uleb128 0
	.4byte	.LASF327
	.byte	0x5
	.uleb128 0
	.4byte	.LASF328
	.byte	0x5
	.uleb128 0
	.4byte	.LASF329
	.byte	0x5
	.uleb128 0
	.4byte	.LASF330
	.byte	0x5
	.uleb128 0
	.4byte	.LASF331
	.byte	0x5
	.uleb128 0
	.4byte	.LASF332
	.byte	0x5
	.uleb128 0
	.4byte	.LASF333
	.byte	0x5
	.uleb128 0
	.4byte	.LASF334
	.byte	0x5
	.uleb128 0
	.4byte	.LASF335
	.byte	0x5
	.uleb128 0
	.4byte	.LASF336
	.byte	0x5
	.uleb128 0
	.4byte	.LASF337
	.byte	0x5
	.uleb128 0
	.4byte	.LASF338
	.byte	0x5
	.uleb128 0
	.4byte	.LASF339
	.byte	0x5
	.uleb128 0
	.4byte	.LASF340
	.byte	0x5
	.uleb128 0
	.4byte	.LASF341
	.byte	0x5
	.uleb128 0
	.4byte	.LASF342
	.byte	0x5
	.uleb128 0
	.4byte	.LASF343
	.byte	0x5
	.uleb128 0
	.4byte	.LASF344
	.byte	0x5
	.uleb128 0
	.4byte	.LASF345
	.byte	0x5
	.uleb128 0
	.4byte	.LASF346
	.byte	0x5
	.uleb128 0
	.4byte	.LASF347
	.byte	0x5
	.uleb128 0
	.4byte	.LASF348
	.byte	0x5
	.uleb128 0
	.4byte	.LASF349
	.byte	0x5
	.uleb128 0
	.4byte	.LASF350
	.byte	0x5
	.uleb128 0
	.4byte	.LASF351
	.byte	0x5
	.uleb128 0
	.4byte	.LASF352
	.byte	0x5
	.uleb128 0
	.4byte	.LASF353
	.byte	0x5
	.uleb128 0
	.4byte	.LASF354
	.byte	0x5
	.uleb128 0
	.4byte	.LASF355
	.byte	0x5
	.uleb128 0
	.4byte	.LASF356
	.byte	0x5
	.uleb128 0
	.4byte	.LASF357
	.byte	0x5
	.uleb128 0
	.4byte	.LASF358
	.byte	0x5
	.uleb128 0
	.4byte	.LASF359
	.byte	0x5
	.uleb128 0
	.4byte	.LASF360
	.byte	0x5
	.uleb128 0
	.4byte	.LASF361
	.byte	0x5
	.uleb128 0
	.4byte	.LASF362
	.byte	0x5
	.uleb128 0
	.4byte	.LASF363
	.byte	0x5
	.uleb128 0
	.4byte	.LASF364
	.byte	0x5
	.uleb128 0
	.4byte	.LASF365
	.byte	0x5
	.uleb128 0
	.4byte	.LASF366
	.byte	0x5
	.uleb128 0
	.4byte	.LASF367
	.byte	0x5
	.uleb128 0
	.4byte	.LASF368
	.byte	0x5
	.uleb128 0
	.4byte	.LASF369
	.byte	0x5
	.uleb128 0
	.4byte	.LASF370
	.byte	0x5
	.uleb128 0
	.4byte	.LASF371
	.byte	0x5
	.uleb128 0
	.4byte	.LASF372
	.byte	0x5
	.uleb128 0
	.4byte	.LASF373
	.byte	0x5
	.uleb128 0
	.4byte	.LASF374
	.byte	0x5
	.uleb128 0
	.4byte	.LASF375
	.byte	0x5
	.uleb128 0
	.4byte	.LASF376
	.byte	0x5
	.uleb128 0
	.4byte	.LASF377
	.byte	0x5
	.uleb128 0
	.4byte	.LASF378
	.byte	0x5
	.uleb128 0
	.4byte	.LASF379
	.byte	0x5
	.uleb128 0
	.4byte	.LASF380
	.byte	0x5
	.uleb128 0
	.4byte	.LASF381
	.byte	0x5
	.uleb128 0
	.4byte	.LASF382
	.byte	0x5
	.uleb128 0
	.4byte	.LASF383
	.byte	0x5
	.uleb128 0
	.4byte	.LASF384
	.byte	0x5
	.uleb128 0
	.4byte	.LASF385
	.byte	0x5
	.uleb128 0
	.4byte	.LASF386
	.byte	0x5
	.uleb128 0
	.4byte	.LASF387
	.byte	0x5
	.uleb128 0
	.4byte	.LASF388
	.byte	0x5
	.uleb128 0
	.4byte	.LASF389
	.byte	0x5
	.uleb128 0
	.4byte	.LASF390
	.byte	0x5
	.uleb128 0
	.4byte	.LASF391
	.byte	0x5
	.uleb128 0
	.4byte	.LASF392
	.byte	0x5
	.uleb128 0
	.4byte	.LASF393
	.byte	0x5
	.uleb128 0
	.4byte	.LASF394
	.byte	0x5
	.uleb128 0
	.4byte	.LASF395
	.byte	0x5
	.uleb128 0
	.4byte	.LASF396
	.byte	0x5
	.uleb128 0
	.4byte	.LASF397
	.byte	0x5
	.uleb128 0
	.4byte	.LASF398
	.byte	0x5
	.uleb128 0
	.4byte	.LASF399
	.byte	0x5
	.uleb128 0
	.4byte	.LASF400
	.byte	0x5
	.uleb128 0
	.4byte	.LASF401
	.byte	0x5
	.uleb128 0
	.4byte	.LASF402
	.byte	0x5
	.uleb128 0
	.4byte	.LASF403
	.byte	0x5
	.uleb128 0
	.4byte	.LASF404
	.byte	0x6
	.uleb128 0
	.4byte	.LASF405
	.byte	0x5
	.uleb128 0
	.4byte	.LASF406
	.byte	0x6
	.uleb128 0
	.4byte	.LASF407
	.byte	0x6
	.uleb128 0
	.4byte	.LASF408
	.byte	0x6
	.uleb128 0
	.4byte	.LASF409
	.byte	0x6
	.uleb128 0
	.4byte	.LASF410
	.byte	0x5
	.uleb128 0
	.4byte	.LASF411
	.byte	0x6
	.uleb128 0
	.4byte	.LASF412
	.byte	0x6
	.uleb128 0
	.4byte	.LASF413
	.byte	0x6
	.uleb128 0
	.4byte	.LASF414
	.byte	0x5
	.uleb128 0
	.4byte	.LASF415
	.byte	0x5
	.uleb128 0
	.4byte	.LASF416
	.byte	0x6
	.uleb128 0
	.4byte	.LASF417
	.byte	0x5
	.uleb128 0
	.4byte	.LASF418
	.byte	0x5
	.uleb128 0
	.4byte	.LASF419
	.byte	0x5
	.uleb128 0
	.4byte	.LASF420
	.byte	0x6
	.uleb128 0
	.4byte	.LASF421
	.byte	0x5
	.uleb128 0
	.4byte	.LASF422
	.byte	0x5
	.uleb128 0
	.4byte	.LASF423
	.byte	0x6
	.uleb128 0
	.4byte	.LASF424
	.byte	0x5
	.uleb128 0
	.4byte	.LASF425
	.byte	0x5
	.uleb128 0
	.4byte	.LASF426
	.byte	0x5
	.uleb128 0
	.4byte	.LASF427
	.byte	0x5
	.uleb128 0
	.4byte	.LASF428
	.byte	0x5
	.uleb128 0
	.4byte	.LASF429
	.byte	0x5
	.uleb128 0
	.4byte	.LASF430
	.byte	0x6
	.uleb128 0
	.4byte	.LASF431
	.byte	0x5
	.uleb128 0
	.4byte	.LASF432
	.byte	0x5
	.uleb128 0
	.4byte	.LASF433
	.byte	0x5
	.uleb128 0
	.4byte	.LASF434
	.byte	0x6
	.uleb128 0
	.4byte	.LASF435
	.byte	0x5
	.uleb128 0
	.4byte	.LASF436
	.byte	0x5
	.uleb128 0
	.4byte	.LASF437
	.byte	0x6
	.uleb128 0
	.4byte	.LASF438
	.byte	0x5
	.uleb128 0
	.4byte	.LASF439
	.byte	0x6
	.uleb128 0
	.4byte	.LASF440
	.byte	0x6
	.uleb128 0
	.4byte	.LASF441
	.byte	0x6
	.uleb128 0
	.4byte	.LASF442
	.byte	0x5
	.uleb128 0
	.4byte	.LASF443
	.byte	0x6
	.uleb128 0
	.4byte	.LASF444
	.byte	0x6
	.uleb128 0
	.4byte	.LASF445
	.byte	0x6
	.uleb128 0
	.4byte	.LASF446
	.byte	0x5
	.uleb128 0
	.4byte	.LASF447
	.byte	0x5
	.uleb128 0
	.4byte	.LASF448
	.byte	0x5
	.uleb128 0
	.4byte	.LASF449
	.byte	0x5
	.uleb128 0
	.4byte	.LASF450
	.byte	0x6
	.uleb128 0
	.4byte	.LASF451
	.byte	0x5
	.uleb128 0
	.4byte	.LASF452
	.byte	0x5
	.uleb128 0
	.4byte	.LASF453
	.byte	0x5
	.uleb128 0
	.4byte	.LASF454
	.byte	0x6
	.uleb128 0
	.4byte	.LASF455
	.byte	0x5
	.uleb128 0
	.4byte	.LASF456
	.byte	0x6
	.uleb128 0
	.4byte	.LASF457
	.byte	0x6
	.uleb128 0
	.4byte	.LASF458
	.byte	0x6
	.uleb128 0
	.4byte	.LASF459
	.byte	0x6
	.uleb128 0
	.4byte	.LASF460
	.byte	0x6
	.uleb128 0
	.4byte	.LASF461
	.byte	0x6
	.uleb128 0
	.4byte	.LASF462
	.byte	0x5
	.uleb128 0
	.4byte	.LASF463
	.byte	0x5
	.uleb128 0
	.4byte	.LASF464
	.byte	0x5
	.uleb128 0
	.4byte	.LASF465
	.byte	0x5
	.uleb128 0
	.4byte	.LASF448
	.byte	0x5
	.uleb128 0
	.4byte	.LASF466
	.byte	0x5
	.uleb128 0
	.4byte	.LASF467
	.byte	0x5
	.uleb128 0
	.4byte	.LASF468
	.byte	0x5
	.uleb128 0
	.4byte	.LASF469
	.byte	0x5
	.uleb128 0
	.4byte	.LASF470
	.byte	0x5
	.uleb128 0
	.4byte	.LASF471
	.byte	0x5
	.uleb128 0
	.4byte	.LASF472
	.byte	0x5
	.uleb128 0
	.4byte	.LASF473
	.byte	0x5
	.uleb128 0
	.4byte	.LASF474
	.byte	0x5
	.uleb128 0
	.4byte	.LASF475
	.byte	0x5
	.uleb128 0
	.4byte	.LASF476
	.byte	0x5
	.uleb128 0
	.4byte	.LASF477
	.byte	0x5
	.uleb128 0
	.4byte	.LASF478
	.byte	0x5
	.uleb128 0
	.4byte	.LASF479
	.byte	0x5
	.uleb128 0
	.4byte	.LASF480
	.byte	0x5
	.uleb128 0
	.4byte	.LASF481
	.byte	0x5
	.uleb128 0
	.4byte	.LASF482
	.byte	0x5
	.uleb128 0
	.4byte	.LASF483
	.byte	0x5
	.uleb128 0
	.4byte	.LASF484
	.byte	0x5
	.uleb128 0
	.4byte	.LASF485
	.byte	0x5
	.uleb128 0
	.4byte	.LASF486
	.byte	0x5
	.uleb128 0
	.4byte	.LASF487
	.byte	0x5
	.uleb128 0
	.4byte	.LASF488
	.byte	0x5
	.uleb128 0
	.4byte	.LASF489
	.byte	0x5
	.uleb128 0
	.4byte	.LASF490
	.byte	0x5
	.uleb128 0
	.4byte	.LASF491
	.byte	0x5
	.uleb128 0
	.4byte	.LASF492
	.byte	0
	.section	.debug_macro,"G",%progbits,wm4.__SEGGER_RTL_Arm_Conf.h.11.07484ddfe2bfa2dc5a9595d705212976,comdat
.Ldebug_macro3:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF500
	.byte	0x5
	.uleb128 0x27
	.4byte	.LASF501
	.byte	0x5
	.uleb128 0x28
	.4byte	.LASF502
	.byte	0x5
	.uleb128 0x29
	.4byte	.LASF503
	.byte	0x5
	.uleb128 0x36
	.4byte	.LASF504
	.byte	0x5
	.uleb128 0x3e
	.4byte	.LASF505
	.byte	0x5
	.uleb128 0x46
	.4byte	.LASF506
	.byte	0x5
	.uleb128 0x51
	.4byte	.LASF507
	.byte	0x5
	.uleb128 0x59
	.4byte	.LASF508
	.byte	0x5
	.uleb128 0x5f
	.4byte	.LASF509
	.byte	0x5
	.uleb128 0x67
	.4byte	.LASF510
	.byte	0x5
	.uleb128 0x6e
	.4byte	.LASF511
	.byte	0x5
	.uleb128 0x76
	.4byte	.LASF512
	.byte	0x5
	.uleb128 0x77
	.4byte	.LASF513
	.byte	0x5
	.uleb128 0x7e
	.4byte	.LASF514
	.byte	0x5
	.uleb128 0x84
	.4byte	.LASF515
	.byte	0x5
	.uleb128 0x8f
	.4byte	.LASF516
	.byte	0x5
	.uleb128 0xa1
	.4byte	.LASF517
	.byte	0x5
	.uleb128 0xbb
	.4byte	.LASF518
	.byte	0x5
	.uleb128 0xc2
	.4byte	.LASF519
	.byte	0x5
	.uleb128 0xcb
	.4byte	.LASF520
	.byte	0x5
	.uleb128 0xef
	.4byte	.LASF521
	.byte	0x5
	.uleb128 0x115
	.4byte	.LASF522
	.byte	0x5
	.uleb128 0x11e
	.4byte	.LASF523
	.byte	0x5
	.uleb128 0x125
	.4byte	.LASF524
	.byte	0x5
	.uleb128 0x12c
	.4byte	.LASF525
	.byte	0x5
	.uleb128 0x134
	.4byte	.LASF526
	.byte	0x5
	.uleb128 0x13c
	.4byte	.LASF527
	.byte	0x5
	.uleb128 0x14a
	.4byte	.LASF528
	.byte	0x5
	.uleb128 0x157
	.4byte	.LASF529
	.byte	0x5
	.uleb128 0x158
	.4byte	.LASF530
	.byte	0x5
	.uleb128 0x15f
	.4byte	.LASF531
	.byte	0x5
	.uleb128 0x16d
	.4byte	.LASF532
	.byte	0x5
	.uleb128 0x172
	.4byte	.LASF533
	.byte	0x5
	.uleb128 0x176
	.4byte	.LASF534
	.byte	0x5
	.uleb128 0x17f
	.4byte	.LASF535
	.byte	0x5
	.uleb128 0x187
	.4byte	.LASF536
	.byte	0x5
	.uleb128 0x19d
	.4byte	.LASF537
	.byte	0x5
	.uleb128 0x1b5
	.4byte	.LASF538
	.byte	0x5
	.uleb128 0x1da
	.4byte	.LASF539
	.byte	0x5
	.uleb128 0x201
	.4byte	.LASF540
	.byte	0x5
	.uleb128 0x207
	.4byte	.LASF541
	.byte	0x5
	.uleb128 0x20d
	.4byte	.LASF542
	.byte	0x5
	.uleb128 0x213
	.4byte	.LASF543
	.byte	0x5
	.uleb128 0x219
	.4byte	.LASF544
	.byte	0x5
	.uleb128 0x21f
	.4byte	.LASF545
	.byte	0x5
	.uleb128 0x225
	.4byte	.LASF546
	.byte	0x5
	.uleb128 0x22b
	.4byte	.LASF547
	.byte	0x5
	.uleb128 0x231
	.4byte	.LASF548
	.byte	0x5
	.uleb128 0x237
	.4byte	.LASF549
	.byte	0x5
	.uleb128 0x23d
	.4byte	.LASF550
	.byte	0x5
	.uleb128 0x243
	.4byte	.LASF551
	.byte	0x5
	.uleb128 0x249
	.4byte	.LASF552
	.byte	0x5
	.uleb128 0x250
	.4byte	.LASF553
	.byte	0x5
	.uleb128 0x255
	.4byte	.LASF554
	.byte	0x5
	.uleb128 0x25d
	.4byte	.LASF555
	.byte	0x5
	.uleb128 0x260
	.4byte	.LASF556
	.byte	0x5
	.uleb128 0x263
	.4byte	.LASF557
	.byte	0x5
	.uleb128 0x268
	.4byte	.LASF558
	.byte	0x5
	.uleb128 0x26f
	.4byte	.LASF559
	.byte	0x5
	.uleb128 0x275
	.4byte	.LASF560
	.byte	0x5
	.uleb128 0x27a
	.4byte	.LASF561
	.byte	0x5
	.uleb128 0x280
	.4byte	.LASF562
	.byte	0x5
	.uleb128 0x281
	.4byte	.LASF563
	.byte	0x5
	.uleb128 0x288
	.4byte	.LASF564
	.byte	0x5
	.uleb128 0x289
	.4byte	.LASF565
	.byte	0x5
	.uleb128 0x28a
	.4byte	.LASF566
	.byte	0x5
	.uleb128 0x28f
	.4byte	.LASF567
	.byte	0x5
	.uleb128 0x290
	.4byte	.LASF568
	.byte	0x5
	.uleb128 0x291
	.4byte	.LASF569
	.byte	0x5
	.uleb128 0x292
	.4byte	.LASF570
	.byte	0x5
	.uleb128 0x293
	.4byte	.LASF571
	.byte	0x5
	.uleb128 0x294
	.4byte	.LASF572
	.byte	0x5
	.uleb128 0x295
	.4byte	.LASF573
	.byte	0x5
	.uleb128 0x296
	.4byte	.LASF574
	.byte	0x5
	.uleb128 0x297
	.4byte	.LASF575
	.byte	0x5
	.uleb128 0x298
	.4byte	.LASF576
	.byte	0x5
	.uleb128 0x299
	.4byte	.LASF577
	.byte	0x5
	.uleb128 0x355
	.4byte	.LASF578
	.byte	0x5
	.uleb128 0x364
	.4byte	.LASF579
	.byte	0x5
	.uleb128 0x365
	.4byte	.LASF580
	.byte	0x5
	.uleb128 0x366
	.4byte	.LASF581
	.byte	0x5
	.uleb128 0x367
	.4byte	.LASF582
	.byte	0x5
	.uleb128 0x368
	.4byte	.LASF583
	.byte	0x5
	.uleb128 0x369
	.4byte	.LASF584
	.byte	0x5
	.uleb128 0x36b
	.4byte	.LASF585
	.byte	0x5
	.uleb128 0x36c
	.4byte	.LASF586
	.byte	0x5
	.uleb128 0x36d
	.4byte	.LASF587
	.byte	0
	.section	.debug_macro,"G",%progbits,wm4.__SEGGER_RTL_ConfDefaults.h.22.24d3414578738a0ad260ab85a6e5bd10,comdat
.Ldebug_macro4:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x16
	.4byte	.LASF588
	.byte	0x5
	.uleb128 0x17
	.4byte	.LASF589
	.byte	0x5
	.uleb128 0x18
	.4byte	.LASF590
	.byte	0x5
	.uleb128 0x1a
	.4byte	.LASF591
	.byte	0x5
	.uleb128 0x1b
	.4byte	.LASF592
	.byte	0x5
	.uleb128 0x1c
	.4byte	.LASF593
	.byte	0x5
	.uleb128 0x1e
	.4byte	.LASF594
	.byte	0x5
	.uleb128 0x1f
	.4byte	.LASF595
	.byte	0x5
	.uleb128 0x20
	.4byte	.LASF596
	.byte	0x5
	.uleb128 0x2d
	.4byte	.LASF597
	.byte	0x5
	.uleb128 0x31
	.4byte	.LASF598
	.byte	0x5
	.uleb128 0x35
	.4byte	.LASF599
	.byte	0x5
	.uleb128 0x3d
	.4byte	.LASF600
	.byte	0x5
	.uleb128 0x45
	.4byte	.LASF601
	.byte	0x5
	.uleb128 0x49
	.4byte	.LASF602
	.byte	0x5
	.uleb128 0x75
	.4byte	.LASF603
	.byte	0x5
	.uleb128 0x76
	.4byte	.LASF604
	.byte	0x5
	.uleb128 0x77
	.4byte	.LASF605
	.byte	0x5
	.uleb128 0x78
	.4byte	.LASF606
	.byte	0x5
	.uleb128 0x79
	.4byte	.LASF607
	.byte	0x5
	.uleb128 0x7a
	.4byte	.LASF608
	.byte	0x5
	.uleb128 0x7b
	.4byte	.LASF609
	.byte	0x5
	.uleb128 0x7c
	.4byte	.LASF610
	.byte	0x5
	.uleb128 0x7d
	.4byte	.LASF611
	.byte	0x5
	.uleb128 0x7e
	.4byte	.LASF612
	.byte	0x5
	.uleb128 0x7f
	.4byte	.LASF613
	.byte	0x5
	.uleb128 0x80
	.4byte	.LASF614
	.byte	0x5
	.uleb128 0x81
	.4byte	.LASF615
	.byte	0x5
	.uleb128 0x82
	.4byte	.LASF616
	.byte	0x5
	.uleb128 0x83
	.4byte	.LASF617
	.byte	0x5
	.uleb128 0x84
	.4byte	.LASF618
	.byte	0x5
	.uleb128 0x85
	.4byte	.LASF619
	.byte	0x5
	.uleb128 0x87
	.4byte	.LASF620
	.byte	0x5
	.uleb128 0x88
	.4byte	.LASF621
	.byte	0x5
	.uleb128 0x89
	.4byte	.LASF622
	.byte	0x5
	.uleb128 0x8c
	.4byte	.LASF623
	.byte	0x5
	.uleb128 0x8d
	.4byte	.LASF624
	.byte	0x5
	.uleb128 0x8e
	.4byte	.LASF625
	.byte	0x5
	.uleb128 0x8f
	.4byte	.LASF626
	.byte	0x5
	.uleb128 0x90
	.4byte	.LASF627
	.byte	0x5
	.uleb128 0xca
	.4byte	.LASF628
	.byte	0x5
	.uleb128 0xd4
	.4byte	.LASF629
	.byte	0x5
	.uleb128 0xd8
	.4byte	.LASF630
	.byte	0x5
	.uleb128 0xdc
	.4byte	.LASF631
	.byte	0x5
	.uleb128 0xe0
	.4byte	.LASF632
	.byte	0x5
	.uleb128 0xe4
	.4byte	.LASF633
	.byte	0x5
	.uleb128 0xe8
	.4byte	.LASF634
	.byte	0x6
	.uleb128 0xec
	.4byte	.LASF635
	.byte	0x5
	.uleb128 0xed
	.4byte	.LASF630
	.byte	0x6
	.uleb128 0xee
	.4byte	.LASF636
	.byte	0x5
	.uleb128 0xef
	.4byte	.LASF633
	.byte	0x5
	.uleb128 0xf3
	.4byte	.LASF637
	.byte	0x5
	.uleb128 0xf7
	.4byte	.LASF638
	.byte	0x5
	.uleb128 0xfb
	.4byte	.LASF639
	.byte	0x5
	.uleb128 0xff
	.4byte	.LASF640
	.byte	0x5
	.uleb128 0x107
	.4byte	.LASF641
	.byte	0x5
	.uleb128 0x10b
	.4byte	.LASF642
	.byte	0x5
	.uleb128 0x12b
	.4byte	.LASF643
	.byte	0x5
	.uleb128 0x146
	.4byte	.LASF644
	.byte	0x5
	.uleb128 0x14e
	.4byte	.LASF645
	.byte	0x5
	.uleb128 0x156
	.4byte	.LASF646
	.byte	0x5
	.uleb128 0x15e
	.4byte	.LASF647
	.byte	0x5
	.uleb128 0x163
	.4byte	.LASF648
	.byte	0x5
	.uleb128 0x164
	.4byte	.LASF649
	.byte	0x5
	.uleb128 0x18f
	.4byte	.LASF650
	.byte	0x5
	.uleb128 0x193
	.4byte	.LASF651
	.byte	0x5
	.uleb128 0x1a6
	.4byte	.LASF652
	.byte	0x5
	.uleb128 0x1b8
	.4byte	.LASF653
	.byte	0x5
	.uleb128 0x1bc
	.4byte	.LASF654
	.byte	0x5
	.uleb128 0x1c0
	.4byte	.LASF655
	.byte	0x5
	.uleb128 0x1c4
	.4byte	.LASF656
	.byte	0x5
	.uleb128 0x1d1
	.4byte	.LASF657
	.byte	0x5
	.uleb128 0x1d2
	.4byte	.LASF658
	.byte	0x5
	.uleb128 0x1da
	.4byte	.LASF659
	.byte	0x5
	.uleb128 0x1de
	.4byte	.LASF660
	.byte	0x5
	.uleb128 0x1e2
	.4byte	.LASF661
	.byte	0x5
	.uleb128 0x1e5
	.4byte	.LASF662
	.byte	0x5
	.uleb128 0x1e8
	.4byte	.LASF663
	.byte	0x5
	.uleb128 0x1eb
	.4byte	.LASF664
	.byte	0x5
	.uleb128 0x1ee
	.4byte	.LASF665
	.byte	0x5
	.uleb128 0x206
	.4byte	.LASF666
	.byte	0x5
	.uleb128 0x20a
	.4byte	.LASF667
	.byte	0x5
	.uleb128 0x20e
	.4byte	.LASF668
	.byte	0x5
	.uleb128 0x212
	.4byte	.LASF669
	.byte	0x5
	.uleb128 0x222
	.4byte	.LASF670
	.byte	0x5
	.uleb128 0x227
	.4byte	.LASF671
	.byte	0x5
	.uleb128 0x22c
	.4byte	.LASF672
	.byte	0x5
	.uleb128 0x22d
	.4byte	.LASF673
	.byte	0x5
	.uleb128 0x238
	.4byte	.LASF674
	.byte	0x5
	.uleb128 0x23c
	.4byte	.LASF675
	.byte	0x5
	.uleb128 0x240
	.4byte	.LASF676
	.byte	0x5
	.uleb128 0x244
	.4byte	.LASF677
	.byte	0
	.section	.debug_macro,"G",%progbits,wm4.__SEGGER_RTL.h.26.dafde22208ccda87397994258692170b,comdat
.Ldebug_macro5:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x1a
	.4byte	.LASF678
	.byte	0x5
	.uleb128 0x1b
	.4byte	.LASF679
	.byte	0x5
	.uleb128 0x25
	.4byte	.LASF680
	.byte	0x5
	.uleb128 0x29
	.4byte	.LASF681
	.byte	0
	.section	.debug_macro,"G",%progbits,wm4.stdio.h.34.42aa5dfc4dec4b7eea22339ad13bc805,comdat
.Ldebug_macro6:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.uleb128 0x22
	.4byte	.LASF682
	.byte	0x5
	.uleb128 0x26
	.4byte	.LASF683
	.byte	0x5
	.uleb128 0x2a
	.4byte	.LASF684
	.byte	0x5
	.uleb128 0x2b
	.4byte	.LASF685
	.byte	0x5
	.uleb128 0x35
	.4byte	.LASF686
	.byte	0x5
	.uleb128 0x36
	.4byte	.LASF687
	.byte	0x5
	.uleb128 0x37
	.4byte	.LASF688
	.byte	0x5
	.uleb128 0x39
	.4byte	.LASF689
	.byte	0x5
	.uleb128 0x3a
	.4byte	.LASF690
	.byte	0x5
	.uleb128 0x3b
	.4byte	.LASF691
	.byte	0x5
	.uleb128 0x3c
	.4byte	.LASF692
	.byte	0x5
	.uleb128 0x47
	.4byte	.LASF693
	.byte	0x5
	.uleb128 0x4c
	.4byte	.LASF694
	.byte	0x5
	.uleb128 0x51
	.4byte	.LASF695
	.byte	0x5
	.uleb128 0x56
	.4byte	.LASF696
	.byte	0
	.section	.debug_macro,"G",%progbits,wm4.stdint.h.11.41cebd920198fcae1efc8eda76700dbd,comdat
.Ldebug_macro7:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xb
	.4byte	.LASF698
	.byte	0x5
	.uleb128 0x24
	.4byte	.LASF699
	.byte	0x5
	.uleb128 0x25
	.4byte	.LASF700
	.byte	0x5
	.uleb128 0x26
	.4byte	.LASF701
	.byte	0x5
	.uleb128 0x27
	.4byte	.LASF702
	.byte	0x5
	.uleb128 0x28
	.4byte	.LASF703
	.byte	0x5
	.uleb128 0x29
	.4byte	.LASF704
	.byte	0x5
	.uleb128 0x2a
	.4byte	.LASF705
	.byte	0x5
	.uleb128 0x2b
	.4byte	.LASF706
	.byte	0x5
	.uleb128 0x34
	.4byte	.LASF707
	.byte	0x5
	.uleb128 0x35
	.4byte	.LASF708
	.byte	0x5
	.uleb128 0x36
	.4byte	.LASF709
	.byte	0x5
	.uleb128 0x37
	.4byte	.LASF710
	.byte	0x5
	.uleb128 0x41
	.4byte	.LASF711
	.byte	0x5
	.uleb128 0x42
	.4byte	.LASF712
	.byte	0x5
	.uleb128 0x43
	.4byte	.LASF713
	.byte	0x5
	.uleb128 0x4d
	.4byte	.LASF714
	.byte	0x5
	.uleb128 0x4e
	.4byte	.LASF715
	.byte	0x5
	.uleb128 0x4f
	.4byte	.LASF716
	.byte	0x5
	.uleb128 0x50
	.4byte	.LASF717
	.byte	0x5
	.uleb128 0x51
	.4byte	.LASF718
	.byte	0x5
	.uleb128 0x52
	.4byte	.LASF719
	.byte	0x5
	.uleb128 0x53
	.4byte	.LASF720
	.byte	0x5
	.uleb128 0x54
	.4byte	.LASF721
	.byte	0x5
	.uleb128 0x55
	.4byte	.LASF722
	.byte	0x5
	.uleb128 0x56
	.4byte	.LASF723
	.byte	0x5
	.uleb128 0x57
	.4byte	.LASF724
	.byte	0x5
	.uleb128 0x58
	.4byte	.LASF725
	.byte	0x5
	.uleb128 0x62
	.4byte	.LASF726
	.byte	0x5
	.uleb128 0x63
	.4byte	.LASF727
	.byte	0x5
	.uleb128 0x64
	.4byte	.LASF728
	.byte	0x5
	.uleb128 0x65
	.4byte	.LASF729
	.byte	0x5
	.uleb128 0x66
	.4byte	.LASF730
	.byte	0x5
	.uleb128 0x67
	.4byte	.LASF731
	.byte	0x5
	.uleb128 0x68
	.4byte	.LASF732
	.byte	0x5
	.uleb128 0x69
	.4byte	.LASF733
	.byte	0x5
	.uleb128 0x6a
	.4byte	.LASF734
	.byte	0x5
	.uleb128 0x6b
	.4byte	.LASF735
	.byte	0x5
	.uleb128 0x6c
	.4byte	.LASF736
	.byte	0x5
	.uleb128 0x6d
	.4byte	.LASF737
	.byte	0x5
	.uleb128 0x77
	.4byte	.LASF738
	.byte	0x5
	.uleb128 0x78
	.4byte	.LASF739
	.byte	0x5
	.uleb128 0x79
	.4byte	.LASF740
	.byte	0x5
	.uleb128 0x7a
	.4byte	.LASF741
	.byte	0x5
	.uleb128 0x7b
	.4byte	.LASF742
	.byte	0x5
	.uleb128 0x7c
	.4byte	.LASF743
	.byte	0x5
	.uleb128 0x8d
	.4byte	.LASF744
	.byte	0x5
	.uleb128 0x8e
	.4byte	.LASF745
	.byte	0x5
	.uleb128 0x97
	.4byte	.LASF746
	.byte	0x5
	.uleb128 0x98
	.4byte	.LASF747
	.byte	0x5
	.uleb128 0x99
	.4byte	.LASF748
	.byte	0x5
	.uleb128 0x9a
	.4byte	.LASF749
	.byte	0x5
	.uleb128 0xa3
	.4byte	.LASF750
	.byte	0x5
	.uleb128 0xa4
	.4byte	.LASF751
	.byte	0x5
	.uleb128 0xa5
	.4byte	.LASF752
	.byte	0x5
	.uleb128 0xa6
	.4byte	.LASF753
	.byte	0x5
	.uleb128 0xaf
	.4byte	.LASF754
	.byte	0x5
	.uleb128 0xb0
	.4byte	.LASF755
	.byte	0x5
	.uleb128 0xba
	.4byte	.LASF756
	.byte	0x5
	.uleb128 0xbc
	.4byte	.LASF757
	.byte	0
	.section	.debug_macro,"G",%progbits,wm4.app_uart_ringbuff.h.13.a1cd98c730310357b41dc99f7398e7f4,comdat
.Ldebug_macro8:
	.2byte	0x4
	.byte	0
	.byte	0x5
	.uleb128 0xd
	.4byte	.LASF760
	.byte	0x5
	.uleb128 0xe
	.4byte	.LASF761
	.byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF647:
	.ascii	"__SEGGER_RTL_BitcastToF64(X) __SEGGER_RTL_BitcastTo"
	.ascii	"F64_inline(X)\000"
.LASF579:
	.ascii	"__SEGGER_RTL_SIGNAL_SIGABRT __aeabi_SIGABRT\000"
.LASF690:
	.ascii	"_IOFBF 0\000"
.LASF186:
	.ascii	"__DECIMAL_DIG__ 17\000"
.LASF370:
	.ascii	"__UHA_FBIT__ 8\000"
.LASF813:
	.ascii	"app_uart_ringbuffer_reset\000"
.LASF416:
	.ascii	"__ARM_FEATURE_CLZ 1\000"
.LASF390:
	.ascii	"__GCC_ATOMIC_WCHAR_T_LOCK_FREE 2\000"
.LASF382:
	.ascii	"__CHAR_UNSIGNED__ 1\000"
.LASF766:
	.ascii	"size_t\000"
.LASF572:
	.ascii	"__SEGGER_RTL_BYTE_PATTERN(X) __SEGGER_RTL_BYTE_PATT"
	.ascii	"ERN_func(X)\000"
.LASF243:
	.ascii	"__FLT64_HAS_INFINITY__ 1\000"
.LASF334:
	.ascii	"__LLACCUM_MIN__ (-0X1P31LLK-0X1P31LLK)\000"
.LASF6:
	.ascii	"__GNUC_MINOR__ 2\000"
.LASF490:
	.ascii	"uECC_SQUARE_FUNC 0\000"
.LASF79:
	.ascii	"__PTRDIFF_MAX__ 0x7fffffff\000"
.LASF493:
	.ascii	"APP_UART_RINGBUFF_H \000"
.LASF644:
	.ascii	"__SEGGER_RTL_BitcastToU32(X) __SEGGER_RTL_BitcastTo"
	.ascii	"U32_inline(X)\000"
.LASF661:
	.ascii	"__SEGGER_RTL_U64_H(X) ((__SEGGER_RTL_U32)((__SEGGER"
	.ascii	"_RTL_U64)(X) >> 32))\000"
.LASF239:
	.ascii	"__FLT64_MIN__ 1.1\000"
.LASF90:
	.ascii	"__INTMAX_MAX__ 0x7fffffffffffffffLL\000"
.LASF614:
	.ascii	"__SEGGER_RTL_LEAST_U8 unsigned\000"
.LASF351:
	.ascii	"__TQ_IBIT__ 0\000"
.LASF686:
	.ascii	"SEEK_SET 0\000"
.LASF236:
	.ascii	"__FLT64_DECIMAL_DIG__ 17\000"
.LASF689:
	.ascii	"L_tmpnam 256\000"
.LASF14:
	.ascii	"__ATOMIC_CONSUME 1\000"
.LASF284:
	.ascii	"__LFRACT_MIN__ (-0.5LR-0.5LR)\000"
.LASF75:
	.ascii	"__WCHAR_MAX__ 0xffffffffU\000"
.LASF818:
	.ascii	"check_for\000"
.LASF640:
	.ascii	"__SEGGER_RTL_STDOUT_BUFFER_LEN 64\000"
.LASF795:
	.ascii	"startstringlength\000"
.LASF685:
	.ascii	"__va_list __SEGGER_RTL_VA_LIST\000"
.LASF765:
	.ascii	"signed char\000"
.LASF476:
	.ascii	"APP_TIMER_V2 1\000"
.LASF18:
	.ascii	"__SIZEOF_LONG_LONG__ 8\000"
.LASF169:
	.ascii	"__DBL_MAX_10_EXP__ 308\000"
.LASF274:
	.ascii	"__FRACT_MIN__ (-0.5R-0.5R)\000"
.LASF340:
	.ascii	"__ULLACCUM_MAX__ 0XFFFFFFFFFFFFFFFFP-32ULLK\000"
.LASF731:
	.ascii	"INT_FAST32_MAX INT32_MAX\000"
.LASF310:
	.ascii	"__USACCUM_MAX__ 0XFFFFP-8UHK\000"
.LASF262:
	.ascii	"__SFRACT_FBIT__ 7\000"
.LASF94:
	.ascii	"__INTMAX_WIDTH__ 64\000"
.LASF460:
	.ascii	"__ARM_FEATURE_BF16_SCALAR_ARITHMETIC\000"
.LASF347:
	.ascii	"__SQ_IBIT__ 0\000"
.LASF28:
	.ascii	"__ORDER_PDP_ENDIAN__ 3412\000"
.LASF453:
	.ascii	"__ARM_FEATURE_IDIV 1\000"
.LASF551:
	.ascii	"__SEGGER_RTL_CORE_HAS_BLX_REG 1\000"
.LASF595:
	.ascii	"__WIDTH_FLOAT 1\000"
.LASF43:
	.ascii	"__INT8_TYPE__ signed char\000"
.LASF422:
	.ascii	"__ARM_ARCH_PROFILE 77\000"
.LASF309:
	.ascii	"__USACCUM_MIN__ 0.0UHK\000"
.LASF219:
	.ascii	"__FLT32_DECIMAL_DIG__ 9\000"
.LASF574:
	.ascii	"__SEGGER_RTL_FILL_TAIL(N,W,C) __SEGGER_RTL_FILL_TAI"
	.ascii	"L_func(N, W, C)\000"
.LASF182:
	.ascii	"__LDBL_MIN_EXP__ (-1021)\000"
.LASF806:
	.ascii	"app_uart_ringbuffer_get\000"
.LASF180:
	.ascii	"__LDBL_MANT_DIG__ 53\000"
.LASF119:
	.ascii	"__UINT8_C(c) c\000"
.LASF44:
	.ascii	"__INT16_TYPE__ short int\000"
.LASF660:
	.ascii	"__SEGGER_RTL_FILE_IMPL __SEGGER_RTL_FILE_impl\000"
.LASF739:
	.ascii	"PTRDIFF_MAX INT32_MAX\000"
.LASF805:
	.ascii	"app_uart_ringbuffer_wait_for\000"
.LASF383:
	.ascii	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 1\000"
.LASF601:
	.ascii	"__SEGGER_RTL_INCLUDE_SEGGER_API 0\000"
.LASF4:
	.ascii	"__STDC_HOSTED__ 1\000"
.LASF297:
	.ascii	"__ULLFRACT_FBIT__ 64\000"
.LASF761:
	.ascii	"TIME_OUT 5000\000"
.LASF42:
	.ascii	"__SIG_ATOMIC_TYPE__ int\000"
.LASF691:
	.ascii	"_IOLBF 1\000"
.LASF556:
	.ascii	"__SEGGER_RTL_FLOAT64_C_COMPLEX double _Complex\000"
.LASF775:
	.ascii	"DATA_IS_AVALABLE\000"
.LASF62:
	.ascii	"__INT_FAST64_TYPE__ long long int\000"
.LASF37:
	.ascii	"__WINT_TYPE__ unsigned int\000"
.LASF680:
	.ascii	"__SEGGER_RTL_FILE_IMPL_DEFINED \000"
.LASF648:
	.ascii	"__SEGGER_RTL_SMULL_X(X,Y) __SEGGER_RTL_SMULL_X_func"
	.ascii	"((X), (Y))\000"
.LASF218:
	.ascii	"__FLT32_MAX_10_EXP__ 38\000"
.LASF785:
	.ascii	"buffertolookinto\000"
.LASF228:
	.ascii	"__FP_FAST_FMAF32 1\000"
.LASF140:
	.ascii	"__UINTPTR_MAX__ 0xffffffffU\000"
.LASF486:
	.ascii	"NRF52_PAN_74 1\000"
.LASF215:
	.ascii	"__FLT32_MIN_EXP__ (-125)\000"
.LASF707:
	.ascii	"UINT8_MAX 255\000"
.LASF210:
	.ascii	"__FLT16_HAS_INFINITY__ 1\000"
.LASF86:
	.ascii	"__WCHAR_WIDTH__ 32\000"
.LASF287:
	.ascii	"__ULFRACT_FBIT__ 32\000"
.LASF233:
	.ascii	"__FLT64_MIN_10_EXP__ (-307)\000"
.LASF32:
	.ascii	"__GNUC_EXECUTION_CHARSET_NAME \"UTF-8\"\000"
.LASF9:
	.ascii	"__ATOMIC_RELAXED 0\000"
.LASF699:
	.ascii	"INT8_MIN (-128)\000"
.LASF133:
	.ascii	"__INT_FAST64_WIDTH__ 64\000"
.LASF1:
	.ascii	"__STDC_VERSION__ 199901L\000"
.LASF171:
	.ascii	"__DBL_MAX__ ((double)1.1)\000"
.LASF487:
	.ascii	"NRF_CRYPTO_MAX_INSTANCE_COUNT 1\000"
.LASF266:
	.ascii	"__SFRACT_EPSILON__ 0x1P-7HR\000"
.LASF514:
	.ascii	"__SEGGER_RTL_FLOAT16 _Float16\000"
.LASF113:
	.ascii	"__INT32_C(c) c ## L\000"
.LASF356:
	.ascii	"__USQ_FBIT__ 32\000"
.LASF27:
	.ascii	"__ORDER_BIG_ENDIAN__ 4321\000"
.LASF217:
	.ascii	"__FLT32_MAX_EXP__ 128\000"
.LASF237:
	.ascii	"__FLT64_MAX__ 1.1\000"
.LASF606:
	.ascii	"__SEGGER_RTL_I32 int\000"
.LASF354:
	.ascii	"__UHQ_FBIT__ 16\000"
.LASF535:
	.ascii	"__SEGGER_RTL_PUBLIC_API __attribute__((__weak__))\000"
.LASF232:
	.ascii	"__FLT64_MIN_EXP__ (-1021)\000"
.LASF750:
	.ascii	"UINT8_C(x) (x ##u)\000"
.LASF88:
	.ascii	"__PTRDIFF_WIDTH__ 32\000"
.LASF256:
	.ascii	"__FLT32X_EPSILON__ 1.1\000"
.LASF526:
	.ascii	"__SEGGER_RTL_UMULL(lo,hi,x0,x1) do { __asm__( \"umu"
	.ascii	"ll %0, %1, %2, %3\" : \"=r\"(lo), \"=r\"(hi) : \"r\""
	.ascii	"((unsigned)(x0)), \"r\"((unsigned)(x1)) ); } while "
	.ascii	"(0)\000"
.LASF134:
	.ascii	"__UINT_FAST8_MAX__ 0xffffffffU\000"
.LASF546:
	.ascii	"__SEGGER_RTL_CORE_HAS_IDIV 1\000"
.LASF474:
	.ascii	"DEBUG 1\000"
.LASF154:
	.ascii	"__FLT_MAX__ 1.1\000"
.LASF323:
	.ascii	"__LACCUM_IBIT__ 32\000"
.LASF129:
	.ascii	"__INT_FAST16_WIDTH__ 32\000"
.LASF434:
	.ascii	"__VFP_FP__ 1\000"
.LASF499:
	.ascii	"__SEGGER_RTL_CONF_H \000"
.LASF138:
	.ascii	"__INTPTR_MAX__ 0x7fffffff\000"
.LASF396:
	.ascii	"__GCC_ATOMIC_POINTER_LOCK_FREE 2\000"
.LASF673:
	.ascii	"__SEGGER_RTL_SUBNORMALS_FLUSH_TO_ZERO 1\000"
.LASF308:
	.ascii	"__USACCUM_IBIT__ 8\000"
.LASF515:
	.ascii	"__SEGGER_RTL_MAX_ALIGN 8\000"
.LASF223:
	.ascii	"__FLT32_EPSILON__ 1.1\000"
.LASF279:
	.ascii	"__UFRACT_MIN__ 0.0UR\000"
.LASF702:
	.ascii	"INT16_MAX 32767\000"
.LASF96:
	.ascii	"__SIG_ATOMIC_MIN__ (-__SIG_ATOMIC_MAX__ - 1)\000"
.LASF259:
	.ascii	"__FLT32X_HAS_INFINITY__ 1\000"
.LASF740:
	.ascii	"SIZE_MAX INT32_MAX\000"
.LASF55:
	.ascii	"__UINT_LEAST8_TYPE__ unsigned char\000"
.LASF667:
	.ascii	"__SEGGER_RTL_NAN __builtin_nanf(\"0x7fc00000\")\000"
.LASF512:
	.ascii	"__SEGGER_RTL_TYPESET 32\000"
.LASF318:
	.ascii	"__UACCUM_IBIT__ 16\000"
.LASF764:
	.ascii	"long int\000"
.LASF576:
	.ascii	"__SEGGER_RTL_WR_WORD(A,W) __SEGGER_RTL_WR_WORD_func"
	.ascii	"(A, W)\000"
.LASF255:
	.ascii	"__FLT32X_MIN__ 1.1\000"
.LASF132:
	.ascii	"__INT_FAST64_MAX__ 0x7fffffffffffffffLL\000"
.LASF252:
	.ascii	"__FLT32X_DECIMAL_DIG__ 17\000"
.LASF260:
	.ascii	"__FLT32X_HAS_QUIET_NAN__ 1\000"
.LASF782:
	.ascii	"RingBuffer\000"
.LASF59:
	.ascii	"__INT_FAST8_TYPE__ int\000"
.LASF374:
	.ascii	"__UDA_FBIT__ 32\000"
.LASF235:
	.ascii	"__FLT64_MAX_10_EXP__ 308\000"
.LASF93:
	.ascii	"__UINTMAX_C(c) c ## ULL\000"
.LASF31:
	.ascii	"__SIZEOF_POINTER__ 4\000"
.LASF51:
	.ascii	"__INT_LEAST8_TYPE__ signed char\000"
.LASF610:
	.ascii	"__SEGGER_RTL_I8 signed char\000"
.LASF386:
	.ascii	"__GCC_ATOMIC_BOOL_LOCK_FREE 2\000"
.LASF346:
	.ascii	"__SQ_FBIT__ 31\000"
.LASF612:
	.ascii	"__SEGGER_RTL_LEAST_U16 unsigned\000"
.LASF444:
	.ascii	"__ARM_NEON__\000"
.LASF578:
	.ascii	"__SEGGER_RTL_SIGNAL_MAX 6\000"
.LASF758:
	.ascii	"_LIBCPP_STRING_H \000"
.LASF447:
	.ascii	"__THUMB_INTERWORK__ 1\000"
.LASF300:
	.ascii	"__ULLFRACT_MAX__ 0XFFFFFFFFFFFFFFFFP-64ULLR\000"
.LASF477:
	.ascii	"APP_TIMER_V2_RTC1_ENABLED 1\000"
.LASF482:
	.ascii	"MBEDTLS_CONFIG_FILE \"nrf_crypto_mbedtls_config.h\""
	.ascii	"\000"
.LASF33:
	.ascii	"__GNUC_WIDE_EXECUTION_CHARSET_NAME \"UTF-32LE\"\000"
.LASF249:
	.ascii	"__FLT32X_MIN_10_EXP__ (-307)\000"
.LASF41:
	.ascii	"__CHAR32_TYPE__ long unsigned int\000"
.LASF562:
	.ascii	"__SEGGER_RTL_P2I(X) ((unsigned)(X))\000"
.LASF441:
	.ascii	"__ARM_FEATURE_FP16_VECTOR_ARITHMETIC\000"
.LASF566:
	.ascii	"__SEGGER_RTL_UNALIGNED_ATTR __attribute__((__aligne"
	.ascii	"d__(1)))\000"
.LASF710:
	.ascii	"UINT64_MAX 18446744073709551615ULL\000"
.LASF179:
	.ascii	"__DBL_IS_IEC_60559__ 2\000"
.LASF136:
	.ascii	"__UINT_FAST32_MAX__ 0xffffffffU\000"
.LASF151:
	.ascii	"__FLT_MAX_EXP__ 128\000"
.LASF17:
	.ascii	"__SIZEOF_LONG__ 4\000"
.LASF573:
	.ascii	"__SEGGER_RTL_FILL_HEAD(A,W,C) __SEGGER_RTL_FILL_HEA"
	.ascii	"D_func(A, W, C)\000"
.LASF583:
	.ascii	"__SEGGER_RTL_SIGNAL_SIGSEGV __aeabi_SIGSEGV\000"
.LASF21:
	.ascii	"__SIZEOF_DOUBLE__ 8\000"
.LASF114:
	.ascii	"__INT_LEAST32_WIDTH__ 32\000"
.LASF798:
	.ascii	"endposition\000"
.LASF527:
	.ascii	"__SEGGER_RTL_UMULL_X(x,y) ((__SEGGER_RTL_U64)(__SEG"
	.ascii	"GER_RTL_U32)(x) * (__SEGGER_RTL_U32)(y))\000"
.LASF801:
	.ascii	"app_uart_ringbuffer_copy_upto\000"
.LASF724:
	.ascii	"UINT_LEAST32_MAX UINT32_MAX\000"
.LASF638:
	.ascii	"__SEGGER_RTL_MAX_HEAP_SIZE (8*1024*1024u)\000"
.LASF516:
	.ascii	"__SEGGER_RTL_FP_ABI 2\000"
.LASF155:
	.ascii	"__FLT_NORM_MAX__ 1.1\000"
.LASF819:
	.ascii	"app_uart_ringbuffer_peek\000"
.LASF735:
	.ascii	"UINT_FAST16_MAX UINT32_MAX\000"
.LASF376:
	.ascii	"__UTA_FBIT__ 64\000"
.LASF153:
	.ascii	"__FLT_DECIMAL_DIG__ 9\000"
.LASF542:
	.ascii	"__SEGGER_RTL_CORE_HAS_REV 1\000"
.LASF428:
	.ascii	"__thumb__ 1\000"
.LASF729:
	.ascii	"INT_FAST16_MAX INT32_MAX\000"
.LASF112:
	.ascii	"__INT_LEAST32_MAX__ 0x7fffffffL\000"
.LASF50:
	.ascii	"__UINT64_TYPE__ long long unsigned int\000"
.LASF767:
	.ascii	"uint8_t\000"
.LASF443:
	.ascii	"__ARM_FEATURE_FMA 1\000"
.LASF191:
	.ascii	"__LDBL_EPSILON__ 1.1\000"
.LASF380:
	.ascii	"__GNUC_STDC_INLINE__ 1\000"
.LASF534:
	.ascii	"__SEGGER_RTL_REQUEST_INLINE __inline__\000"
.LASF439:
	.ascii	"__ARM_FP16_ARGS 1\000"
.LASF723:
	.ascii	"UINT_LEAST16_MAX UINT16_MAX\000"
.LASF497:
	.ascii	"__SEGGER_RTL_H \000"
.LASF602:
	.ascii	"__SEGGER_RTL_INCLUDE_C_API 1\000"
.LASF7:
	.ascii	"__GNUC_PATCHLEVEL__ 1\000"
.LASF389:
	.ascii	"__GCC_ATOMIC_CHAR32_T_LOCK_FREE 2\000"
.LASF120:
	.ascii	"__UINT_LEAST16_MAX__ 0xffff\000"
.LASF777:
	.ascii	"Head\000"
.LASF672:
	.ascii	"__SEGGER_RTL_SUBNORMALS_READ_AS_ZERO 1\000"
.LASF148:
	.ascii	"__FLT_DIG__ 6\000"
.LASF65:
	.ascii	"__UINT_FAST32_TYPE__ unsigned int\000"
.LASF768:
	.ascii	"unsigned char\000"
.LASF3:
	.ascii	"__STDC_UTF_32__ 1\000"
.LASF20:
	.ascii	"__SIZEOF_FLOAT__ 4\000"
.LASF303:
	.ascii	"__SACCUM_IBIT__ 8\000"
.LASF152:
	.ascii	"__FLT_MAX_10_EXP__ 38\000"
.LASF206:
	.ascii	"__FLT16_MIN__ 1.1\000"
.LASF518:
	.ascii	"__SEGGER_RTL_FLT_SELECT(HEX,DEC) HEX\000"
.LASF275:
	.ascii	"__FRACT_MAX__ 0X7FFFP-15R\000"
.LASF141:
	.ascii	"__GCC_IEC_559 0\000"
.LASF494:
	.ascii	"_LIBCPP_STDIO_H \000"
.LASF130:
	.ascii	"__INT_FAST32_MAX__ 0x7fffffff\000"
.LASF10:
	.ascii	"__ATOMIC_SEQ_CST 5\000"
.LASF748:
	.ascii	"INT32_C(x) (x)\000"
.LASF547:
	.ascii	"__SEGGER_RTL_CORE_HAS_CBZ_CBNZ 1\000"
.LASF705:
	.ascii	"INT64_MIN (-9223372036854775807LL-1)\000"
.LASF524:
	.ascii	"__SEGGER_RTL_SMLAL(lo,hi,x0,x1) do { __asm__( \"sml"
	.ascii	"al %0, %1, %2, %3\" : \"+r\"(lo), \"+r\"(hi) : \"r\""
	.ascii	"((unsigned)(x0)), \"r\"((unsigned)(x1)) ); } while "
	.ascii	"(0)\000"
.LASF481:
	.ascii	"INITIALIZE_USER_SECTIONS 1\000"
.LASF754:
	.ascii	"INTMAX_C(x) (x ##LL)\000"
.LASF103:
	.ascii	"__UINT16_MAX__ 0xffff\000"
.LASF815:
	.ascii	"GNU C99 11.2.1 20220111 -fmessage-length=0 -std=gnu"
	.ascii	"99 -mcpu=cortex-m4 -mlittle-endian -mfloat-abi=hard"
	.ascii	" -mfpu=fpv4-sp-d16 -mthumb -mtp=soft -mfp16-format="
	.ascii	"ieee -munaligned-access -gdwarf-4 -g3 -gpubnames -f"
	.ascii	"omit-frame-pointer -fno-dwarf2-cfi-asm -ffunction-s"
	.ascii	"ections -fdata-sections -fshort-enums -fno-common\000"
.LASF491:
	.ascii	"uECC_SUPPORT_COMPRESSED_POINT 0\000"
.LASF749:
	.ascii	"INT64_C(x) (x ##LL)\000"
.LASF757:
	.ascii	"WCHAR_MIN __WCHAR_MIN__\000"
.LASF175:
	.ascii	"__DBL_DENORM_MIN__ ((double)1.1)\000"
.LASF770:
	.ascii	"uint16_t\000"
.LASF701:
	.ascii	"INT16_MIN (-32767-1)\000"
.LASF429:
	.ascii	"__thumb2__ 1\000"
.LASF212:
	.ascii	"__FLT16_IS_IEC_60559__ 2\000"
.LASF598:
	.ascii	"__SEGGER_RTL_FORCE_SOFT_FLOAT 0\000"
.LASF505:
	.ascii	"__SEGGER_RTL_UNREACHABLE() __builtin_unreachable()\000"
.LASF507:
	.ascii	"__SEGGER_RTL_INCLUDE_AEABI_API 2\000"
.LASF326:
	.ascii	"__LACCUM_EPSILON__ 0x1P-31LK\000"
.LASF170:
	.ascii	"__DBL_DECIMAL_DIG__ 17\000"
.LASF745:
	.ascii	"WINT_MAX 2147483647L\000"
.LASF22:
	.ascii	"__SIZEOF_LONG_DOUBLE__ 8\000"
.LASF398:
	.ascii	"__PRAGMA_REDEFINE_EXTNAME 1\000"
.LASF36:
	.ascii	"__WCHAR_TYPE__ unsigned int\000"
.LASF762:
	.ascii	"char\000"
.LASF373:
	.ascii	"__USA_IBIT__ 16\000"
.LASF384:
	.ascii	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 1\000"
.LASF653:
	.ascii	"__SEGGER_RTL_RODATA_IS_RW 0\000"
.LASF698:
	.ascii	"__SEGGER_RTL_STDINT_H \000"
.LASF66:
	.ascii	"__UINT_FAST64_TYPE__ long long unsigned int\000"
.LASF635:
	.ascii	"__SEGGER_RTL_FORMAT_INT_WIDTH\000"
.LASF684:
	.ascii	"__SEGGER_RTL_VA_LIST_DEFINED \000"
.LASF362:
	.ascii	"__HA_FBIT__ 7\000"
.LASF451:
	.ascii	"__FDPIC__\000"
.LASF519:
	.ascii	"__SEGGER_RTL_CORE_HAS_MLA 1\000"
.LASF580:
	.ascii	"__SEGGER_RTL_SIGNAL_SIGFPE __aeabi_SIGFPE\000"
.LASF229:
	.ascii	"__FLT32_IS_IEC_60559__ 2\000"
.LASF622:
	.ascii	"__SEGGER_RTL_SIZEOF_PTR 4\000"
.LASF257:
	.ascii	"__FLT32X_DENORM_MIN__ 1.1\000"
.LASF752:
	.ascii	"UINT32_C(x) (x ##u)\000"
.LASF202:
	.ascii	"__FLT16_MAX_10_EXP__ 4\000"
.LASF268:
	.ascii	"__USFRACT_IBIT__ 0\000"
.LASF712:
	.ascii	"INTMAX_MAX INT64_MAX\000"
.LASF269:
	.ascii	"__USFRACT_MIN__ 0.0UHR\000"
.LASF465:
	.ascii	"__SIZEOF_WCHAR_T 4\000"
.LASF445:
	.ascii	"__ARM_NEON\000"
.LASF102:
	.ascii	"__UINT8_MAX__ 0xff\000"
.LASF184:
	.ascii	"__LDBL_MAX_EXP__ 1024\000"
.LASF593:
	.ascii	"__WIDTH_LONG_LONG 2\000"
.LASF176:
	.ascii	"__DBL_HAS_DENORM__ 1\000"
.LASF366:
	.ascii	"__DA_FBIT__ 31\000"
.LASF69:
	.ascii	"__GXX_ABI_VERSION 1016\000"
.LASF328:
	.ascii	"__ULACCUM_IBIT__ 32\000"
.LASF677:
	.ascii	"__SEGGER_RTL_CORE_HAS_IDIVM_X 0\000"
.LASF350:
	.ascii	"__TQ_FBIT__ 127\000"
.LASF793:
	.ascii	"buffercopyfrom\000"
.LASF659:
	.ascii	"__SEGGER_RTL_SCALED_INTEGER 0\000"
.LASF643:
	.ascii	"__SEGGER_RTL_NAN_FORMAT __SEGGER_RTL_NAN_FORMAT_IEE"
	.ascii	"E\000"
.LASF123:
	.ascii	"__UINT32_C(c) c ## UL\000"
.LASF694:
	.ascii	"__SEGGER_RTL_FPOS_T_DEFINED \000"
.LASF319:
	.ascii	"__UACCUM_MIN__ 0.0UK\000"
.LASF238:
	.ascii	"__FLT64_NORM_MAX__ 1.1\000"
.LASF203:
	.ascii	"__FLT16_DECIMAL_DIG__ 5\000"
.LASF35:
	.ascii	"__PTRDIFF_TYPE__ int\000"
.LASF774:
	.ascii	"DATA_IS_NOT_AVALABLE\000"
.LASF558:
	.ascii	"__SEGGER_RTL_PREFER_BRANCH_FREE_CODE 1\000"
.LASF591:
	.ascii	"__WIDTH_INT 0\000"
.LASF321:
	.ascii	"__UACCUM_EPSILON__ 0x1P-16UK\000"
.LASF459:
	.ascii	"__ARM_FEATURE_MATMUL_INT8\000"
.LASF655:
	.ascii	"__SEGGER_RTL_SIDE_BY_SIZE 0\000"
.LASF391:
	.ascii	"__GCC_ATOMIC_SHORT_LOCK_FREE 2\000"
.LASF570:
	.ascii	"__SEGGER_RTL_DIFF_INDEX(X,Y) __SEGGER_RTL_DIFF_INDE"
	.ascii	"X_func(X, Y)\000"
.LASF307:
	.ascii	"__USACCUM_FBIT__ 8\000"
.LASF727:
	.ascii	"INT_FAST8_MAX INT8_MAX\000"
.LASF395:
	.ascii	"__GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1\000"
.LASF304:
	.ascii	"__SACCUM_MIN__ (-0X1P7HK-0X1P7HK)\000"
.LASF322:
	.ascii	"__LACCUM_FBIT__ 31\000"
.LASF498:
	.ascii	"__SEGGER_RTL_LIBC_CONF_DEFAULTS_H \000"
.LASF539:
	.ascii	"__SEGGER_RTL_CLZ_U32(X) __SEGGER_RTL_CLZ_U32_safe_i"
	.ascii	"nline(X)\000"
.LASF227:
	.ascii	"__FLT32_HAS_QUIET_NAN__ 1\000"
.LASF367:
	.ascii	"__DA_IBIT__ 32\000"
.LASF780:
	.ascii	"RingBuffer_type\000"
.LASF584:
	.ascii	"__SEGGER_RTL_SIGNAL_SIGTERM __aeabi_SIGTERM\000"
.LASF194:
	.ascii	"__LDBL_HAS_INFINITY__ 1\000"
.LASF368:
	.ascii	"__TA_FBIT__ 63\000"
.LASF751:
	.ascii	"UINT16_C(x) (x ##u)\000"
.LASF251:
	.ascii	"__FLT32X_MAX_10_EXP__ 308\000"
.LASF548:
	.ascii	"__SEGGER_RTL_CORE_HAS_TBB_TBH 1\000"
.LASF590:
	.ascii	"__SEGGER_RTL_NAN_FORMAT_COMPACT 2\000"
.LASF656:
	.ascii	"__SEGGER_RTL_SPECIALIZE_COMPARES 1\000"
.LASF353:
	.ascii	"__UQQ_IBIT__ 0\000"
.LASF468:
	.ascii	"__HEAP_SIZE__ 8192\000"
.LASF646:
	.ascii	"__SEGGER_RTL_BitcastToU64(X) __SEGGER_RTL_BitcastTo"
	.ascii	"U64_inline(X)\000"
.LASF118:
	.ascii	"__UINT_LEAST8_MAX__ 0xff\000"
.LASF485:
	.ascii	"NRF52832_XXAA 1\000"
.LASF738:
	.ascii	"PTRDIFF_MIN INT32_MIN\000"
.LASF695:
	.ascii	"__SEGGER_RTL_FILE_DEFINED \000"
.LASF162:
	.ascii	"__FP_FAST_FMAF 1\000"
.LASF261:
	.ascii	"__FLT32X_IS_IEC_60559__ 2\000"
.LASF111:
	.ascii	"__INT_LEAST16_WIDTH__ 16\000"
.LASF145:
	.ascii	"__DEC_EVAL_METHOD__ 2\000"
.LASF442:
	.ascii	"__ARM_FEATURE_FP16_FML\000"
.LASF565:
	.ascii	"__SEGGER_RTL_ALIGN_REM(X) 0\000"
.LASF174:
	.ascii	"__DBL_EPSILON__ ((double)1.1)\000"
.LASF589:
	.ascii	"__SEGGER_RTL_NAN_FORMAT_FAST 1\000"
.LASF271:
	.ascii	"__USFRACT_EPSILON__ 0x1P-8UHR\000"
.LASF716:
	.ascii	"INT_LEAST16_MIN INT16_MIN\000"
.LASF522:
	.ascii	"__SEGGER_RTL_SMULL_HI(x0,x1) ({ long __trash, __hi;"
	.ascii	" __asm__( \"smull %0, %1, %2, %3\" : \"=r\"(__trash"
	.ascii	"), \"=r\"(__hi) : \"r\"((unsigned)(x0)), \"r\"((uns"
	.ascii	"igned)(x1)) ); __hi; })\000"
.LASF267:
	.ascii	"__USFRACT_FBIT__ 8\000"
.LASF335:
	.ascii	"__LLACCUM_MAX__ 0X7FFFFFFFFFFFFFFFP-31LLK\000"
.LASF792:
	.ascii	"endstring\000"
.LASF272:
	.ascii	"__FRACT_FBIT__ 15\000"
.LASF379:
	.ascii	"__USER_LABEL_PREFIX__ \000"
.LASF105:
	.ascii	"__UINT64_MAX__ 0xffffffffffffffffULL\000"
.LASF104:
	.ascii	"__UINT32_MAX__ 0xffffffffUL\000"
.LASF106:
	.ascii	"__INT_LEAST8_MAX__ 0x7f\000"
.LASF812:
	.ascii	"app_uart_ringbuffer_put\000"
.LASF403:
	.ascii	"__ARM_FEATURE_QBIT 1\000"
.LASF529:
	.ascii	"__SEGGER_RTL_UNLIKELY(X) __builtin_expect((X), 0)\000"
.LASF11:
	.ascii	"__ATOMIC_ACQUIRE 2\000"
.LASF410:
	.ascii	"__ARM_FEATURE_COMPLEX\000"
.LASF605:
	.ascii	"__SEGGER_RTL_U32 unsigned\000"
.LASF420:
	.ascii	"__ARM_SIZEOF_WCHAR_T 4\000"
.LASF250:
	.ascii	"__FLT32X_MAX_EXP__ 1024\000"
.LASF378:
	.ascii	"__REGISTER_PREFIX__ \000"
.LASF652:
	.ascii	"__SEGGER_RTL_NO_RETURN \000"
.LASF122:
	.ascii	"__UINT_LEAST32_MAX__ 0xffffffffUL\000"
.LASF631:
	.ascii	"__SEGGER_RTL_FORMAT_FLOAT_WIDTH __WIDTH_DOUBLE\000"
.LASF619:
	.ascii	"__SEGGER_RTL_U64_C(X) X ##uLL\000"
.LASF117:
	.ascii	"__INT_LEAST64_WIDTH__ 64\000"
.LASF160:
	.ascii	"__FLT_HAS_INFINITY__ 1\000"
.LASF550:
	.ascii	"__SEGGER_RTL_CORE_HAS_BFC_BFI_BFX 1\000"
.LASF797:
	.ascii	"startposition\000"
.LASF98:
	.ascii	"__INT8_MAX__ 0x7f\000"
.LASF678:
	.ascii	"__SEGGER_RTL_VERSION 41600\000"
.LASF8:
	.ascii	"__VERSION__ \"11.2.1 20220111\"\000"
.LASF408:
	.ascii	"__ARM_FEATURE_CRC32\000"
.LASF264:
	.ascii	"__SFRACT_MIN__ (-0.5HR-0.5HR)\000"
.LASF365:
	.ascii	"__SA_IBIT__ 16\000"
.LASF142:
	.ascii	"__GCC_IEC_559_COMPLEX 0\000"
.LASF412:
	.ascii	"__ARM_FEATURE_MVE\000"
.LASF48:
	.ascii	"__UINT16_TYPE__ short unsigned int\000"
.LASF599:
	.ascii	"__SEGGER_RTL_CONFIG_CODE_COVERAGE 0\000"
.LASF703:
	.ascii	"INT32_MIN (-2147483647L-1)\000"
.LASF810:
	.ascii	"check\000"
.LASF709:
	.ascii	"UINT32_MAX 4294967295UL\000"
.LASF189:
	.ascii	"__LDBL_NORM_MAX__ 1.1\000"
.LASF144:
	.ascii	"__FLT_EVAL_METHOD_TS_18661_3__ 0\000"
.LASF81:
	.ascii	"__SCHAR_WIDTH__ 8\000"
.LASF63:
	.ascii	"__UINT_FAST8_TYPE__ unsigned int\000"
.LASF333:
	.ascii	"__LLACCUM_IBIT__ 32\000"
.LASF276:
	.ascii	"__FRACT_EPSILON__ 0x1P-15R\000"
.LASF360:
	.ascii	"__UTQ_FBIT__ 128\000"
.LASF100:
	.ascii	"__INT32_MAX__ 0x7fffffffL\000"
.LASF115:
	.ascii	"__INT_LEAST64_MAX__ 0x7fffffffffffffffLL\000"
.LASF461:
	.ascii	"__ARM_FEATURE_BF16_VECTOR_ARITHMETIC\000"
.LASF224:
	.ascii	"__FLT32_DENORM_MIN__ 1.1\000"
.LASF528:
	.ascii	"__SEGGER_RTL_UMLAL(lo,hi,x0,x1) do { __asm__(\"umla"
	.ascii	"l %0, %1, %2, %3\" : \"+r\"(lo), \"+r\"(hi) : \"r\""
	.ascii	"((unsigned)(x0)), \"r\"((unsigned)(x1)) ); } while "
	.ascii	"(0)\000"
.LASF213:
	.ascii	"__FLT32_MANT_DIG__ 24\000"
.LASF674:
	.ascii	"__SEGGER_RTL_CORE_HAS_UDIV_X 0\000"
.LASF125:
	.ascii	"__UINT64_C(c) c ## ULL\000"
.LASF58:
	.ascii	"__UINT_LEAST64_TYPE__ long long unsigned int\000"
.LASF741:
	.ascii	"INTPTR_MIN INT32_MIN\000"
.LASF742:
	.ascii	"INTPTR_MAX INT32_MAX\000"
.LASF549:
	.ascii	"__SEGGER_RTL_CORE_HAS_UXT_SXT 1\000"
.LASF388:
	.ascii	"__GCC_ATOMIC_CHAR16_T_LOCK_FREE 2\000"
.LASF654:
	.ascii	"__SEGGER_RTL_USE_PARA(Para) (void)Para\000"
.LASF168:
	.ascii	"__DBL_MAX_EXP__ 1024\000"
.LASF12:
	.ascii	"__ATOMIC_RELEASE 3\000"
.LASF258:
	.ascii	"__FLT32X_HAS_DENORM__ 1\000"
.LASF147:
	.ascii	"__FLT_MANT_DIG__ 24\000"
.LASF781:
	.ascii	"timeout\000"
.LASF359:
	.ascii	"__UDQ_IBIT__ 0\000"
.LASF466:
	.ascii	"__SES_ARM 1\000"
.LASF543:
	.ascii	"__SEGGER_RTL_CORE_HAS_PKHTB_PKHBT 1\000"
.LASF320:
	.ascii	"__UACCUM_MAX__ 0XFFFFFFFFP-16UK\000"
.LASF627:
	.ascii	"__SEGGER_RTL_SIZEOF_WCHAR_T __SIZEOF_WCHAR_T__\000"
.LASF720:
	.ascii	"INT_LEAST64_MIN INT64_MIN\000"
.LASF541:
	.ascii	"__SEGGER_RTL_CORE_HAS_UQADD_UQSUB 1\000"
.LASF575:
	.ascii	"__SEGGER_RTL_RD_WORD(A) __SEGGER_RTL_RD_WORD_func(A"
	.ascii	")\000"
.LASF101:
	.ascii	"__INT64_MAX__ 0x7fffffffffffffffLL\000"
.LASF404:
	.ascii	"__ARM_FEATURE_SAT 1\000"
.LASF200:
	.ascii	"__FLT16_MIN_10_EXP__ (-4)\000"
.LASF298:
	.ascii	"__ULLFRACT_IBIT__ 0\000"
.LASF469:
	.ascii	"__SES_VERSION 63201\000"
.LASF5:
	.ascii	"__GNUC__ 11\000"
.LASF241:
	.ascii	"__FLT64_DENORM_MIN__ 1.1\000"
.LASF470:
	.ascii	"__GNU_LINKER 1\000"
.LASF84:
	.ascii	"__LONG_WIDTH__ 32\000"
.LASF624:
	.ascii	"__SEGGER_RTL_SIZE_T __SIZE_TYPE__\000"
.LASF317:
	.ascii	"__UACCUM_FBIT__ 16\000"
.LASF577:
	.ascii	"__SEGGER_RTL_WR_PARTIAL_WORD(A,W,N) __SEGGER_RTL_WR"
	.ascii	"_PARTIAL_WORD_func(A, W, N)\000"
.LASF281:
	.ascii	"__UFRACT_EPSILON__ 0x1P-16UR\000"
.LASF76:
	.ascii	"__WCHAR_MIN__ 0U\000"
.LASF192:
	.ascii	"__LDBL_DENORM_MIN__ 1.1\000"
.LASF159:
	.ascii	"__FLT_HAS_DENORM__ 1\000"
.LASF555:
	.ascii	"__SEGGER_RTL_FLOAT32_C_COMPLEX float _Complex\000"
.LASF222:
	.ascii	"__FLT32_MIN__ 1.1\000"
.LASF472:
	.ascii	"_LIBCPP_HAS_NO_OFF_T_FUNCTIONS 1\000"
.LASF393:
	.ascii	"__GCC_ATOMIC_LONG_LOCK_FREE 2\000"
.LASF329:
	.ascii	"__ULACCUM_MIN__ 0.0ULK\000"
.LASF425:
	.ascii	"__ARM_ARCH 7\000"
.LASF146:
	.ascii	"__FLT_RADIX__ 2\000"
.LASF772:
	.ascii	"long long int\000"
.LASF413:
	.ascii	"__ARM_FEATURE_CMSE\000"
.LASF816:
	.ascii	"F:\\nRF5_SDK_17.1.0_ddde560\\examples\\Myproject\\t"
	.ascii	"emplate_project_combine\\app_uart_ringbuff.c\000"
.LASF629:
	.ascii	"__SEGGER_RTL_OPTIMIZE 0\000"
.LASF195:
	.ascii	"__LDBL_HAS_QUIET_NAN__ 1\000"
.LASF803:
	.ascii	"numberofchar\000"
.LASF85:
	.ascii	"__LONG_LONG_WIDTH__ 64\000"
.LASF137:
	.ascii	"__UINT_FAST64_MAX__ 0xffffffffffffffffULL\000"
.LASF435:
	.ascii	"__ARM_FP\000"
.LASF363:
	.ascii	"__HA_IBIT__ 8\000"
.LASF139:
	.ascii	"__INTPTR_WIDTH__ 32\000"
.LASF394:
	.ascii	"__GCC_ATOMIC_LLONG_LOCK_FREE 1\000"
.LASF135:
	.ascii	"__UINT_FAST16_MAX__ 0xffffffffU\000"
.LASF626:
	.ascii	"__SEGGER_RTL_WCHAR_T __WCHAR_TYPE__\000"
.LASF733:
	.ascii	"INT_FAST64_MAX INT64_MAX\000"
.LASF234:
	.ascii	"__FLT64_MAX_EXP__ 1024\000"
.LASF552:
	.ascii	"__SEGGER_RTL_CORE_HAS_LONG_SHIFT 1\000"
.LASF688:
	.ascii	"SEEK_END 2\000"
.LASF91:
	.ascii	"__INTMAX_C(c) c ## LL\000"
.LASF623:
	.ascii	"__SEGGER_RTL_PTRDIFF_T __PTRDIFF_TYPE__\000"
.LASF421:
	.ascii	"__ARM_ARCH_PROFILE\000"
.LASF46:
	.ascii	"__INT64_TYPE__ long long int\000"
.LASF190:
	.ascii	"__LDBL_MIN__ 1.1\000"
.LASF24:
	.ascii	"__CHAR_BIT__ 8\000"
.LASF399:
	.ascii	"__SIZEOF_WCHAR_T__ 4\000"
.LASF536:
	.ascii	"__SEGGER_RTL_FLOAT32_ABS(__m) ({ float __d; __asm__"
	.ascii	" __volatile__(\"vabs.f32 %[d], %[m]\" : [d] \"=t\"("
	.ascii	"__d) : [m] \"t\"(__m)); __d; })\000"
.LASF246:
	.ascii	"__FLT32X_MANT_DIG__ 53\000"
.LASF254:
	.ascii	"__FLT32X_NORM_MAX__ 1.1\000"
.LASF427:
	.ascii	"__GCC_ASM_FLAG_OUTPUTS__ 1\000"
.LASF280:
	.ascii	"__UFRACT_MAX__ 0XFFFFP-16UR\000"
.LASF201:
	.ascii	"__FLT16_MAX_EXP__ 16\000"
.LASF779:
	.ascii	"Buffer\000"
.LASF263:
	.ascii	"__SFRACT_IBIT__ 0\000"
.LASF615:
	.ascii	"__SEGGER_RTL_LEAST_I8 int\000"
.LASF778:
	.ascii	"Tail\000"
.LASF746:
	.ascii	"INT8_C(x) (x)\000"
.LASF29:
	.ascii	"__BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__\000"
.LASF446:
	.ascii	"__ARM_NEON_FP\000"
.LASF492:
	.ascii	"uECC_VLI_NATIVE_LITTLE_ENDIAN 1\000"
.LASF791:
	.ascii	"startstring\000"
.LASF683:
	.ascii	"EOF (-1)\000"
.LASF277:
	.ascii	"__UFRACT_FBIT__ 16\000"
.LASF358:
	.ascii	"__UDQ_FBIT__ 64\000"
.LASF158:
	.ascii	"__FLT_DENORM_MIN__ 1.1\000"
.LASF185:
	.ascii	"__LDBL_MAX_10_EXP__ 308\000"
.LASF204:
	.ascii	"__FLT16_MAX__ 1.1\000"
.LASF61:
	.ascii	"__INT_FAST32_TYPE__ int\000"
.LASF788:
	.ascii	"string\000"
.LASF253:
	.ascii	"__FLT32X_MAX__ 1.1\000"
.LASF588:
	.ascii	"__SEGGER_RTL_NAN_FORMAT_IEEE 0\000"
.LASF763:
	.ascii	"unsigned int\000"
.LASF560:
	.ascii	"__SEGGER_RTL_X_assert __aeabi_assert\000"
.LASF714:
	.ascii	"INT_LEAST8_MIN INT8_MIN\000"
.LASF726:
	.ascii	"INT_FAST8_MIN INT8_MIN\000"
.LASF149:
	.ascii	"__FLT_MIN_EXP__ (-125)\000"
.LASF244:
	.ascii	"__FLT64_HAS_QUIET_NAN__ 1\000"
.LASF787:
	.ascii	"bufferlength\000"
.LASF607:
	.ascii	"__SEGGER_RTL_U16 unsigned short\000"
.LASF448:
	.ascii	"__ARM_ARCH_7EM__ 1\000"
.LASF242:
	.ascii	"__FLT64_HAS_DENORM__ 1\000"
.LASF338:
	.ascii	"__ULLACCUM_IBIT__ 32\000"
.LASF39:
	.ascii	"__UINTMAX_TYPE__ long long unsigned int\000"
.LASF377:
	.ascii	"__UTA_IBIT__ 64\000"
.LASF755:
	.ascii	"UINTMAX_C(x) (x ##uLL)\000"
.LASF143:
	.ascii	"__FLT_EVAL_METHOD__ 0\000"
.LASF811:
	.ascii	"app_uart_ringbuffer_GetDataFormBuffer\000"
.LASF70:
	.ascii	"__SCHAR_MAX__ 0x7f\000"
.LASF127:
	.ascii	"__INT_FAST8_WIDTH__ 32\000"
.LASF2:
	.ascii	"__STDC_UTF_16__ 1\000"
.LASF489:
	.ascii	"uECC_OPTIMIZATION_LEVEL 3\000"
.LASF414:
	.ascii	"__ARM_FEATURE_LDREX\000"
.LASF109:
	.ascii	"__INT_LEAST16_MAX__ 0x7fff\000"
.LASF352:
	.ascii	"__UQQ_FBIT__ 8\000"
.LASF199:
	.ascii	"__FLT16_MIN_EXP__ (-13)\000"
.LASF594:
	.ascii	"__WIDTH_NONE 0\000"
.LASF511:
	.ascii	"__SEGGER_RTL_UNALIGNED_RW_FAULTS 0\000"
.LASF285:
	.ascii	"__LFRACT_MAX__ 0X7FFFFFFFP-31LR\000"
.LASF503:
	.ascii	"__SEGGER_RTL_ISA_ARM 2\000"
.LASF0:
	.ascii	"__STDC__ 1\000"
.LASF679:
	.ascii	"__SEGGER_RTL_MAX_CATEGORY 5\000"
.LASF467:
	.ascii	"__ARM_ARCH_FPV4_SP_D16__ 1\000"
.LASF501:
	.ascii	"__SEGGER_RTL_ISA_T16 0\000"
.LASF642:
	.ascii	"__SEGGER_RTL_LOCALE_THREAD \000"
.LASF30:
	.ascii	"__FLOAT_WORD_ORDER__ __ORDER_LITTLE_ENDIAN__\000"
.LASF47:
	.ascii	"__UINT8_TYPE__ unsigned char\000"
.LASF173:
	.ascii	"__DBL_MIN__ ((double)1.1)\000"
.LASF630:
	.ascii	"__SEGGER_RTL_FORMAT_INT_WIDTH __WIDTH_LONG_LONG\000"
.LASF456:
	.ascii	"__ARM_FEATURE_COPROC 15\000"
.LASF808:
	.ascii	"app_uart_ringbuff_data_check\000"
.LASF82:
	.ascii	"__SHRT_WIDTH__ 16\000"
.LASF799:
	.ascii	"loop1\000"
.LASF372:
	.ascii	"__USA_FBIT__ 16\000"
.LASF248:
	.ascii	"__FLT32X_MIN_EXP__ (-1021)\000"
.LASF161:
	.ascii	"__FLT_HAS_QUIET_NAN__ 1\000"
.LASF696:
	.ascii	"__SEGGER_RTL_LOCALE_T_DEFINED \000"
.LASF286:
	.ascii	"__LFRACT_EPSILON__ 0x1P-31LR\000"
.LASF569:
	.ascii	"__SEGGER_RTL_ZBYTE_INDEX(X) __SEGGER_RTL_ZBYTE_INDE"
	.ascii	"X_func(X)\000"
.LASF172:
	.ascii	"__DBL_NORM_MAX__ ((double)1.1)\000"
.LASF419:
	.ascii	"__ARM_SIZEOF_MINIMAL_ENUM 1\000"
.LASF545:
	.ascii	"__SEGGER_RTL_CORE_HAS_MOVW_MOVT 1\000"
.LASF423:
	.ascii	"__arm__ 1\000"
.LASF532:
	.ascii	"__SEGGER_RTL_NEVER_INLINE __attribute__((__noinline"
	.ascii	"__, __noclone__))\000"
.LASF216:
	.ascii	"__FLT32_MIN_10_EXP__ (-37)\000"
.LASF523:
	.ascii	"__SEGGER_RTL_SMULL(lo,hi,x0,x1) do { __asm__( \"smu"
	.ascii	"ll %0, %1, %2, %3\" : \"=r\"(lo), \"=r\"(hi) : \"r\""
	.ascii	"((unsigned)(x0)), \"r\"((unsigned)(x1)) ); } while "
	.ascii	"(0)\000"
.LASF613:
	.ascii	"__SEGGER_RTL_LEAST_I16 int\000"
.LASF438:
	.ascii	"__ARM_FP16_FORMAT_ALTERNATIVE\000"
.LASF756:
	.ascii	"WCHAR_MAX __WCHAR_MAX__\000"
.LASF704:
	.ascii	"INT32_MAX 2147483647L\000"
.LASF789:
	.ascii	"buffertocopy\000"
.LASF25:
	.ascii	"__BIGGEST_ALIGNMENT__ 8\000"
.LASF717:
	.ascii	"INT_LEAST16_MAX INT16_MAX\000"
.LASF369:
	.ascii	"__TA_IBIT__ 64\000"
.LASF651:
	.ascii	"__SEGGER_RTL_DIVMOD_U64(Q,R,N,D) do { Q = N / D; R "
	.ascii	"= N - Q*D; } while (0)\000"
.LASF407:
	.ascii	"__ARM_FEATURE_QRDMX\000"
.LASF603:
	.ascii	"__SEGGER_RTL_U64 unsigned long long\000"
.LASF587:
	.ascii	"__SEGGER_RTL_SIGNAL_SIG_IGN __aeabi_SIG_IGN\000"
.LASF74:
	.ascii	"__LONG_LONG_MAX__ 0x7fffffffffffffffLL\000"
.LASF197:
	.ascii	"__FLT16_MANT_DIG__ 11\000"
.LASF87:
	.ascii	"__WINT_WIDTH__ 32\000"
.LASF666:
	.ascii	"__SEGGER_RTL_INFINITY __builtin_inff()\000"
.LASF278:
	.ascii	"__UFRACT_IBIT__ 0\000"
.LASF411:
	.ascii	"__ARM_32BIT_STATE 1\000"
.LASF107:
	.ascii	"__INT8_C(c) c\000"
.LASF283:
	.ascii	"__LFRACT_IBIT__ 0\000"
.LASF533:
	.ascii	"__SEGGER_RTL_ALWAYS_INLINE __inline__ __attribute__"
	.ascii	"((__always_inline__))\000"
.LASF480:
	.ascii	"FLOAT_ABI_HARD 1\000"
.LASF753:
	.ascii	"UINT64_C(x) (x ##uLL)\000"
.LASF166:
	.ascii	"__DBL_MIN_EXP__ (-1021)\000"
.LASF637:
	.ascii	"__SEGGER_RTL_MINIMAL_LOCALE 0\000"
.LASF658:
	.ascii	"__SEGGER_RTL_CLZ_U64_SYNTHESIZED \000"
.LASF500:
	.ascii	"__SEGGER_RTL_ARM_CONF_H \000"
.LASF214:
	.ascii	"__FLT32_DIG__ 6\000"
.LASF730:
	.ascii	"INT_FAST32_MIN INT32_MIN\000"
.LASF737:
	.ascii	"UINT_FAST64_MAX UINT64_MAX\000"
.LASF645:
	.ascii	"__SEGGER_RTL_BitcastToF32(X) __SEGGER_RTL_BitcastTo"
	.ascii	"F32_inline(X)\000"
.LASF563:
	.ascii	"__SEGGER_RTL_I2P(X) ((void *)(X))\000"
.LASF193:
	.ascii	"__LDBL_HAS_DENORM__ 1\000"
.LASF397:
	.ascii	"__HAVE_SPECULATION_SAFE_VALUE 1\000"
.LASF302:
	.ascii	"__SACCUM_FBIT__ 7\000"
.LASF385:
	.ascii	"__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 1\000"
.LASF517:
	.ascii	"__SEGGER_RTL_FP_HW 1\000"
.LASF564:
	.ascii	"__SEGGER_RTL_ALIGN_PTR(X) (void *)(X)\000"
.LASF314:
	.ascii	"__ACCUM_MIN__ (-0X1P15K-0X1P15K)\000"
.LASF405:
	.ascii	"__ARM_FEATURE_CRYPTO\000"
.LASF53:
	.ascii	"__INT_LEAST32_TYPE__ long int\000"
.LASF473:
	.ascii	"__NO_AEABI_ERR__ 1\000"
.LASF431:
	.ascii	"__ARM_ARCH_ISA_THUMB\000"
.LASF124:
	.ascii	"__UINT_LEAST64_MAX__ 0xffffffffffffffffULL\000"
.LASF273:
	.ascii	"__FRACT_IBIT__ 0\000"
.LASF790:
	.ascii	"loop\000"
.LASF245:
	.ascii	"__FLT64_IS_IEC_60559__ 2\000"
.LASF634:
	.ascii	"__SEGGER_RTL_FORMAT_CHAR_CLASS 1\000"
.LASF26:
	.ascii	"__ORDER_LITTLE_ENDIAN__ 1234\000"
.LASF561:
	.ascii	"__SEGGER_RTL_X_errno_addr __aeabi_errno_addr\000"
.LASF773:
	.ascii	"long long unsigned int\000"
.LASF150:
	.ascii	"__FLT_MIN_10_EXP__ (-37)\000"
.LASF715:
	.ascii	"INT_LEAST8_MAX INT8_MAX\000"
.LASF687:
	.ascii	"SEEK_CUR 1\000"
.LASF719:
	.ascii	"INT_LEAST32_MAX INT32_MAX\000"
.LASF71:
	.ascii	"__SHRT_MAX__ 0x7fff\000"
.LASF196:
	.ascii	"__LDBL_IS_IEC_60559__ 2\000"
.LASF341:
	.ascii	"__ULLACCUM_EPSILON__ 0x1P-32ULLK\000"
.LASF426:
	.ascii	"__APCS_32__ 1\000"
.LASF348:
	.ascii	"__DQ_FBIT__ 63\000"
.LASF568:
	.ascii	"__SEGGER_RTL_ZBYTE_CHECK(X) __SEGGER_RTL_ZBYTE_CHEC"
	.ascii	"K_func(X)\000"
.LASF355:
	.ascii	"__UHQ_IBIT__ 0\000"
.LASF479:
	.ascii	"CONFIG_GPIO_AS_PINRESET 1\000"
.LASF604:
	.ascii	"__SEGGER_RTL_I64 long long\000"
.LASF60:
	.ascii	"__INT_FAST16_TYPE__ int\000"
.LASF540:
	.ascii	"__SEGGER_RTL_CORE_HAS_ISA_SIMD32 1\000"
.LASF290:
	.ascii	"__ULFRACT_MAX__ 0XFFFFFFFFP-32ULR\000"
.LASF478:
	.ascii	"BOARD_PCA10040 1\000"
.LASF56:
	.ascii	"__UINT_LEAST16_TYPE__ short unsigned int\000"
.LASF157:
	.ascii	"__FLT_EPSILON__ 1.1\000"
.LASF325:
	.ascii	"__LACCUM_MAX__ 0X7FFFFFFFFFFFFFFFP-31LK\000"
.LASF40:
	.ascii	"__CHAR16_TYPE__ short unsigned int\000"
.LASF728:
	.ascii	"INT_FAST16_MIN INT32_MIN\000"
.LASF247:
	.ascii	"__FLT32X_DIG__ 15\000"
.LASF156:
	.ascii	"__FLT_MIN__ 1.1\000"
.LASF205:
	.ascii	"__FLT16_NORM_MAX__ 1.1\000"
.LASF336:
	.ascii	"__LLACCUM_EPSILON__ 0x1P-31LLK\000"
.LASF15:
	.ascii	"__FINITE_MATH_ONLY__ 0\000"
.LASF128:
	.ascii	"__INT_FAST16_MAX__ 0x7fffffff\000"
.LASF639:
	.ascii	"__SEGGER_RTL_ATEXIT_COUNT 1\000"
.LASF19:
	.ascii	"__SIZEOF_SHORT__ 2\000"
.LASF609:
	.ascii	"__SEGGER_RTL_U8 unsigned char\000"
.LASF330:
	.ascii	"__ULACCUM_MAX__ 0XFFFFFFFFFFFFFFFFP-32ULK\000"
.LASF628:
	.ascii	"__SEGGER_RTL_SIZEOF_LDOUBLE 8\000"
.LASF289:
	.ascii	"__ULFRACT_MIN__ 0.0ULR\000"
.LASF483:
	.ascii	"NO_VTOR_CONFIG 1\000"
.LASF349:
	.ascii	"__DQ_IBIT__ 0\000"
.LASF700:
	.ascii	"INT8_MAX 127\000"
.LASF462:
	.ascii	"__ARM_BF16_FORMAT_ALTERNATIVE\000"
.LASF45:
	.ascii	"__INT32_TYPE__ long int\000"
.LASF817:
	.ascii	"F:\\nRF5_SDK_17.1.0_ddde560\\examples\\Myproject\\t"
	.ascii	"emplate_project_combine\\pca10040\\blank\\ses\000"
.LASF662:
	.ascii	"__SEGGER_RTL_U64_L(X) ((__SEGGER_RTL_U32)(__SEGGER_"
	.ascii	"RTL_U64)(X))\000"
.LASF675:
	.ascii	"__SEGGER_RTL_CORE_HAS_IDIV_X 0\000"
.LASF620:
	.ascii	"__SEGGER_RTL_SIZEOF_INT 4\000"
.LASF784:
	.ascii	"memset\000"
.LASF621:
	.ascii	"__SEGGER_RTL_SIZEOF_LONG 4\000"
.LASF475:
	.ascii	"DEBUG_NRF 1\000"
.LASF521:
	.ascii	"__SEGGER_RTL_CORE_HAS_EXT_MUL 1\000"
.LASF725:
	.ascii	"UINT_LEAST64_MAX UINT64_MAX\000"
.LASF608:
	.ascii	"__SEGGER_RTL_I16 short\000"
.LASF361:
	.ascii	"__UTQ_IBIT__ 0\000"
.LASF364:
	.ascii	"__SA_FBIT__ 15\000"
.LASF296:
	.ascii	"__LLFRACT_EPSILON__ 0x1P-63LLR\000"
.LASF554:
	.ascii	"__SEGGER_RTL_USE_FPU_FOR_IDIV 0\000"
.LASF450:
	.ascii	"__ARM_EABI__ 1\000"
.LASF471:
	.ascii	"_LIBCPP_HAS_NO_THREADS 1\000"
.LASF592:
	.ascii	"__WIDTH_LONG 1\000"
.LASF464:
	.ascii	"__ELF__ 1\000"
.LASF163:
	.ascii	"__FLT_IS_IEC_60559__ 2\000"
.LASF430:
	.ascii	"__THUMBEL__ 1\000"
.LASF402:
	.ascii	"__ARM_FEATURE_DSP 1\000"
.LASF693:
	.ascii	"__SEGGER_RTL_SIZE_T_DEFINED \000"
.LASF343:
	.ascii	"__QQ_IBIT__ 0\000"
.LASF692:
	.ascii	"_IONBF 2\000"
.LASF713:
	.ascii	"UINTMAX_MAX UINT64_MAX\000"
.LASF670:
	.ascii	"__SEGGER_RTL_HIDE(X) __c_ ##X\000"
.LASF525:
	.ascii	"__SEGGER_RTL_UMULL_HI(x0,x1) ({ unsigned long __tra"
	.ascii	"sh, __hi; __asm__( \"umull %0, %1, %2, %3\" : \"=r\""
	.ascii	"(__trash), \"=r\"(__hi) : \"r\"((unsigned)(x0)), \""
	.ascii	"r\"((unsigned)(x1)) ); __hi; })\000"
.LASF332:
	.ascii	"__LLACCUM_FBIT__ 31\000"
.LASF357:
	.ascii	"__USQ_IBIT__ 0\000"
.LASF582:
	.ascii	"__SEGGER_RTL_SIGNAL_SIGINT __aeabi_SIGINT\000"
.LASF57:
	.ascii	"__UINT_LEAST32_TYPE__ long unsigned int\000"
.LASF417:
	.ascii	"__ARM_FEATURE_NUMERIC_MAXMIN\000"
.LASF495:
	.ascii	"_LIBCPP_CONFIG \000"
.LASF38:
	.ascii	"__INTMAX_TYPE__ long long int\000"
.LASF270:
	.ascii	"__USFRACT_MAX__ 0XFFP-8UHR\000"
.LASF392:
	.ascii	"__GCC_ATOMIC_INT_LOCK_FREE 2\000"
.LASF636:
	.ascii	"__SEGGER_RTL_FORMAT_WIDTH_PRECISION\000"
.LASF681:
	.ascii	"__SEGGER_RTL_SIZE_MAX 4294967295uL\000"
.LASF440:
	.ascii	"__ARM_FEATURE_FP16_SCALAR_ARITHMETIC\000"
.LASF311:
	.ascii	"__USACCUM_EPSILON__ 0x1P-8UHK\000"
.LASF178:
	.ascii	"__DBL_HAS_QUIET_NAN__ 1\000"
.LASF295:
	.ascii	"__LLFRACT_MAX__ 0X7FFFFFFFFFFFFFFFP-63LLR\000"
.LASF406:
	.ascii	"__ARM_FEATURE_UNALIGNED 1\000"
.LASF581:
	.ascii	"__SEGGER_RTL_SIGNAL_SIGILL __aeabi_SIGILL\000"
.LASF760:
	.ascii	"BUFFER_SIZE 1024U\000"
.LASF305:
	.ascii	"__SACCUM_MAX__ 0X7FFFP-7HK\000"
.LASF67:
	.ascii	"__INTPTR_TYPE__ int\000"
.LASF68:
	.ascii	"__UINTPTR_TYPE__ unsigned int\000"
.LASF502:
	.ascii	"__SEGGER_RTL_ISA_T32 1\000"
.LASF165:
	.ascii	"__DBL_DIG__ 15\000"
.LASF291:
	.ascii	"__ULFRACT_EPSILON__ 0x1P-32ULR\000"
.LASF557:
	.ascii	"__SEGGER_RTL_LDOUBLE_C_COMPLEX long double _Complex"
	.ascii	"\000"
.LASF586:
	.ascii	"__SEGGER_RTL_SIGNAL_SIG_ERR __aeabi_SIG_ERR\000"
.LASF804:
	.ascii	"buffertosave\000"
.LASF802:
	.ascii	"app_uart_ringbuffer_get_after\000"
.LASF23:
	.ascii	"__SIZEOF_SIZE_T__ 4\000"
.LASF633:
	.ascii	"__SEGGER_RTL_FORMAT_WIDTH_PRECISION 1\000"
.LASF600:
	.ascii	"__SEGGER_RTL_INCLUDE_GNU_API 0\000"
.LASF116:
	.ascii	"__INT64_C(c) c ## LL\000"
.LASF183:
	.ascii	"__LDBL_MIN_10_EXP__ (-307)\000"
.LASF544:
	.ascii	"__SEGGER_RTL_CORE_HAS_ADDW_SUBW 1\000"
.LASF617:
	.ascii	"__SEGGER_RTL_U32_C(X) X ##u\000"
.LASF457:
	.ascii	"__ARM_FEATURE_CDE\000"
.LASF313:
	.ascii	"__ACCUM_IBIT__ 16\000"
.LASF649:
	.ascii	"__SEGGER_RTL_SMULL_X_SYNTHESIZED \000"
.LASF732:
	.ascii	"INT_FAST64_MIN INT64_MIN\000"
.LASF769:
	.ascii	"short int\000"
.LASF121:
	.ascii	"__UINT16_C(c) c\000"
.LASF401:
	.ascii	"__SIZEOF_PTRDIFF_T__ 4\000"
.LASF786:
	.ascii	"stringlength\000"
.LASF375:
	.ascii	"__UDA_IBIT__ 32\000"
.LASF381:
	.ascii	"__NO_INLINE__ 1\000"
.LASF504:
	.ascii	"__SEGGER_RTL_NO_BUILTIN __attribute__((optimize(\"-"
	.ascii	"fno-tree-loop-distribute-patterns\")))\000"
.LASF455:
	.ascii	"__ARM_FEATURE_COPROC\000"
.LASF177:
	.ascii	"__DBL_HAS_INFINITY__ 1\000"
.LASF95:
	.ascii	"__SIG_ATOMIC_MAX__ 0x7fffffff\000"
.LASF230:
	.ascii	"__FLT64_MANT_DIG__ 53\000"
.LASF794:
	.ascii	"buffercopyinto\000"
.LASF452:
	.ascii	"__ARM_ARCH_EXT_IDIV__ 1\000"
.LASF657:
	.ascii	"__SEGGER_RTL_CLZ_U64(X) __SEGGER_RTL_CLZ_U64_inline"
	.ascii	"(X)\000"
.LASF496:
	.ascii	"__SEGGER_RTL_STDIO_H \000"
.LASF537:
	.ascii	"__SEGGER_RTL_FLOAT32_SQRT(__m) ({ float __d; __asm_"
	.ascii	"_ __volatile__(\"vsqrt.f32 %[d], %[m]\" : [d] \"=t\""
	.ascii	"(__d) : [m] \"t\"(__m)); __d; })\000"
.LASF327:
	.ascii	"__ULACCUM_FBIT__ 32\000"
.LASF721:
	.ascii	"INT_LEAST64_MAX INT64_MAX\000"
.LASF682:
	.ascii	"NULL 0\000"
.LASF744:
	.ascii	"WINT_MIN (-2147483647L-1)\000"
.LASF99:
	.ascii	"__INT16_MAX__ 0x7fff\000"
.LASF387:
	.ascii	"__GCC_ATOMIC_CHAR_LOCK_FREE 2\000"
.LASF759:
	.ascii	"__SEGGER_RTL_STRING_H \000"
.LASF83:
	.ascii	"__INT_WIDTH__ 32\000"
.LASF418:
	.ascii	"__ARM_FEATURE_SIMD32 1\000"
.LASF220:
	.ascii	"__FLT32_MAX__ 1.1\000"
.LASF776:
	.ascii	"data_type\000"
.LASF301:
	.ascii	"__ULLFRACT_EPSILON__ 0x1P-64ULLR\000"
.LASF312:
	.ascii	"__ACCUM_FBIT__ 15\000"
.LASF97:
	.ascii	"__SIG_ATOMIC_WIDTH__ 32\000"
.LASF618:
	.ascii	"__SEGGER_RTL_I64_C(X) X ##LL\000"
.LASF616:
	.ascii	"__SEGGER_RTL_I32_C(X) X\000"
.LASF282:
	.ascii	"__LFRACT_FBIT__ 31\000"
.LASF632:
	.ascii	"__SEGGER_RTL_FORMAT_WCHAR 1\000"
.LASF697:
	.ascii	"_LIBCPP_STDINT_H \000"
.LASF400:
	.ascii	"__SIZEOF_WINT_T__ 4\000"
.LASF538:
	.ascii	"__SEGGER_RTL_CORE_HAS_CLZ 1\000"
.LASF783:
	.ascii	"strlen\000"
.LASF463:
	.ascii	"__GXX_TYPEINFO_EQUALITY_INLINE 0\000"
.LASF187:
	.ascii	"__LDBL_DECIMAL_DIG__ 17\000"
.LASF671:
	.ascii	"__SEGGER_RTL_RODATA const\000"
.LASF567:
	.ascii	"__SEGGER_RTL_WORD unsigned\000"
.LASF324:
	.ascii	"__LACCUM_MIN__ (-0X1P31LK-0X1P31LK)\000"
.LASF571:
	.ascii	"__SEGGER_RTL_DIFF_BYTE(X,N) __SEGGER_RTL_DIFF_BYTE_"
	.ascii	"func(X, N)\000"
.LASF126:
	.ascii	"__INT_FAST8_MAX__ 0x7fffffff\000"
.LASF225:
	.ascii	"__FLT32_HAS_DENORM__ 1\000"
.LASF208:
	.ascii	"__FLT16_DENORM_MIN__ 1.1\000"
.LASF339:
	.ascii	"__ULLACCUM_MIN__ 0.0ULLK\000"
.LASF131:
	.ascii	"__INT_FAST32_WIDTH__ 32\000"
.LASF708:
	.ascii	"UINT16_MAX 65535\000"
.LASF454:
	.ascii	"__ARM_ASM_SYNTAX_UNIFIED__ 1\000"
.LASF488:
	.ascii	"uECC_ENABLE_VLI_API 0\000"
.LASF796:
	.ascii	"endstringlength\000"
.LASF49:
	.ascii	"__UINT32_TYPE__ long unsigned int\000"
.LASF409:
	.ascii	"__ARM_FEATURE_DOTPROD\000"
.LASF734:
	.ascii	"UINT_FAST8_MAX UINT8_MAX\000"
.LASF449:
	.ascii	"__ARM_PCS_VFP 1\000"
.LASF437:
	.ascii	"__ARM_FP16_FORMAT_IEEE 1\000"
.LASF299:
	.ascii	"__ULLFRACT_MIN__ 0.0ULLR\000"
.LASF711:
	.ascii	"INTMAX_MIN INT64_MIN\000"
.LASF16:
	.ascii	"__SIZEOF_INT__ 4\000"
.LASF293:
	.ascii	"__LLFRACT_IBIT__ 0\000"
.LASF294:
	.ascii	"__LLFRACT_MIN__ (-0.5LLR-0.5LLR)\000"
.LASF706:
	.ascii	"INT64_MAX 9223372036854775807LL\000"
.LASF509:
	.ascii	"__SEGGER_RTL_STRING_ASM 1\000"
.LASF198:
	.ascii	"__FLT16_DIG__ 3\000"
.LASF432:
	.ascii	"__ARM_ARCH_ISA_THUMB 2\000"
.LASF520:
	.ascii	"__SEGGER_RTL_CORE_HAS_MLS 1\000"
.LASF665:
	.ascii	"__SEGGER_RTL_I64_L(X) ((__SEGGER_RTL_U32)(__SEGGER_"
	.ascii	"RTL_U64)(X))\000"
.LASF436:
	.ascii	"__ARM_FP 4\000"
.LASF64:
	.ascii	"__UINT_FAST16_TYPE__ unsigned int\000"
.LASF510:
	.ascii	"__SEGGER_RTL_BYTE_ORDER (-1)\000"
.LASF371:
	.ascii	"__UHA_IBIT__ 8\000"
.LASF316:
	.ascii	"__ACCUM_EPSILON__ 0x1P-15K\000"
.LASF331:
	.ascii	"__ULACCUM_EPSILON__ 0x1P-32ULK\000"
.LASF664:
	.ascii	"__SEGGER_RTL_I64_H(X) ((__SEGGER_RTL_I32)((__SEGGER"
	.ascii	"_RTL_I64)(X) >> 32))\000"
.LASF181:
	.ascii	"__LDBL_DIG__ 15\000"
.LASF597:
	.ascii	"__SEGGER_RTL_SIDE_BY_SIDE 0\000"
.LASF89:
	.ascii	"__SIZE_WIDTH__ 32\000"
.LASF78:
	.ascii	"__WINT_MIN__ 0U\000"
.LASF231:
	.ascii	"__FLT64_DIG__ 15\000"
.LASF77:
	.ascii	"__WINT_MAX__ 0xffffffffU\000"
.LASF108:
	.ascii	"__INT_LEAST8_WIDTH__ 8\000"
.LASF484:
	.ascii	"NRF52 1\000"
.LASF531:
	.ascii	"__SEGGER_RTL_THREAD __thread\000"
.LASF52:
	.ascii	"__INT_LEAST16_TYPE__ short int\000"
.LASF342:
	.ascii	"__QQ_FBIT__ 7\000"
.LASF188:
	.ascii	"__LDBL_MAX__ 1.1\000"
.LASF771:
	.ascii	"short unsigned int\000"
.LASF292:
	.ascii	"__LLFRACT_FBIT__ 63\000"
.LASF226:
	.ascii	"__FLT32_HAS_INFINITY__ 1\000"
.LASF207:
	.ascii	"__FLT16_EPSILON__ 1.1\000"
.LASF669:
	.ascii	"__SEGGER_RTL_HUGE_VALF __builtin_huge_valf()\000"
.LASF668:
	.ascii	"__SEGGER_RTL_HUGE_VAL __builtin_huge_val()\000"
.LASF433:
	.ascii	"__ARMEL__ 1\000"
.LASF596:
	.ascii	"__WIDTH_DOUBLE 2\000"
.LASF663:
	.ascii	"__SEGGER_RTL_U64_MK(H,L) (((__SEGGER_RTL_U64)(__SEG"
	.ascii	"GER_RTL_U32)(H) << 32) + (__SEGGER_RTL_U32)(L))\000"
.LASF530:
	.ascii	"__SEGGER_RTL_LIKELY(X) __builtin_expect((X), 1)\000"
.LASF344:
	.ascii	"__HQ_FBIT__ 15\000"
.LASF625:
	.ascii	"__SEGGER_RTL_WINT_T __WINT_TYPE__\000"
.LASF559:
	.ascii	"__SEGGER_RTL_VA_LIST __builtin_va_list\000"
.LASF315:
	.ascii	"__ACCUM_MAX__ 0X7FFFFFFFP-15K\000"
.LASF80:
	.ascii	"__SIZE_MAX__ 0xffffffffU\000"
.LASF611:
	.ascii	"__SEGGER_RTL_LEAST_U32 unsigned\000"
.LASF337:
	.ascii	"__ULLACCUM_FBIT__ 32\000"
.LASF424:
	.ascii	"__ARM_ARCH\000"
.LASF221:
	.ascii	"__FLT32_NORM_MAX__ 1.1\000"
.LASF73:
	.ascii	"__LONG_MAX__ 0x7fffffffL\000"
.LASF809:
	.ascii	"state\000"
.LASF650:
	.ascii	"__SEGGER_RTL_DIVMOD_U32(Q,R,N,D) do { Q = N / D; R "
	.ascii	"= N - Q*D; } while (0)\000"
.LASF415:
	.ascii	"__ARM_FEATURE_LDREX 7\000"
.LASF814:
	.ascii	"app_uart_ringbuffer_init\000"
.LASF513:
	.ascii	"__SEGGER_RTL_ADDRSIZE 32\000"
.LASF34:
	.ascii	"__SIZE_TYPE__ unsigned int\000"
.LASF553:
	.ascii	"__SEGGER_RTL_FAST_CODE_SECTION(X) __attribute__((__"
	.ascii	"section__(\".fast.\" X)))\000"
.LASF508:
	.ascii	"__SEGGER_RTL_INCLUDE_GNU_FP16_API 1\000"
.LASF265:
	.ascii	"__SFRACT_MAX__ 0X7FP-7HR\000"
.LASF676:
	.ascii	"__SEGGER_RTL_CORE_HAS_UDIVM_X 0\000"
.LASF209:
	.ascii	"__FLT16_HAS_DENORM__ 1\000"
.LASF506:
	.ascii	"__SEGGER_RTL_TARGET_ISA __SEGGER_RTL_ISA_T32\000"
.LASF110:
	.ascii	"__INT16_C(c) c\000"
.LASF585:
	.ascii	"__SEGGER_RTL_SIGNAL_SIG_DFL __aeabi_SIG_DFL\000"
.LASF211:
	.ascii	"__FLT16_HAS_QUIET_NAN__ 1\000"
.LASF641:
	.ascii	"__SEGGER_RTL_STATE_THREAD __SEGGER_RTL_THREAD\000"
.LASF13:
	.ascii	"__ATOMIC_ACQ_REL 4\000"
.LASF345:
	.ascii	"__HQ_IBIT__ 0\000"
.LASF167:
	.ascii	"__DBL_MIN_10_EXP__ (-307)\000"
.LASF800:
	.ascii	"loop2\000"
.LASF807:
	.ascii	"data\000"
.LASF736:
	.ascii	"UINT_FAST32_MAX UINT32_MAX\000"
.LASF306:
	.ascii	"__SACCUM_EPSILON__ 0x1P-7HK\000"
.LASF240:
	.ascii	"__FLT64_EPSILON__ 1.1\000"
.LASF92:
	.ascii	"__UINTMAX_MAX__ 0xffffffffffffffffULL\000"
.LASF164:
	.ascii	"__DBL_MANT_DIG__ 53\000"
.LASF288:
	.ascii	"__ULFRACT_IBIT__ 0\000"
.LASF718:
	.ascii	"INT_LEAST32_MIN INT32_MIN\000"
.LASF72:
	.ascii	"__INT_MAX__ 0x7fffffff\000"
.LASF54:
	.ascii	"__INT_LEAST64_TYPE__ long long int\000"
.LASF743:
	.ascii	"UINTPTR_MAX UINT32_MAX\000"
.LASF747:
	.ascii	"INT16_C(x) (x)\000"
.LASF458:
	.ascii	"__ARM_FEATURE_CDE_COPROC\000"
.LASF722:
	.ascii	"UINT_LEAST8_MAX UINT8_MAX\000"
	.ident	"GCC: (based on arm-11.2-2022.02 GCC) 11.2.1 20220111"
