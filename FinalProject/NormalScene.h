#ifndef NORMALSCENE_H_
#define NORMALSCENE_H_
#include "Scene.h"
class NormalScene : public Scene{
	private:
	public:
		NormalScene(SDL_Surface* _screen);
		void eventHandler(SDL_Event& event, int& gameState);
		void display(SDL_Surface* screen);
};
#endif
