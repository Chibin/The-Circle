#ifndef CHARINFOSCENE_H_
#define CHARINFISCENE_H_
#include "Scene.h"

class CharInfoScene : public Scene{
		enum Choice
	{
		MAIN, STATUS, SKILLS, EQUIPS, OPTIONS
	};
	//top menu 
	SDL_Surface *bg, *menuTop, *menuTop1, *menuTop2, *menuTop3, *hand;
	SDL_Rect bgRect, menuTopRect, handRect;
	//status
	SDL_Surface *status1, *statusTitle, *bgChar, *portrait;
	/*text*/  SDL_Surface *currXpTxt, *nextXPTxt, *hpTxt, *mpTxt, *nameTxt; SDL_Rect currXpTxtRect, nextXPTxtRect, hpTxtRect, mpTxtRect, nameTxtRect;
	/*Stats*/ SDL_Surface *currXp, *nextXP, *hp, *mp; SDL_Rect currXpRect, nextXpRect, hpRect, mpRect;
	SDL_Rect status1Rect, statusTitleRect, bgCharRect, portraitSrcRect, portraitDestRect;

	//text


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

