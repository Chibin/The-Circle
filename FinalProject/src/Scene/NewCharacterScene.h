
#ifndef NEWCHARSCREEN_H_
#define NEWCHARSCREEN_H_
#include <SDL_TTF.h>
#include "Scene.h"
class NewCharScreen: public Scene{
	private:
		enum Stage
		{
			PICK, STATS, FINISHED, GOBACK
		};
		//global resources
		SDL_Surface *backScreen, *backScreen1;
		SDL_Rect backScreenRect;
		bool goBack;

		//stage 1 Resources
		SDL_Surface *maleChar, *maleChar1, *femaleChar, *femaleChar1, *bg, *bg1, *malebg, *femalebg;
		SDL_Rect maleCharRect[3], char1, femaleCharRect[3], char2, bgRect, bgRect1, maleBgRect, femaleBgRect;
		Uint32 maleFrame, femaleFrame, currentTick, lastTick, char1Tick, char2Tick;
		
		//stage 2 Resources
		SDL_Surface *malebgp2, *femalebgp2;
		SDL_Rect malebgp2Rect, femalebgp2Rect;

		Stage currentStage;
		bool back, selected;
		void loadStage2();
	public:
		void disposeResources();
		NewCharScreen(SDL_Surface* screen);
		void eventHandler(SDL_Event& event);
		void display(SDL_Surface* screen);
};
#endif
