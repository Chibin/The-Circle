
#ifndef NEWCHARSCREEN_H_
#define NEWCHARSCREEN_H_
#include <SDL_TTF.h>
#include "Scene.h"
class NewCharScreen: public Scene{
	private:
		SDL_Surface *maleChar, *femaleChar, *bg, *malebg;
		SDL_Rect maleCharRect[3], char1, femaleCharRect[2], bgRect, maleBgRect;
		Uint32 maleFrame, femaleFrame, currentTick, lastTick, char1Tick;
		bool back;
	public:
		void disposeResources();
		NewCharScreen(SDL_Surface* screen);
		void eventHandler(SDL_Event& event);
		void display(SDL_Surface* screen);
};
#endif
