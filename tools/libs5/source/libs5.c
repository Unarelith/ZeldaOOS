/*
 * libs5
 * Synthesis's Standalone Simple Sprite System
 * version 0.2
 * Code: Synthesis
 *
 */

#include "libs5.h"

void enableSprites(u8 screen, u8 extPalettes)
{
	int id = 0;
	for (id = 0; id < 128; id++)
	{
		clearSprite(screen, id);
	}

	if (screen)
		*(u16*)0x04001000 |= (1 << 12) | (1 << 4) | ((extPalettes & 1) << 31);
	else
		*(u16*)0x04000000 |= (1 << 12) | (1 << 4) | ((extPalettes & 1) << 31);
}

void clearSprite(u8 screen, u8 sprId)
{
	uint16 *attr0 = &(SPR_AT0(sprId)),
			*attr1 = &(SPR_AT1(sprId)),
			*attr2 = &(SPR_AT2(sprId));
	if (screen)
	{
		attr0 = &(SPR_AT0_SUB(sprId));
		attr1 = &(SPR_AT1_SUB(sprId));
		attr2 = &(SPR_AT2_SUB(sprId));
	}

	*attr0 = (2 << 8);
	*attr1 = 0;
	*attr2 = 0;
}

void drawSprite(u8 screen, u8 sprId, u16 x, u16 y, s5_dimension dimension,
		s5_colors colors, u16 baseTile, u8 palette)
{
	// Note: the sprite keeps its priority unless clearSprite(sprId) is called

	uint16 *attr0 = &(SPR_AT0(sprId)),
			*attr1 = &(SPR_AT1(sprId)),
			*attr2 = &(SPR_AT2(sprId));
	if (screen)
	{
		attr0 = &(SPR_AT0_SUB(sprId));
		attr1 = &(SPR_AT1_SUB(sprId));
		attr2 = &(SPR_AT2_SUB(sprId));
	}

	*attr0 = ((colors & 1) << 13) | ((dimension & 3) << 14) | (y & 0x00ff);

	*attr1 = ((dimension & 0xc) << 12) | (x & 0x01ff);

	*attr2 &= (3 << 10);
	*attr2 |= ((palette & 0xf) << 12) | ((baseTile << colors) & 0x03ff);
}

void moveSprite(u8 screen, u8 sprId, u16 x, u16 y)
{
	uint16 *attr0 = &(SPR_AT0(sprId)),
			*attr1 = &(SPR_AT1(sprId));
	if (screen)
	{
		attr0 = &(SPR_AT0_SUB(sprId));
		attr1 = &(SPR_AT1_SUB(sprId));
	}

	*attr0 &= ~0x00ff;
	*attr0 |= (y & 0x00ff);
	*attr1 &= ~0x01ff;
	*attr1 |= (x & 0x01ff);
}

u16 getSpriteX(u8 screen, u8 sprId)
{
	uint16 *attr1 = &(SPR_AT1(sprId));
	if (screen) attr1 = &(SPR_AT1_SUB(sprId));

	return (*attr1) & 0x01ff;
}

u16 getSpriteY(u8 screen, u8 sprId)
{
	uint16 *attr0 = &(SPR_AT0(sprId));
	if (screen) attr0 = &(SPR_AT0_SUB(sprId));

	return (*attr0) & 0x00ff;
}

void setSpritePriority(u8 screen, u8 sprId, u8 priority)
{
	uint16 *attr2 = &(SPR_AT2(sprId));
	if (screen) attr2 = &(SPR_AT2_SUB(sprId));

	*attr2 &= ~(3 << 10);
	*attr2 |= ((priority & 0x3) << 10);
}

void setSpriteFlip(u8 screen, u8 sprId, u8 hFlip, u8 vFlip)
{
	uint16 *attr1 = &(SPR_AT1(sprId));
	if (screen) attr1 = &(SPR_AT1_SUB(sprId));

	*attr1 &= ~(3 << 12);
	*attr1 |= (hFlip ? (1 << 12) : 0) | (vFlip ? (1 << 13) : 0);
}

void setSpritePalette(u8 screen, u8 sprId, u8 palette)
{
	uint16 *attr2 = &(SPR_AT2(sprId));
	if (screen) attr2 = &(SPR_AT2_SUB(sprId));

	*attr2 &= ~(0xf << 12);
	*attr2 |= ((palette & 0xf) << 12);
}

void enableSpriteAlpha(u8 screen, u8 sprId)
{
	uint16 *attr0 = &(SPR_AT0(sprId));
	if (screen) attr0 = &(SPR_AT0_SUB(sprId));

	*attr0 |= (1 << 10);
}

void disableSpriteAlpha(u8 screen, u8 sprId)
{
	uint16 *attr0 = &(SPR_AT0(sprId));
	if (screen) attr0 = &(SPR_AT0_SUB(sprId));

	*attr0 &= ~(1 << 10);
}

void enableSpriteMosaic(u8 screen, u8 sprId)
{
	uint16 *attr0 = &(SPR_AT0(sprId));
	if (screen) attr0 = &(SPR_AT0_SUB(sprId));

	*attr0 |= (1 << 12);
}

void disableSpriteMosaic(u8 screen, u8 sprId)
{
	uint16 *attr0 = &(SPR_AT0(sprId));
	if (screen) attr0 = &(SPR_AT0_SUB(sprId));

	*attr0 &= ~(1 << 12);
}

void setSpriteMosaic(u8 screen, u8 hSize, u8 vSize)
{
	vu16* mosaicReg = (vu16*)0x0400004C;
	if (screen) mosaicReg = (vu16*)0x0400104C;

	*mosaicReg &= 0x00FF;
	*mosaicReg |= ((vSize & 0xF) << 12) | ((hSize & 0xF) << 8);
}
