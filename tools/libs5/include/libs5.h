/*
 * libs5
 * Synthesis's Standalone Simple Sprite System
 * version 0.2
 * Code: Synthesis
 *
 */

#ifndef _libs5_h_
#define _libs5_h_

#include <nds/ndstypes.h>

#ifdef __cplusplus
extern "C" {
#endif

	// Sprite attributes for main screen
#define SPR_AT0(spr) (*(uint16*)(0x07000000 + (spr << 3)))
#define SPR_AT1(spr) (*(uint16*)(0x07000002 + (spr << 3)))
#define SPR_AT2(spr) (*(uint16*)(0x07000004 + (spr << 3)))

	// Sprite attributes for sub screen
#define SPR_AT0_SUB(spr) (*(uint16*)(0x07000400 + (spr << 3)))
#define SPR_AT1_SUB(spr) (*(uint16*)(0x07000402 + (spr << 3)))
#define SPR_AT2_SUB(spr) (*(uint16*)(0x07000404 + (spr << 3)))


	// Enumerations
typedef enum {
	SprSize_8x8		= 0,
	SprSize_16x8	= 1,
	SprSize_8x16	= 2,
	SprSize_16x16	= 4,
	SprSize_32x8	= 5,
	SprSize_8x32	= 6,
	SprSize_32x32	= 8,
	SprSize_32x16	= 9,
	SprSize_16x32	= 10,
	SprSize_64x64   = 12,
	SprSize_64x32	= 13,
	SprSize_32x64	= 14
} s5_dimension;

typedef enum {
	SprColors_16		= 0,
	SprColors_256		= 1
} s5_colors;

typedef enum {
	VramBankF	= 0,
	VramBankG   = 1,
	VramBankI   = 2
} s5_vramBank;


	// Sprite-related functions
/* screen: 0 = main, 1 = sub
 * extPalettes: 0 = not used, 1 = used
 */
void enableSprites(u8 screen, u8 extPalettes);

void clearSprite(u8 screen, u8 sprId);
/* baseTile corresponds to the first tile of the sprite in OVRAM
 * usesAlpha: 0 disables sprite alpha, 1 enables it
 */
void drawSprite(u8 screen, u8 sprId, u16 x, u16 y, s5_dimension dimension,
		s5_colors colors, u16 baseTile, u8 palette);

void moveSprite(u8 screen, u8 sprId, u16 x, u16 y);
u16 getSpriteX(u8 screen, u8 sprId);
u16 getSpriteY(u8 screen, u8 sprId);

/* priority is in range 0..3 */
void setSpritePriority(u8 screen, u8 sprId, u8 priority);
/* hFlip and vFlip: 0 disables flipping, 1 enables it */
void setSpriteFlip(u8 screen, u8 sprId, u8 hFlip, u8 vFlip);
void setSpritePalette(u8 screen, u8 sprId, u8 palette);

void enableSpriteAlpha(u8 screen, u8 sprId);
void disableSpriteAlpha(u8 screen, u8 sprId);
void enableSpriteMosaic(u8 screen, u8 sprId);
void disableSpriteMosaic(u8 screen, u8 sprId);
void setSpriteMosaic(u8 screen, u8 hSize, u8 vSize);


	// Gfx-related functions
/* baseTile: the first tile index where the data will be copied to.
 *           note: 1 256color tile is equivalent to 2 16color tiles.
 *           That means 256color baseTile = 3 corresponds to 16color baseTile = 6
 */
void loadTiles(u8 screen, u8 baseTile, u8 numberOfTiles, s5_colors format, void* data);
/* slot is in range 0..15 */
void loadPalette(u8 screen, u8 slot, void* palette);
void loadPalette256(u8 screen, void* palette);
/* vramBank: VramBankF or VramBankG for main screen, and VramBankI for sub screen */
void loadExtPalette(s5_vramBank vramBank, u8 slot, void* palette);


#ifdef __cplusplus
}
#endif

#endif
