#ifndef NPC_H
#define NPC_H
#include "Entity.h"
class NPC : public Entity
{
protected:
	SDL_Surface* npcImage;
	SDL_Rect npcRect;
public:
	NPC();
	~NPC();
};

class NPC_girl1 : public NPC
{
	NPC_girl1();
	~NPC_girl1();
};

class NPC_guy1 : public NPC
{
	NPC_guy1();
	~NPC_guy1();
};

#endif