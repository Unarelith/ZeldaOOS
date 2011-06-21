#include "map.h"

Map::Map(UL_IMAGE* image, char* filename, u16 width, u16 height, u16 tileWidth, u16 tileHeight) {
	s_image = image;
	s_filename = filename;
	s_width = width;
	s_height = height;
	s_tileWidth = tileWidth;
	s_tileHeight = tileHeight;
	
	
    u16* table;
    table = (u16*)malloc(s_width * s_height * sizeof(u16));
    // Load map from file
    int filesize;
    struct stat file_status;
    if(stat(filename, &file_status) != 0){
        ulDebug("Unable to load %s", s_filename);
    }
    filesize = file_status.st_size;
    FILE* f = fopen(filename, "r");
    char* buffer = (char*)malloc(sizeof(char) * filesize);
    fread(buffer, 1, filesize, f);
    fclose(f);
    // (Now buffer contains the map file)
    int counter = 0;
    char* token;
    u16 tile;
    const char delimiters[] = "|";
    token = strtok(buffer, delimiters);
    tile = (u16)atof(token);
    table[counter] = tile;
    counter++;
    while(token != NULL){
        token = strtok(NULL, delimiters);
        if(token != NULL){
            tile = (u16)atof(token);
            table[counter] = tile;
        }
        counter++;
    }
    free(buffer);
	
    s_map = ulCreateMap(s_image, (void*)table, s_tileWidth, s_tileHeight, s_width, s_height, UL_MF_U16);
}

Map::~Map() {
	ulDeleteMap(s_map);
}

void Map::draw() {
	ulDrawMap(s_map);
}

void Map::scroll(s16 x, s16 y) {
	s_map->scrollX = x;
	s_map->scrollY = y;
}

void Map::setTile(s16 x, s16 y, u16 tile) {
	u16* t = (u16*)s_map->map;
	t[x + y * s_map->mapSizeX] = tile;
}

u16 Map::getTile(s16 x, s16 y) {
	u16* t = (u16*)s_map->map;
	return t[x + y * s_map->mapSizeX];
}
