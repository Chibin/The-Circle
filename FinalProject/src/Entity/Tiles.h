#ifndef TILES_H
#define TILES_
#include <SDL.h>

class Tiles{
private:
	//Attributes of tile
	SDL_Rect box;
	//Tile type
	int type;
public:
	//imtialize the object
	Tiles(int x, int y, int tileType);
	//show the tiles
	void show();
	//get tile type
	int get_type();
	//get collision box
	SDL_Rect get_box();
};

#endif