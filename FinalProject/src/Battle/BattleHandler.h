#ifndef BATTLEHANDLER_H_
#define BATTLEHANDLER_H_
#include "../Entity/Entity.h"
#include <algorithm>
#include <vector>
#include <SDL_ttf.h>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include "../Entity/Mob.h"
#include "../Entity/Player.h"
#include "../Manager/SceneManager.h"

static bool compare_SPD(Mob* first, Mob* second){
	return (first->getSPD() > second->getSPD());
}
static bool compareEntity_SPD(Entity* first, Entity* second){
	return (first->getSPD() > second->getSPD());
}
class BattleHandler{
	private:
		enum battleSelect{FIGHT,ITEM,RUN,MAGIC, isFight,isItem,isRun, battleEnd,battlePhase,endPhase};
		enum battleCondition{MUTAL,PREEMPTIVE,FLANKED};
		int mobSelected, bpLoopCheck;
		Player* player;
		SceneManager* scene;
		bool playerDead;
		TTF_Font* font;
		std::vector<SDL_Surface*> battleText,endBattleText;
		std::vector<Mob*>* mobs;
	public:
		BattleHandler();
		void loadMobs(std::vector<Mob*>* _mobs);
		//Selected Actions
		void displayItems();
		bool startFight(int& battleMenu,enum battleCondition condition);
		void run(int& battleMenu);
		//BattleCalculations
		void battleLog(std::vector<Entity*>* inOrder, string mobAttacked, enum battleCondition condition);
		//Modifier for the battle display via incrementing a counter
		void battlePhaseUpdate(int& battleMenu);
		//Battle Displays
		void battleDisplayUpdate(int& battleMenu);
		void monsterSelectDisplay(int& battleMenu);
		void battlePhaseDisplay(int& battleMenu);	
		void endPhaseDisplay(int& battleMenu);
		//Sets players and monsters in turn order for battle phase
		void turnOrder(std::vector<Entity*>* inOrder);
		//Monster selection
		void moveLeft();
		void moveRight();
		//Flow state of battle
		void battleHandler(int& battleMenu);
};
#endif