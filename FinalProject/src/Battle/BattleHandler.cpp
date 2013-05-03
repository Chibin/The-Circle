#include "../Scene/BattleScene.h" //no idea why it breaks without this
#include "BattleHandler.h"
BattleHandler::BattleHandler(Player* _player){
	battleText.clear();
	player = _player;
	mobSelected = 0;
	playerDead = false;
}
void BattleHandler::loadMobs(std::vector<Mob*>* _mobs){
	mobs = _mobs;
}

//Selected Actions
void BattleHandler::displayItems(){
}
bool BattleHandler::startFight(int& battleMenu, SDL_Surface* screen,enum battleCondition condition){
	if(mobs->size()  == 0)
		return false;
	if(mobSelected > (int)mobs->size()-1)
		mobSelected = mobs->size()-1;
	string mobAttacked = (*mobs)[mobSelected]->getName();
	std::vector<Entity*>* inOrder = new std::vector<Entity*>();
	turnOrder(inOrder);
	battleLog(inOrder,mobAttacked,condition);
	if(mobs->size() == 0)
		battleMenu = endPhase;
	else
		battleMenu = battlePhase;
	bpLoopCheck = -1;
	return true;
}
void BattleHandler::run(int& battleMenu, SDL_Surface* screen){
	int fasterMonsters = 1;
	SDL_Surface* temp;
	SDL_Color fgColor = {255,255,255};
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
	for(int i = 0; i < (int)mobs->size();i++){
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
			startFight(battleMenu,screen,FLANKED);

		}
	}
	bpLoopCheck = -1;
}
//BattleCalculations
void BattleHandler::battleLog(std::vector<Entity*>* inOrder, string mobAttacked, enum battleCondition condition){
	SDL_Surface* temp;
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
	SDL_Color fgColor = {255,200,0};
	SDL_Color deadColor = {255,50,0};
	for(int i = 0; i < (int)inOrder->size(); i++){
		std::ostringstream oss;
		if(player->getName() == (*inOrder)[i]->getName()){
			if(condition != FLANKED){
				//Attacking selected mob
				oss << player->getName() << " attacked " << mobAttacked << " for " << player->getATK() << " damage!";
				temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
				battleText.push_back(temp);
				(*mobs)[mobSelected]->setHP((*mobs)[mobSelected]->getHP()-player->getATK());
				if((*mobs)[mobSelected]->getHP() <= 0){
					std::ostringstream dead;
					dead << (*mobs)[mobSelected]->getName() << " has been slain.";
					temp = TTF_RenderText_Blended(font,dead.str().c_str(),deadColor);
					battleText.push_back(temp);
					for(int i = 0; i < (int)inOrder->size();i++)
						if((*mobs)[mobSelected] == (*inOrder)[i])
							inOrder->erase(inOrder->begin()+i);
					mobs->erase(mobs->begin()+mobSelected);
					//add to exp gained this fight
				}
			}
		}
		else{
			//Mob attacks selected player
			//Make an AI, may be...?
			//checks if player has a free attack
			if(condition != PREEMPTIVE){
				oss << (*inOrder)[i]->getName() << " attacks Player with " << (*inOrder)[i]->getATK() << " damage!";
				temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
				battleText.push_back(temp);
				player->setHP(player->getHP()-(*inOrder)[i]->getATK());
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
					for(int i = 0; i < (int)inOrder->size();i++)
						if(player == (*inOrder)[i])
							inOrder->erase(inOrder->begin()+i);
					break;
					//battleLost 
					//teleport back to rest point, aka change Player Position.
				}
			}
		}
	}
	if(mobs->size() == 0){
		temp = TTF_RenderText_Blended(font,"YOU WON THE FIGHT!!!", fgColor);
		endBattleText.push_back(temp);
	}
}

//Modifier for the battle display via incrementing a counter
void BattleHandler::battlePhaseUpdate(int& battleMenu, SDL_Surface* screen){
	bpLoopCheck++;
}
//For Display
void BattleHandler::battleDisplayUpdate(int& battleMenu, SDL_Surface* screen){
	if(battleMenu == isFight || battleMenu == battlePhase)
		monsterSelectDisplay(screen,battleMenu);
	if(battleMenu == battlePhase){
		battlePhaseDisplay(battleMenu,screen);	
	}
	if(battleMenu == endPhase){
		endPhaseDisplay(battleMenu,screen);
	}
}
void BattleHandler::monsterSelectDisplay(SDL_Surface* screen,int& battleMenu){
	//cout << "Fighting ";
	int x = 0, y = 0;
	SDL_Rect* mobRect = new SDL_Rect[mobs->size()];
	for(int i = 0; i < (int)mobs->size(); i++){
		mobRect[i].x = i*150; mobRect[i].y = 0;
		//cout << (*mobs)[i]->getName() << " ";
		if(mobSelected == i)
			SDL_BlitSurface((*mobs)[i]->getEnemyText()[0],NULL,screen,&mobRect[i]);
		else
			SDL_BlitSurface((*mobs)[i]->getEnemyText()[1],NULL,screen,&mobRect[i]);
	}
}
void BattleHandler::battlePhaseDisplay(int& battleMenu, SDL_Surface* screen){
	SDL_Rect bText;
	bText.x = 50;
	bText.y = 400;
	if(bpLoopCheck < (int)battleText.size())
		SDL_BlitSurface(battleText[bpLoopCheck],NULL,screen,&bText);
	else{
		for(int i = 0; i < (int)battleText.size(); i++)
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
void BattleHandler::endPhaseDisplay(int& battleMenu, SDL_Surface* screen){
	SDL_Rect bText;
	bText.x = 50;
	bText.y = 400;
	if(bpLoopCheck < (int)endBattleText.size())
		SDL_BlitSurface(endBattleText[bpLoopCheck],NULL,screen,&bText);
	else{
		for(int i = 0; i < (int)endBattleText.size(); i++)
			SDL_FreeSurface(endBattleText[i]);
		battleMenu = battleEnd;
		endBattleText.clear();
	}
}

//Sets players and monsters in turn order for battle phase
void BattleHandler::turnOrder(std::vector<Entity*>* inOrder){
	inOrder->push_back((Entity*)player);
	for(int i = 0; i < (int)mobs->size(); i++)
		inOrder->push_back((Entity*)(*mobs)[i]);
	std::sort(inOrder->begin(),inOrder->end(),compareEntity_SPD);
}

//Monster Selection
void BattleHandler::moveLeft(){
	if(mobSelected > 0)
		mobSelected--;	 
}
void BattleHandler::moveRight(){
	if(mobSelected < (int)mobs->size()-1)
		mobSelected++;
}

//Flow State of battle
void BattleHandler::battleHandler(int& battleMenu,SDL_Surface* screen){
	switch(battleMenu){
		case FIGHT:
			battleMenu = isFight;
			//monsterSelectDisplay(screen, battleMenu);
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
			if(!startFight(battleMenu,screen,MUTAL)){
				//call EXP EVENT?
				battleMenu = endPhase;
				cout << "BATTLE SHOULD END" << endl;
			}
			break;
		case battlePhase:
			//battlePhaseDisplay(battleMenu,screen);
			break;
		case endPhase:
			//endPhaseDisplay(battleMenu,screen);
			cout <<" END OF BATTLE" << endl;
			break;
		case battleEnd:
			break;
		default:
			cerr << "STOP PRESSING ENTER" << endl;
			break;
	}
}
