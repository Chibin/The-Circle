#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Player: public Entity{
	private:
		//Collision Box
		SDL_Rect box;
		//the x and y offeset of the character
		int x , y;
		//The velocity of the character
		int xVel, yVel;

		SDL_Surface* playerText[2];
	public:
		//intialized the character
		Player();
		//takes key presses and adjust player velocity
		void move();
		//show the player on screen
		void show();
		//set the camera on the player
		void setCamera();
		SDL_Surface** getPlayerText();
};
#endif