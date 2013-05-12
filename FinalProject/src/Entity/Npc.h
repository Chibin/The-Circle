#ifndef NPC_H
#define NPC_H
#include "Entity.h" // for Entity
#include "../Scene/Scene.h" // for Animation
#include "SDL_image.h"
#include <string> // for name

class Animation;

class NPC : public Entity
{
protected:
	std::string npcName;
	SDL_Surface* npcImage;
	SDL_Rect npcRect;
	Animation *npcUp, *npcDown, *npcLeft, *npcRight, *currentAnimation;
public:
	NPC();
	virtual SDL_Rect* getRect(void);
	virtual SDL_Surface* getSurface(void);
	virtual Animation* getAnimation(void);
	virtual void setFrames(void);
	SDL_Surface* load_imageBlue(std::string file); // function to load images with blue/transparent background
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