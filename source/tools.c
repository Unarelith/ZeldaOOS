/*
	* =====================================================================================
	*
	*       Filename:  tools.c
	*
	*    Description:  Simple tools for nds programming
	*
	*        Version:  1.0
	*        Created:  24/01/2014 13:43:41
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
#include "timer.h"
#include "tools.h"

void       nds_delay(uint32_t delay)
 {
		uint32_t old_time;
		
		old_time = g_os_time;
		while(g_os_time - old_time < delay)
		 {
				swiWaitForVBlank();
			}
	}

