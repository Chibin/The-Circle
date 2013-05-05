#ifndef OPENINGSCENE_H_
#define OPENINGSCENE_H_
#include "Scene.h"
class OpeningScene: public Scene{
	private:
		SDL_Surface *newGame[2], *quit[2], *bg, *load[2];
		SDL_Rect newGameRect, startRect, quitRect, bgRectSrc, bgRectDest, loadRect;
		//int quitValue, newValue, loadValue;
	public:
		int count, maxButton;
		OpeningScene(SDL_Surface* screen);
		void eventHandler(SDL_Event& event);
		void display(SDL_Surface* screen);
		void disposeResources();
};
#endif
