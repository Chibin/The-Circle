#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "Scene.h"
#include "../Battle/BattleHandler.h"
#include "../Entity/Entity.h"
#include <vector>
class BattleScene : public Scene{
	private:
		TTF_Font* font;
		SDL_Surface* textFight[2],* textRun[2],* textItem[2],* textDefend[2],* textMagic[2],* screen;
		SDL_Surface* bgBattleMenu;
		SDL_Rect fightLoc, runLoc, itemLoc, magicLoc, bgBattleMenuLoc;
		int fightVal, runVal,itemVal,magicVal;
		enum battleSelect{FIGHT,ITEM,RUN,MAGIC, isFight,isItem,isRun, battleEnd,battlePhase,endPhase};
		BattleHandler* bManager;
		Player* player;
		int battleMenu;
	public:
		BattleScene(SDL_Surface* screen);
		void eventHandler(SDL_Event& event);
		void display(SDL_Surface* screen);
		~BattleScene();
		void loadMobs();
};
#endif
