/*
 * =====================================================================================
 *
 *       Filename:  Tileset.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  16/07/2014 13:47:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef TILESET_HPP_
#define TILESET_HPP_

#include <nds.h>

struct Tileset {
	Tileset(u8 *_info, const unsigned int *_tiles, u32 _tilesLength, const u16 *_palette, u32 _palLength) :
		info(_info), tiles(_tiles), tilesLength(_tilesLength), palette(_palette), palLength(_palLength) {}
	
	u8 *info;
	
	const unsigned int *tiles;
	u32 tilesLength;
	
	const u16 *palette;
	u32 palLength;
};

#endif // TILESET_HPP_
