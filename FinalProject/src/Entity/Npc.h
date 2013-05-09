#ifndef NPC_H
#define NPC_H
#include "Entity.h" // for Entity
#include "../Scene/Scene.h" // for Animation
#include "SDL_image.h"
#include <string> // for name

class NPC : public Entity
{
protected:
	std::string npcName;
	SDL_Surface* npcImage;
	SDL_Rect npcRect;
	Animation *npcUp, *npcDown, *npcLeft, *npcRight, *currentAnimation;
public:
	NPC();
	virtual SDL_Rect* getRect();
	virtual SDL_Surface* getSurface();
	virtual Animation* getAnimation();
	virtual void setFrames();
	~NPC(){}
};

class NPC_girl1 : public NPC
{
public:
	NPC_girl1();
	~NPC_girl1(){}
};

class NPC_guy1 : public NPC
{
public:
	NPC_guy1();
	~NPC_guy1(){}
};

#endif