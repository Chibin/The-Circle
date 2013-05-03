#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "Scene.h"
#include "BattleManager.h"
#include "Entity.h"
#include <vector>
class BattleScene : public Scene{
	private:
		TTF_Font* font;
		SDL_Surface* textFight[2],* textRun[2],* textItem[2],* textDefend[2],* textMagic[2],* screen;
		SDL_Surface* bgBattleMenu;
		SDL_Rect fightLoc, runLoc, itemLoc, magicLoc, bgBattleMenuLoc;
		int fightVal, runVal,itemVal,magicVal;
		enum battleSelect{FIGHT,ITEM,RUN,MAGIC, isFight,isItem,isRun, battleEnd,battlePhase,endPhase};
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
