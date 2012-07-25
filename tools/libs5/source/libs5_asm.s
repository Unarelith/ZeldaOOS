@ libs5
@ Synthesis's Standalone Simple Sprite System
@ version 0.2
@ Code: Synthesis

.arm
.align

@---------------------------------------------------------------------------------
.global loadTiles
.type	loadTiles STT_FUNC
@---------------------------------------------------------------------------------
loadTiles:
@---------------------------------------------------------------------------------
@	PARAMETERS:
@	r0: screen
@	r1: base tile
@	r2: number of tiles
@	r3: color format custom id (0 for 4bit, 1 for 8bit)
@	Stack: data ptr

	stmfd sp!, {r0-r10}

	mov r4, #0x6400000
	cmp r0, #0
	addne r4, r4, #0x200000
	add r6, r3, #5
	lsl r5, r1, r6
	add r4, r4, r5

	add r6, sp, #44
	ldr r0, [r6]
	mov r1, r4

	lsl r2, r2, r3

@---------------------------------------------------------------------------------
lt_copyLoop:
@---------------------------------------------------------------------------------
	ldmia r0!, {r3-r10}
	stmia r1!, {r3-r10}
	subs r2, r2, #1
	bne lt_copyLoop

	ldmfd sp!, {r0-r10}
	bx lr

@---------------------------------------------------------------------------------
.global loadPalette
.type	loadPalette STT_FUNC
@---------------------------------------------------------------------------------
loadPalette:
@---------------------------------------------------------------------------------
@	PARAMETERS:
@	r0: screen
@	r1: slot
@	r2: data ptr

	stmfd sp!, {r0-r9}

	mov r3, #0x5000000
	add r3, r3, #0x200
	cmp r0, #0
	addne r3, r3, #0x400
	add r3, r3, r1, lsl #5

	mov r0, r2
	mov r1, r3

	ldmia r0!, {r2-r9}
	stmia r1!, {r2-r9}

	ldmfd sp!, {r0-r9}
	bx lr

@---------------------------------------------------------------------------------
.global loadPalette256
.type	loadPalette256 STT_FUNC
@---------------------------------------------------------------------------------
loadPalette256:
@---------------------------------------------------------------------------------
@	PARAMETERS:
@	r0: screen
@	r1: data ptr

	stmfd sp!, {r0-r11}

	mov r3, #0x5000000
	add r3, r3, #0x200
	cmp r0, #0
	addne r3, r3, #0x400

	mov r0, r2
	mov r1, r3

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r9}
	stmia r1!, {r2-r9}

	ldmfd sp!, {r0-r11}
	bx lr


@---------------------------------------------------------------------------------
.global loadExtPalette
.type	loadExtPalette STT_FUNC
@---------------------------------------------------------------------------------
loadExtPalette:
@---------------------------------------------------------------------------------
@	PARAMETERS:
@	r0: vram bank custom id (0 for F, 1 for G, 2 for I)
@	r1: slot
@	r2: data ptr

	stmfd sp!, {r0-r11}

	mov r3, #0x04000000		@ r3 = &VRAM_x_CR
	add r3, r3, #0x200
	add r3, r3, #0x45
	mov r4, #0x80			@ VRAM_ENABLE | VRAM_x_LCD
	add r6, r4, #5			@ VRAM_ENABLE | VRAM_x_SPRITE_EXTENDED_PALETTE
	mov r5, #0x6800000
	add r5, r5, #0x90000

	cmp r0, #1
	addeq r3, r3, #1
	addeq r5, r5, #0x4000

	cmp r0, #2
	addeq r3, r3, #4
	addeq r5, r5, #0x10000
	addeq r6, r4, #3	@ VRAM_ENABLE | VRAM_x_SPRITE_SUB_EXTENDED_PALETTE

	strb r4, [r3]
	push {r3}				@ VRAM_x_CR
	push {r6}				@ VRAM_x_TYPE
	add r5, r5, r1, lsl #9

	mov r0, r2
	mov r1, r5

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}
	ldmia r0!, {r2-r11}
	stmia r1!, {r2-r11}

	ldmia r0!, {r2-r9}
	stmia r1!, {r2-r9}

	pop {r1}				@ VRAM_x_TYPE
	pop {r0}				@ VRAM_x_CR
	strb r1, [r0]

	ldmfd sp!, {r0-r11}
	bx lr

