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

#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#define TILESETS 1
#define MAPS 2

Tileset* initTilesets();
Map** initMaps(u8 mapBg);

#endif // MAPMANAGER_H
