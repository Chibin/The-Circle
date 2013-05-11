#ifndef NORMALSCENE_H_
#define NORMALSCENE_H_
#include "Scene.h"
class NormalScene : public Scene{
	private:
		enum PLayerState
		{
			DIALOGUE, ROAM, EVENT 
		};
		SDL_Surface *playerModel, *tempMap;
		SDL_Rect mapRect;
		PLayerState currentState;
		int currentTick, lastTick;
	public:
		NormalScene();
		//void eventHandler(SDL_Event& event, int& gameState);
		void eventHandler(SDL_Event& event);
		void display();
		void disposeResources();
};
#endif
