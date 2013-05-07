#ifndef NORMALSCENE_H_
#define NORMALSCENE_H_
#include "Scene.h"
class NormalScene : public Scene{
	private:
		enum PLayerState
		{
			DIALOGUE, ROAM, MERCHANT 
		};
		SDL_Surface *playerModel, *tempMap;
		SDL_Rect mapRect, *tempAnim;
		Animation *playerAnimUp, *playerAnimDown, *playerAnimLeft, *playerAnimRight, *currentAnim;
		PLayerState currentState;
		int velocity,currentTick, lastTick;
	public:
		NormalScene();
		//void eventHandler(SDL_Event& event, int& gameState);
		void eventHandler(SDL_Event& event);
		void display();
		void disposeResources();
};
#endif
