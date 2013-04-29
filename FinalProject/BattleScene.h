#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "Scene.h"
class BattleScene : public Scene{
	private:
		TTF_Font* font;
		SDL_Surface* textFight[2],* textRun[2];
		SDL_Rect fightLoc, runLoc;
		int fightVal, runVal;
	public:
		BattleScene(int* gameOver);
		void eventHandler(SDL_Event& event, int& gameState);
		void display(SDL_Surface* screen);
		~BattleScene();
};
#endif



