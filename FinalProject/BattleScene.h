#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "Scene.h"
#include "BattleManager.h"
#include "Entity.h"
#include <vector>
class BattleScene : public Scene{
	private:
		TTF_Font* font;
		SDL_Surface* textFight[2],* textRun[2],* screen;
		SDL_Rect fightLoc, runLoc;
		int fightVal, runVal;
		enum battleSelect{FIGHT,ITEM,RUN, isFight,isItem,isRun, battleEnd};
		BattleManager* bManager;
		Player* player;
		int battleMenu;
	public:
		BattleScene(int* gameOver, SDL_Surface* screen);
		void eventHandler(SDL_Event& event, int& gameState);
		void display(SDL_Surface* screen);
		~BattleScene();
		void loadMobs();
};
#endif
