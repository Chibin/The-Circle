
#ifndef NEWCHARSCREEN_H_
#define NEWCHARSCREEN_H_
#include <SDL_TTF.h>
#include "Scene.h"
class NewCharScreen: public Scene{
	private:
		SDL_Surface *maleChar[3], *femaleChar, *bg, *malebg;
		SDL_Rect makeCharRect, femaleCharRect, bgRect;
		int maleFrame, femaleFrame;
	public:
		
		NewCharScreen(SDL_Surface* screen);
		void eventHandler(SDL_Event& event);
		void display(SDL_Surface* screen);
};
#endif
