/*---------------------------------------------------------------------------------

    The Legend of Zelda: Oracle of Secrets
    Copyright (C) 2011 Pixelda quent42340@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

---------------------------------------------------------------------------------*/

#ifndef MAIN_H
#define MAIN_H

extern int i;

#define SCREEN_UP 0
#define SCREEN_DOWN 1

#include <nds.h> // Include libnds header
#include <libs5.h> // s5 lib header
#include <fat.h> // File system
#include <filesystem.h> // Filesystem lib

// Some other headers
#include <time.h> // Used for initializing random seed
#include <stdio.h> // Printing text
#include <malloc.h> // Memory allocation
#include <math.h> // Math functions
#include <string.h> // String functions
#include <vector> // Vector
#include <sys/stat.h>
#include <sys/dir.h>
#include <ctype.h>
#include <dirent.h>

using namespace std;

#include "gfx.h"

#include "timer.h"
#include "sprites.h"
#include "map.h"
#include "player.h"
#include "weapon.h"
#include "mapManager.h"
#include "game.h"

#define WAIT_FOR_START(text) { printf(text); while(!(keysDown() & KEY_START)) { scanKeys(); swiWaitForVBlank(); } }

#endif // MAIN_H
