#ifndef CHARINFOSCENE_H_
#define CHARINFISCENE_H_
#include "Scene.h"

class CharInfoScene : public Scene{
		enum Choice
	{
		MAIN, STATUS, SKILLS, EQUIPS, OPTIONS
	};
	//top menu 
	SDL_Surface *bg, *menuTop, *menuTop1, *menuTop2, *menuTop3, *hand, *secondBG;
	SDL_Rect bgRect, menuTopRect, handRect, secondBGRect;
	//status
	SDL_Surface *status1, *statusTitle, *bgChar, *portrait;
	/*text*/  SDL_Surface *currXpTxt, *nextXPTxt, *hpTxt, *mpTxt, *nameTxt; SDL_Rect currXpTxtRect, nextXPTxtRect, hpTxtRect, mpTxtRect, nameTxtRect;
	/*Stats*/ SDL_Surface *currXp, *nextXP, *hp, *mp, *level; SDL_Rect currXpRect, nextXpRect, hpRect, mpRect, levelRect;
	SDL_Rect status1Rect, statusTitleRect, bgCharRect, portraitSrcRect, portraitDestRect;
	//skills
	SDL_Surface *status2;
	SDL_Rect status2Rect;
	//equips
	SDL_Surface *status3;
	SDL_Rect status3Rect;
	//option
	SDL_Surface *status4, *saveTxt, *loadTxt, *quitToMenu, *quitGame, *optionBg;
	SDL_Rect  saveTxtRect, loadTxtRect, quitToMenuRect, quitGameRect, optionBgRect;

	Choice currentChoice;
	int mainMenuChoice, optionChoice;
	TTF_Font *font;
public:
	CharInfoScene();
	void eventHandler(SDL_Event& event);
	void display();
	void disposeResources();
};


#endif

