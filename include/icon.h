#ifndef ICON_H
#define ICON_H

#include "main.h"

enum ICON_TYPE {
	ICON_SEED = 0,
	ICON_WEAPON = 1,
	ICON_OBJECT = 2
};

class Icon : public qSprite {
	public:
		// Construct & Destruct
		Icon(int i, u8* gfx);
		~Icon();
		
	private:
		char* s_name; // Icon name
		ICON_TYPE s_type; // Icon type
};

#endif // ICON_H
