#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player: public Entity{
	private:
		//Collision Box
		SDL_Rect box;
		//The velocity of the character
		int xVel, yVel;

		SDL_Surface* playerText[2];
	public:
		Player();
		SDL_Surface** getPlayerText();

#endif