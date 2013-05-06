#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Player.h"
#include "Tiles.h"

class Player: public Entity{

public:
	enum PlayerType
	{
		LLYOD, NATILIA
	};
	//intialized the character
	static Player& getInstance();

	//takes key presses and adjust player velocity
	void move(Tiles *tiles[] );
	//show the player on screen
	void show();
	//set the camera on the player
	void setCamera();
	void touchObject();
	void setType(PlayerType);
	PlayerType getType();
	SDL_Surface** getPlayerText();
	
private:
	PlayerType type;
	//Collision Box
	SDL_Rect box;
	//the x and y offeset of the character
	int x , y;
	//The velocity of the character
	int xVel, yVel;
	Player();
	SDL_Surface* playerText[2];
	//disable copy constructors
	Player(Player const& copy);
	Player& operator = (Player const& copy);

};
#endif