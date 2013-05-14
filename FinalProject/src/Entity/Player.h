#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "../Scene/Scene.h"
class Animation;
class Player: public Entity{

public:
	enum PlayerType
	{
		LLYOD, NATILIA
	};
	enum MoveState{
		UP,DOWN,LEFT,RIGHT
	};
	//intialized the character
	//getter
	static Player& getInstance();
	int getPositionX();
	int getPositionY();
	PlayerType getType();
	SDL_Surface** getPlayerText();
	SDL_Rect* getPlayerPosition();
	Animation* getAnimRight();
	Animation* getAnimLeft();
	Animation* getAnimUp();
	Animation* getAnimDown();
	int getMapOffsetX();
	int getMapOffsetY();
	int getVelocity();
	int getXP();
	int getMaxXp();
	//setter
	void setType(PlayerType);
	void move(int x, int y);
	void setCamera();
	void setPosition(int,int);
	void setPlayer(bool);
	void setAnimState(MoveState);
	//misc
	void show();
	void renderPlayer();
	void renderLastPlayerFrame();
private:
	SDL_Surface* model;
	PlayerType type;
	Animation *current,*playerAnimUp, *playerAnimDown, *playerAnimLeft, *playerAnimRight;
	//Collision Box
	SDL_Rect rect, *tempAnim;;
	//experience points
	int currentXP, maxXP;
	//The velocity of the character
	int xVel, yVel;
	int mapOffsetX, mapOffsetY;
	Player();
	SDL_Surface* playerText[2];
	//disable copy constructors
	Player(Player const& copy);
	Player& operator = (Player const& copy);
	int velocity,currentTick, lastTick;
};
#endif
