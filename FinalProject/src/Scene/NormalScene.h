#ifndef NORMALSCENE_H_
#define NORMALSCENE_H_
#include "Scene.h"
#include <vector> // for npc
#include "../src/Entity/NPC.h"// npc

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
		//For NPC chat box
		SDL_Surface *textBox;
		SDL_Rect textBoxRect;

	public:
		NormalScene();
		//void eventHandler(SDL_Event& event, int& gameState);
		void eventHandler(SDL_Event& event);
		void display();
		void disposeResources();
		string npcText;
};
#endif
