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
#include "../Entity/Entity.h"
#include "../Entity/Magic.h"

static bool compare_SPD(Mob* first, Mob* second){
	return (first->getSPD() > second->getSPD());
}
static bool compareEntity_SPD(Entity* first, Entity* second){
	return (first->getSPD() > second->getSPD());
}
class BattleHandler{
	private:
		enum battleSelect{FIGHT,ITEM,RUN,MAGIC, isFight,isMagic,isItem,isRun,magicTargetSelect, battlePhase,magicBattlePhase,endPhase,battleEnd};
		enum battleCondition{MUTAL,PREEMPTIVE,FLANKED};
		int mobSelected, bpLoopCheck,magicSelected;
		Player* player;
		SceneManager* scene;
		bool playerDead;
		TTF_Font* font;
		std::vector<SDL_Surface*> battleText,endBattleText;
		std::vector<Mob*>* mobs;
		int prevPhase, prevmagicSelected;
		bool magicMenuTrigger;
		bool drawingText;
		bool drawingComplete;
		SDL_Rect textScroller;
	public:
		BattleHandler();
		void resetDrawingTextBool();
		void loadMobs(std::vector<Mob*>* _mobs);
		//Selected Actions
		void displayItems();
		void MagicMenu();
		bool startFight(int& battleMenu,enum battleCondition condition);
		void run(int& battleMenu);
		//BattleCalculations
		void battleLog(std::vector<Entity*>* inOrder, string mobAttacked, enum battleCondition condition,int battleMenu);
		void MagicBattlePhase(Magic selectedMagic,std::vector<Entity*>* inOrder);
		void magicDamage(Magic selectedMagic,std::vector<Entity*>* inOrder);
		void magicHeal(Magic selectedMagic,std::vector<Entity*>* inOrder);
		void magicDebuff(Magic selectedMagic,std::vector<Entity*>* inOrder);
		void magicBuff(Magic selectedMagic,std::vector<Entity*>* inOrder);
		//Updates the text to the next text
		void textUpdate(int& battleMenu);
		void textScrollDisplay(std::vector<SDL_Surface*>& textVector,int index,bool& drawingText,bool& drawingComplete,SDL_Rect startPos);
		//Determines the start index for magic and item menu to be drawn
		int indexScrollDeteminer(int& startingIndex, int currentIndex, int scrollLimit);
		//Battle Displays
		void battleDisplayUpdate(int& battleMenu);
		void monsterSelectDisplay(int& battleMenu);
		void magicSelectDisplay();
		void magicMenuDisplay();
		void battlePhaseDisplay(int& battleMenu);	
		void endPhaseDisplay(int& battleMenu);
		//Sets players and monsters in turn order for battle phase
		void turnOrder(std::vector<Entity*>* inOrder);
		//Input Handler
		void inputHandler();
		//Monster selection
		void moveLeft();
		void moveRight();
		//Magic Selection
		void magicUp();
		void magicDown();
		//Flow state of battle
		void battleHandler(int& battleMenu);
};
#endif
