#include "weapon.h"

char* strlwr(char* str) {
	char* string = str;
	for(i = 0 ; string[i] ; i++) {
		string[i] = tolower(string[i]);
	}
	return string;
}

Weapon::Weapon(const char* icon, int iconSize, char* name, int level) {
	s_name = name;
	s_level = level;
	s_icon = ulLoadImageFilePNG(icon, iconSize, UL_IN_VRAM, UL_PF_PAL8);
	if(!s_icon) {
		ulDebug("unable to load: %s icon\n", name);
	}
}

Weapon::~Weapon() {
	ulDeleteImage(s_icon);
}
