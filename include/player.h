#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"
#include "sprite3D.h"

#include "link_png.h"

class Player : public Sprite3D {
	public:
		// Construct & Destruct
		Player();
		~Player();
	
	private:
		int lifes;
};

#endif // PLAYER_H
