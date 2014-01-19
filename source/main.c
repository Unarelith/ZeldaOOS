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
#include "timer.h"
#include "animation.h"
#include "sprite.h"
#include "character.h"
#include "player.h"
#include "tileset.h"
#include "map.h"
#include "map_manager.h"
#include "character_manager.h"

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
  
	 video_init();
  
  consoleDemoInit();
  
		map_manager_load_all();
		
		character_manager_init_all();
  
  map_load(g_current_map);
  
  while(1)
   {
    scanKeys();
				
    character_move(g_player);
    
    character_render(g_player);
    
	 	 swiWaitForVBlank();
	  }
		
		character_manager_free_all();
  
		map_manager_free_all();
 }

