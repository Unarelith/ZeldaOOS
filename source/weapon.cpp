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
#include "main.h"

Weapon::Weapon(Sprite* icon, Sprite* animation) {
	s_icon = icon;
	s_animation = animation;
}

Weapon::~Weapon() {
	delete s_icon;
	delete s_animation;
}

void Weapon::drawIcon() {
	s_icon->draw(s_key, 176);
}

void Weapon::playAnimation() {
	//s_animation->playAnimation();
}
