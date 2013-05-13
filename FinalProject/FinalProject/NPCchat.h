#ifndef	NPCCHAT_H
#define NPCCHAT_H
#include "../src/Scene/Scene.h"

class NPCchat : public Scene
{
public:
	SDL_Surface *textBox;
	SDL_Rect textBoxRect;
	TTF_Font *textBoxFont;
	
};

#endif