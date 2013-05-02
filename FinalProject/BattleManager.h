#ifndef BATTLEMANAGER_H_
#define BATTLEMANAGER_H_
#include "Entity.h"
#include <algorithm>
#include <vector>
#include <SDL_ttf.h>
#include <sstream>
#include <stdlib.h>
#include <cmath>
static bool compare_SPD(Mob* first, Mob* second){
	return (first->getSPD() > second->getSPD());
}
static bool compareEntity_SPD(Entity* first, Entity* second){
	return (first->getSPD() > second->getSPD());
}

class BattleManager{
	private:
		enum battleSelect{FIGHT,ITEM,RUN,MAGIC, isFight,isItem,isRun, battleEnd,battlePhase,endPhase};
		int mobSelected;
		int bpLoopCheck;
		Player* player;
		bool playerDead;
		TTF_Font* font;
		std::vector<SDL_Surface*> battleText;
		std::vector<SDL_Surface*> endBattleText;
		std::vector<Mob*>* mobs;
	public:
		BattleManager(Player* _player){
			battleText.clear();
			player = _player;
			mobSelected = 0;
			playerDead = false;
		}
		void loadMobs(std::vector<Mob*>* _mobs){
			mobs = _mobs;
		}
		void monsterSelect(SDL_Surface* screen,int& battleMenu){
			//cout << "Fighting ";
			int x = 0, y = 0;
			SDL_Rect* mobRect = new SDL_Rect[mobs->size()];
			for(int i = 0; i < mobs->size(); i++){
				mobRect[i].x = i*150; mobRect[i].y = 0;
				//cout << (*mobs)[i]->getName() << " ";
				if(mobSelected == i)
					SDL_BlitSurface((*mobs)[i]->getEnemyText()[0],NULL,screen,&mobRect[i]);
				else
					SDL_BlitSurface((*mobs)[i]->getEnemyText()[1],NULL,screen,&mobRect[i]);
			}
		}
		//when item is selected
		void displayItems(){}

