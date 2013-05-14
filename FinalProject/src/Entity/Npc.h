#ifndef NPC_H
#define NPC_H
#include "Entity.h" // for Entity
#include "../Scene/Scene.h" // for Animation
#include "SDL_image.h"
#include <string> // for name
#include <vector>
#include <SDL_ttf.h>

class Animation;

class NPC : public Entity
{
protected:
	std::string npcName;
	vector<std::string> speach;
	SDL_Surface* npcImage;
	SDL_Rect npcRect;
	Animation *npcUp, *npcDown, *npcLeft, *npcRight, *currentAnimation;
	vector<SDL_Surface*> surfaceText;
	//vector<SDL_Rect> surfaceTextRect;
	SDL_Rect surfaceTextRect;
	TTF_Font* font;
	SDL_Color fgColor;
public:
	NPC();
	string getName(void);
	string speak(void);
	int sentence;
	virtual SDL_Rect* getRect(void);
	virtual SDL_Surface* getSurface(void);
	virtual Animation* getAnimation(void);
	virtual void setFrames(void);
	SDL_Surface* load_imageBlue(std::string file); // function to load images with blue/transparent background
	void displayText(SDL_Surface*);
	~NPC();
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

class NPC_guyRed : public NPC
{
public:
	NPC_guyRed();
	~NPC_guyRed(){}
};

#endif