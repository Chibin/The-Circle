
#ifndef NEWCHARSCREEN_H_
#define NEWCHARSCREEN_H_
#include <SDL_TTF.h>
#include "Scene.h"
class NewCharScreen: public Scene{
	private:
		SDL_Surface *maleChar, *femaleChar, *bg, *malebg;
		SDL_Rect makeCharRect[2], femaleCharRect[2], bgRect, maleBgRect;
		int maleFrame, femaleFrame;
	public:
		void disposeResources();
		NewCharScreen(SDL_Surface* screen);
		void eventHandler(SDL_Event& event);
		void display(SDL_Surface* screen);
};
#endif
