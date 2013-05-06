#ifndef NORMALSCENE_H_
#define NORMALSCENE_H_
#include "Scene.h"
class NormalScene : public Scene{
	private:
		SDL_Surface *playerModel;
	public:
		NormalScene();
		//void eventHandler(SDL_Event& event, int& gameState);
		void eventHandler(SDL_Event& event);
		void display();
		void disposeResources();
};
#endif
