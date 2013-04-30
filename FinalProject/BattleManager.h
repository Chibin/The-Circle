#ifndef BATTLEMANAGER_H_
#define BATTLEMANAGER_H_
#include "Entity.h"
#include <algorithm>
#include <vector>

static bool compare_SPD(Mob* first, Mob* second){
		return (first->getSPD() > second->getSPD());
}
static bool compareEntity_SPD(Entity* first, Entity* second){
		return (first->getSPD() > second->getSPD());
}

class BattleManager{
	private:
		enum battleSelect{FIGHT,ITEM,RUN, isFight,isItem,isRun};
		int mobSelected;
		Player* player;
		std::vector<Mob*>* mobs;
	public:
	BattleManager(Player* _player){
		player = _player;
		mobSelected = 0;
	}
	void loadMobs(std::vector<Mob*>* _mobs){
		mobs = _mobs;
	}
	void monsterSelect(SDL_Surface* screen,int& battleMenu){
		//cout << "Fighting ";
		int x = 0, y = 0;
		int size = 1;
		size = mobs->size();
		SDL_Rect* mobRect = new SDL_Rect[size];
		for(int i = 0; i < mobs->size(); i++){
			mobRect[i].x = i*150; mobRect[i].y = 0;
			//cout << (*mobs)[i]->getName() << " ";
			if(mobSelected == i)
				SDL_BlitSurface((*mobs)[i]->getEnemyText()[0],NULL,screen,&mobRect[i]);
			else
				SDL_BlitSurface((*mobs)[i]->getEnemyText()[1],NULL,screen,&mobRect[i]);
		}
	//	SDL_Flip(screen);
		//cout << endl;
	}
	void items(){}
	void run(){
		cout << "RAN AWAY" << endl;
	}
	void battleUpdate(int& battleMenu, SDL_Surface* screen){
		monsterSelect(screen,battleMenu);
	}
	void battleHandler(int& battleMenu,SDL_Surface* screen){
		switch(battleMenu){
			case FIGHT:
				cout << "I WANT TO FIGHT" << endl;
				battleMenu = isFight;
				monsterSelect(screen, battleMenu);
				break;
			case ITEM:
				break;
			case RUN:
				cout << "I WANT TO RUN" << endl;
				break;
			case isFight:
				startFight();
				break;
			default:
				cout << "STOP PRESSING ENTER" << endl;
				break;
		}
	}
	void startFight(){
		cout << "Calculate damage here " << endl;
		cout << "Attacking mob Number " << mobSelected+1 << endl;
		std::vector<Entity*>* inOrder = new std::vector<Entity*>();
		turnOrder(inOrder);
		cout << "IN ORDER " << inOrder->size() << endl;
	}

	void turnOrder(std::vector<Entity*>* inOrder){
		inOrder->push_back((Entity*)player);
		for(int i = 0; i < mobs->size(); i++)
			inOrder->push_back((Entity*)(*mobs)[i]);
		std::sort(inOrder->begin(),inOrder->end(),compareEntity_SPD);
		for(int i = 0; i < inOrder->size(); i++)
			cout << (*inOrder)[i]->getName() << " " << (*inOrder)[i]->getSPD() << endl;
	}

	void moveLeft(){
		if(mobSelected > 0)
			mobSelected--;	 
		cout <<"MOVING LEFT" << mobSelected << endl;
	}

	void moveRight(){
		if(mobSelected < mobs->size()-1)
			mobSelected++;
		cout << "MOVING RIGHT" << mobSelected << endl;
	}
};

#endif
