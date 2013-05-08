#ifndef BATTLESCENE_H_
#define BATTLESCENE_H_
#include "Scene.h"
#include "../Battle/BattleHandler.h"
#include "../Entity/Entity.h"
#include <vector>
class BattleScene : public Scene{
	private:
		TTF_Font* font;
		SDL_Surface* textFight[2],* textRun[2],* textItem[2],* textDefend[2],* textMagic[2];
		SDL_Surface* bgBattleMenu;
		SDL_Rect fightLoc, runLoc, itemLoc, magicLoc, bgBattleMenuLoc;
		int fightVal, runVal,itemVal,magicVal;
		enum battleSelect{FIGHT,ITEM,RUN,MAGIC, isFight,isMagic,isItem,isRun,magicTargetSelect, battlePhase,magicBattlePhase,endPhase,battleEnd};
		BattleHandler* bManager;
		int battleMenu;
	public:
		BattleScene();
		void eventHandler(SDL_Event& event);
		void display();
		void disposeResources();
		~BattleScene();
		void loadMobs();
};
#endif
