#ifndef CHARINFOSCENE_H_
#define CHARINFISCENE_H_
#include "Scene.h"

class CharInfoScene : public Scene{
		enum Choice
	{
		MAIN, STATUS, SKILLS, EQUIPS, OPTIONS
	};
	//top menu 
	SDL_Surface *bg, *portrait, *menuTop, *menuTop1, *menuTop2, *menuTop3;
	SDL_Rect bgRect, menuTopRect;
	//status
	SDL_Surface *status1, *statusTitle, *bgChar;
	SDL_Rect status1Rect, statusTitleRect, bgCharRect;


	Choice currentChoice;
	int mainMenuChoice;
	TTF_Font *font;
public:
	CharInfoScene();
	void eventHandler(SDL_Event& event);
	void display();
	void disposeResources();
};


#endif

