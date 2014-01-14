/*
 * =====================================================================================
 *
 *   Program name:  ZeldaOracle
 *       Filename:  main.c
 *
 *    Description:  ZeldaOracle is a 2D Zelda: Oracle
 *                  of-like engine written in pure C
 *                  with the libnds
 *
 *        Version:  1.0
 *        Created:  06/01/2014 20:31:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <nds.h>
#include "libs5.h"
#include "link.h"
#include "timer.h"
#include "sprite.h"

void video_init()
 {
  videoSetMode(MODE_5_2D);
  videoSetModeSub(MODE_5_2D);
  
  vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
  vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
  vramSetBankC(VRAM_C_SUB_BG_0x06200000);
  vramSetBankD(VRAM_D_SUB_SPRITE);
  
  sprite_system_init();
 }

uint8_t link_animations[12][4] = {
	{4,0},
	{5,1},
	{6,2},
	{7,3}
};

int main(void)
 {
  defaultExceptionHandler();
  
  timer_system_init();
  
  s_sprite *test_sprite;
  
	 video_init();
  
  consoleDemoInit();
  
  test_sprite = sprite_new(SCREEN_UP, 0, SprSize_16x16, 0, 4, 32, 0, linkTiles, linkPal);
  sprite_add_animation(test_sprite, 2, link_animations[0], 100);
  sprite_add_animation(test_sprite, 2, link_animations[1], 100);
  sprite_add_animation(test_sprite, 2, link_animations[2], 100);
  sprite_add_animation(test_sprite, 2, link_animations[3], 100);
  
  while(1)
   {
    sprite_play_animation(test_sprite, 0, 0, 0);
    
	 	 swiWaitForVBlank();
	  }
 }
