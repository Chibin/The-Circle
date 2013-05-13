#ifndef CHARINFOSCENE_H_
#define CHARINFISCENE_H_
#include "Scene.h"

class CharInfoScene : public Scene{
		enum Choice
	{
		MAIN, ITEMS, SKILLS, OPTIONS
	};
	SDL_Surface *bg, *portrait, *menuTop, *menuTop1, *menuTop2, *menuTop3;
	SDL_Rect bgRect, menuTopRect;
	Choice currentChoice;
	int mainMenuChoice;
public:
	CharInfoScene();
	void eventHandler(SDL_Event& event);
	void display();
	void disposeResources();
};


#endif

