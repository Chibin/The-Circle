#ifndef OPENINGSCENE_H_
#define OPENINGSCENE_H_
#include "Scene.h"
class OpeningScene: public Scene{
	private:
		SDL_Surface *start[2], *quit[2];
		SDL_Rect startRect, quitRect;
		int startValue, quitValue;
	public:
		OpeningScene(int* _gameOver,SDL_Surface* screen);
		void eventHandler(SDL_Event& event, int& gameState);
		void display(SDL_Surface* screen);
};
#endif
