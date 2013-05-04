#include "Tiles.h"

Tiles::Tiles(int x, int y, int tileType){
	box.x = x;
	box.y = y;
	type = tileType;
}

// TODO: add show code to tiles
void Tiles::show(){

}

int Tiles::get_type(){
	return type;
}

SDL_Rect Tiles::get_box(){
	return box;
}