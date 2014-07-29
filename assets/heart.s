
@{{BLOCK(heart)

@=======================================================================
@
@	heart, 16x16@4, 
@	Transparent color : 0F,F0,FF
@	4 tiles Metatiled by 2x2 not compressed
@	Total size: 512 + 128 = 640
@
@	Time-stamp: 2014-07-29, 14:32:41
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.12
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global heartTiles		@ 128 unsigned chars
	.hidden heartTiles
heartTiles:
	.word 0x00110110,0x01551551,0x01565651,0x01566651,0x00156510,0x00015100,0x00001000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

@}}BLOCK(heart)
