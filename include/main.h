#ifndef MAIN_H
#define MAIN_H

extern int i;

#define SCREEN_UP 0
#define SCREEN_DOWN 1

#include <nds.h> // Include libnds header
#include <libs5.h> // s5 lib header
#include <ulib/ulib.h>
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
#include "game.h"
#include "player.h"

#define WAIT_FOR_START(text) { printf(text); while(!(keysDown() & KEY_START)) { scanKeys(); swiWaitForVBlank(); } }

#endif // MAIN_H
