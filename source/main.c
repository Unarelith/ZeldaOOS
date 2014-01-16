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
#include <stdio.h>
#include <nds.h>
#include <fat.h>
#include <filesystem.h>
#include "libs5.h"
#include "link.h"
#include "timer.h"
#include "sprite.h"
#include "plain.h"
#include "map.h"
#include "character.h"

void video_init()
 {
  videoSetMode(MODE_5_2D);
  videoSetModeSub(MODE_5_2D);
  
  vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
  vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
  vramSetBankC(VRAM_C_SUB_BG_0x06200000);
  vramSetBankD(VRAM_D_SUB_SPRITE);
  
  sprite_system_init();
  
  map_system_init();
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
  
  printf("NitroFS loading...\n");
	 
  if(!nitroFSInit())
   {
    printf("FATAL ERROR: Bad nitroFS init\n");
    while(1)
     {
      swiWaitForVBlank();
     }
   }
  
  printf("NitroFS loaded!\n");
  
  consoleClear();
  
  timer_system_init();
  
  t_character *link;
  
	 video_init();
  
  consoleDemoInit();
  
  link = character_new(SCREEN_UP, 0, 0, direction_down, 0, SprSize_16x16, 0, 4, 32, 0, linkTiles, linkPal);
  sprite_add_animation(link->sprite, 2, link_animations[0], 100);
  sprite_add_animation(link->sprite, 2, link_animations[1], 100);
  sprite_add_animation(link->sprite, 2, link_animations[2], 100);
  sprite_add_animation(link->sprite, 2, link_animations[3], 100);
  
  t_tileset *plain = tileset_new(NULL, plainTiles, plainTilesLen, plainPal, plainPalLen);
  
  t_map *a1 = map_new(plain, "/maps/a1.map", 16, 12, 0, 0, 0);
  
  map_load(a1);
  
  while(1)
   {
    character_render(link);
    
	 	 swiWaitForVBlank();
	  }
  
  map_free(a1);
  
  tileset_free(plain);
  
  character_free(link);
 }