		void endPhaseLoop(int& battleMenu, SDL_Surface* screen){
			SDL_Rect bText;
			bText.x = 50;
			bText.y = 400;
			if(bpLoopCheck < endBattleText.size())
				SDL_BlitSurface(endBattleText[bpLoopCheck],NULL,screen,&bText);
			else{
				cout << "I GET HERE" << endl;
				for(int i = 0; i < endBattleText.size(); i++)
					SDL_FreeSurface(endBattleText[i]);
				battleMenu = battleEnd;
				endBattleText.clear();
			}
		}
		void run(int& battleMenu, SDL_Surface* screen){
			int fasterMonsters = 1;
			SDL_Surface* temp;
			SDL_Color fgColor = {255,255,255};
			font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
			for(int i = 0; i < mobs->size();i++){
				if(player->getSPD() < (*mobs)[i]->getSPD())
					fasterMonsters++;
			}
			if(fasterMonsters == 0){
				temp = TTF_RenderText_Blended(font,"Player got away!",fgColor);
				endBattleText.push_back(temp);
				battleMenu = endPhase;
			}
			else{
				double chanceToRun = (1.0/(double)fasterMonsters)*100;
				double runAway = rand()%100+1;
				if(runAway <= chanceToRun){
					temp = TTF_RenderText_Blended(font,"Player got away!",fgColor);
					endBattleText.push_back(temp);
					battleMenu = endPhase;
				}
				else{
					fgColor.g = 100; fgColor.b = 0;
					temp = TTF_RenderText_Blended(font,"Player is flanked!",fgColor);
					battleText.push_back(temp);
					battleMenu = battlePhase;
					//commence attack of mob here
				}
			}
			bpLoopCheck = -1;
		}
		//redraws during display()
		void battleUpdate(int& battleMenu, SDL_Surface* screen){
			monsterSelect(screen,battleMenu);
		}
		void battleHandler(int& battleMenu,SDL_Surface* screen){
			switch(battleMenu){
				case FIGHT:
					battleMenu = isFight;
					monsterSelect(screen, battleMenu);
					break;
				case MAGIC:
					cout << "NO ABILITIES LEARNED" << endl;
					break;
				case ITEM:
					cout << "ITEMS WHERE R U" << endl;
					break;
				case RUN:
						run(battleMenu,screen);
					break;
				case isFight:
					if(!startFight(battleMenu,screen)){
						//call EXP EVENT?
						battleMenu = battlePhase;
						cout << "BATTLE SHOULD END" << endl;
					}
					break;
				case battlePhase:
					battlePhaseLoop(battleMenu,screen);
					break;
				case endPhase:
					endPhaseLoop(battleMenu,screen);
					cout <<" END OF BATTLE" << endl;
					break;
				default:
					cout << "STOP PRESSING ENTER" << endl;
					break;
			}
		}
		void battleLog(std::vector<Entity*>* inOrder, string mobAttacked){
			SDL_Surface* temp;
			font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
			SDL_Color fgColor = {255,200,0};
			SDL_Color deadColor = {255,50,0};
			for(int i = 0; i < inOrder->size(); i++){
				std::ostringstream oss;
				if(player->getName() == (*inOrder)[i]->getName()){
					//Attacking selected mob
					//cout << "Before battle, HP of mob is: " << (*mobs)[mobSelected]->getHP() << endl;
					oss << player->getName() << " attacked " << mobAttacked << " for " << player->getATK() << " damage!";
					temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
					battleText.push_back(temp);
					(*mobs)[mobSelected]->setHP((*mobs)[mobSelected]->getHP()-player->getATK());
					//cout << "After battle, HP of mob is: " << (*mobs)[mobSelected]->getHP() << endl;
					if((*mobs)[mobSelected]->getHP() <= 0){
						std::ostringstream dead;
						dead << (*mobs)[mobSelected]->getName() << " has been slain.";
						temp = TTF_RenderText_Blended(font,dead.str().c_str(),deadColor);
						battleText.push_back(temp);
						//removes from the inOrder vector
						for(int i = 0; i < inOrder->size();i++)
							if((*mobs)[mobSelected] == (*inOrder)[i])
								inOrder->erase(inOrder->begin()+i);
						mobs->erase(mobs->begin()+mobSelected);
						//add to exp gained this fight
					}
				}
				else{
					//Mob attacks selected player
					//Make an AI, may be...?
					//cout << "Current HP of Player: " << player->getHP() << endl;
					oss << (*inOrder)[i]->getName() << " attacks Player with " << (*inOrder)[i]->getATK() << " damage!";
					temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
					battleText.push_back(temp);
					player->setHP(player->getHP()-(*inOrder)[i]->getATK());
					//cout << "After Battle HP: " << player->getHP() << endl;
					if(player->getHP() <= 0){
						std::ostringstream dead, gameover;
						dead << player->getName() << " has been slain.";
						temp = TTF_RenderText_Blended(font,dead.str().c_str(),deadColor);
						battleText.push_back(temp);
						gameover << "GAME OVER!!";
						temp = TTF_RenderText_Blended(font,gameover.str().c_str(),deadColor);
						battleText.push_back(temp);
						playerDead = true;
						//remove player: Implemented this way so
						//if there are more than 1 player, they can still fight
						for(int i = 0; i < inOrder->size();i++)
							if(player == (*inOrder)[i])
								inOrder->erase(inOrder->begin()+i);
						break;
						//battleLost 
						//teleport back to rest point, change Player Position.
					}
				}
			}
		}
		bool startFight(int& battleMenu, SDL_Surface* screen){
			if(mobs->size()  == 0)
				return false;
			if(mobSelected > mobs->size()-1)
				mobSelected = mobs->size()-1;
			string mobAttacked = (*mobs)[mobSelected]->getName();
			std::vector<Entity*>* inOrder = new std::vector<Entity*>();
			turnOrder(inOrder);
			battleLog(inOrder,mobAttacked);
			bpLoopCheck = 0;
			battleMenu = battlePhase;
			bpLoopCheck = -1;
			return true;
		}
		void battlePhaseUpdate(int& battleMenu, SDL_Surface* screen){
			bpLoopCheck++;
		}
		void battlePhaseLoop(int& battleMenu, SDL_Surface* screen){
			SDL_Rect bText;
			bText.x = 50;
			bText.y = 400;
			if(bpLoopCheck < battleText.size())
				SDL_BlitSurface(battleText[bpLoopCheck],NULL,screen,&bText);
			else{
				for(int i = 0; i < battleText.size(); i++)
					SDL_FreeSurface(battleText[i]);
				battleMenu = FIGHT;
				if(playerDead){
					battleMenu = battleEnd;
					cout << "Revived with 10 HP" << endl;
					player->setHP(10);
					playerDead = false;
					battleMenu = endPhase;
				}
				bpLoopCheck = 0;
				battleText.clear();
			}
		}
		void turnOrder(std::vector<Entity*>* inOrder){
			inOrder->push_back((Entity*)player);
			for(int i = 0; i < mobs->size(); i++)
				inOrder->push_back((Entity*)(*mobs)[i]);
			std::sort(inOrder->begin(),inOrder->end(),compareEntity_SPD);
		}

		void moveLeft(){
			if(mobSelected > 0)
				mobSelected--;	 
		}

		void moveRight(){
			if(mobSelected < mobs->size()-1)
				mobSelected++;
		}
};

#endif
