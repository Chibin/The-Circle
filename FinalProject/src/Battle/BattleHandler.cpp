#include "../Scene/BattleScene.h" //no idea why it breaks without this
#include "BattleHandler.h"
BattleHandler::BattleHandler(){
	battleText.clear();
	endBattleText.clear();
	player = &Player::getInstance();
	scene = &SceneManager::getInstance();
	magicMenuTrigger = false;
	mobSelected = 0;
	magicSelected = 0;
	prevmagicSelected = 0;
	playerDead = false;
	drawingText = false; 
	drawingComplete = false;
	player->forgetAllMagicAbilities();
	PowHammer newMagic;	FireBall newMagic2; FirstAid newMagic3;
	AngelFeathers newMagic4; DemonFang newMagic5; DumDog newMagic6;
	ParaBall newMagic7;
	player->learnMagicAbility((Magic)newMagic);
	player->learnMagicAbility((Magic)newMagic2);
	player->learnMagicAbility((Magic)newMagic3);
	player->learnMagicAbility((Magic)newMagic4);
	player->learnMagicAbility((Magic)newMagic5);
	player->learnMagicAbility((Magic)newMagic6);
	player->learnMagicAbility((Magic)newMagic7);
}
void BattleHandler::loadMobs(std::vector<Mob*>* _mobs){
	mobs = _mobs;
}

//Selected Actions
void BattleHandler::displayItems(){
}
void BattleHandler::MagicMenu(){
	if(player->getMagicAbilities().size() == 0)
		cout <<"PLAYER HAS NO ABILITIES" << endl;
	else{
		cout << player->getMagicAbilities()[0].getMagicName() << endl;
		cout << player->getMagicAbilities()[0].getMagicDamage() << endl;
		cout << "displaying Magic" << endl;
	}

}
bool BattleHandler::startFight(int& battleMenu, enum battleCondition condition){
	if(mobs->size()  == 0)
		return false;
	if(mobSelected > (int)mobs->size()-1)
		mobSelected = mobs->size()-1;
	string mobAttacked = (*mobs)[mobSelected]->getName();
	std::vector<Entity*>* inOrder = new std::vector<Entity*>();
	prevPhase = battleMenu;
	turnOrder(inOrder);
	battleLog(inOrder,mobAttacked,condition,battleMenu);
	if(mobs->size() == 0)
		battleMenu = endPhase;
	else
		battleMenu = battlePhase;
	bpLoopCheck = -1;
	return true;
}
void BattleHandler::run(int& battleMenu){
	int fasterMonsters = 1;
	SDL_Surface* temp;
	SDL_Color fgColor = {255,255,255};
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
	for(int i = 0; i < (int)mobs->size();i++){
		if(player->getSPD() < (*mobs)[i]->getSPD())
			fasterMonsters++;
	}
	if(fasterMonsters == 0){
		string sentence = player->getName();
		sentence += " ran away!";
		temp = TTF_RenderText_Blended(font,sentence.c_str(),fgColor);
		endBattleText.push_back(temp);
		battleMenu = endPhase;
	}
	else{
		double chanceToRun = (1.0/(double)fasterMonsters)*100;
		double runAway = rand()%100+1;
		if(runAway <= chanceToRun){
			string sentence = player->getName();
			sentence += " ran away!";
			temp = TTF_RenderText_Blended(font,sentence.c_str(),fgColor);
			endBattleText.push_back(temp);
			battleMenu = endPhase;
		}
		else{
			fgColor.g = 100; fgColor.b = 0;
			temp = TTF_RenderText_Blended(font,"Player is flanked!",fgColor);
			battleText.push_back(temp);
			battleMenu = battlePhase;
			//commence attack of mob here
			startFight(battleMenu,FLANKED);
		}
	}
	bpLoopCheck = -1;
}
//BattleCalculations
void BattleHandler::battleLog(std::vector<Entity*>* inOrder, string mobAttacked, enum battleCondition condition,int battleMenu){
	SDL_Surface* temp;
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
	SDL_Color fgColor = {255,200,0};
	SDL_Color deadColor = {255,50,0};
	for(int i = 0; i < (int)inOrder->size(); i++){
		std::ostringstream oss;
		if(player->getName() == (*inOrder)[i]->getName()){
			if(condition != FLANKED){
				//Attacking selected mob
				if(battleMenu == isFight){
					oss << player->getName() << " attacked " << mobAttacked << " for " << player->getSTR() << " damage!";
					temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
					battleText.push_back(temp);
					(*mobs)[mobSelected]->setHP((*mobs)[mobSelected]->getHP()-player->getSTR());
					if((*mobs)[mobSelected]->getHP() <= 0){
						std::ostringstream dead;
						dead << (*mobs)[mobSelected]->getName() << " has been slain.";
						temp = TTF_RenderText_Blended(font,dead.str().c_str(),deadColor);
						battleText.push_back(temp);
						for(int i = 0; i < (int)inOrder->size();i++)
							if((*mobs)[mobSelected] == (*inOrder)[i])
								inOrder->erase(inOrder->begin()+i);
						delete (*mobs)[mobSelected];
						mobs->erase(mobs->begin()+mobSelected);
						//add to exp gained this fight
					}
				}
				else if(battleMenu == magicTargetSelect){
					//calling magic battle system
					Magic selectedMagic = player->getMagicAbilities()[magicSelected];
					MagicBattlePhase(selectedMagic,inOrder);
				}
			}
		}
		else{
			//Mob attacks selected player
			//Make an AI, may be...?
			//checks if player has a free attack
			if(condition != PREEMPTIVE){
				oss << (*inOrder)[i]->getName() << " attacks Player with " << (*inOrder)[i]->getSTR() << " damage!";
				temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
				battleText.push_back(temp);
				player->setHP(player->getHP()-(*inOrder)[i]->getSTR());
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

void BattleHandler::MagicBattlePhase(Magic selectedMagic,std::vector<Entity*>* inOrder){
	switch(selectedMagic.getMagicType()){
		case Magic::DAMAGE:
			magicDamage(selectedMagic,inOrder);
			break;
		case Magic::HEAL:
			magicHeal(selectedMagic,inOrder);
			break;
		case Magic::BUFF:
			magicBuff(selectedMagic,inOrder);
			break;
		case Magic::DEBUFF:
			magicDebuff(selectedMagic,inOrder);
			break;
		default:
			break;
	}
}
void BattleHandler::magicDamage(Magic selectedMagic,std::vector<Entity*>* inOrder){
	SDL_Surface* temp;
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
	SDL_Color fgColor = {255,200,0};
	SDL_Color deadColor = {255,50,0};
	switch(selectedMagic.getMagicTargetType()){
		case Magic::SINGLE:{
			std::ostringstream oss;
			oss << player->getName() << " attacked " << (*mobs)[mobSelected]->getName() << " for " << selectedMagic.getMagicDamage() << " damage!";
			temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
			battleText.push_back(temp);
			(*mobs)[mobSelected]->setHP((*mobs)[mobSelected]->getHP()-selectedMagic.getMagicDamage());
			if((*mobs)[mobSelected]->getHP() <= 0){
				std::ostringstream dead;
				dead << (*mobs)[mobSelected]->getName() << " has been slain.";
				temp = TTF_RenderText_Blended(font,dead.str().c_str(),deadColor);
				battleText.push_back(temp);
				for(int i = 0; i < (int)inOrder->size();i++)
					if((*mobs)[mobSelected] == (*inOrder)[i])
						inOrder->erase(inOrder->begin()+i);
				delete (*mobs)[mobSelected];
				mobs->erase(mobs->begin()+mobSelected);
				//add to exp gained this fight
				}
			break;
		}
		case Magic::AOE:{
			for(int i = 0; i < (int)mobs->size();i++){
				std::ostringstream oss;
				oss << player->getName() << " attacked " << (*mobs)[i]->getName() << " for " << selectedMagic.getMagicDamage() << " damage!";
				temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
				battleText.push_back(temp);
				(*mobs)[i]->setHP((*mobs)[i]->getHP()-selectedMagic.getMagicDamage());
				if((*mobs)[i]->getHP() <= 0){
					std::ostringstream dead;
					dead << (*mobs)[i]->getName() << " has been slain.";
					temp = TTF_RenderText_Blended(font,dead.str().c_str(),deadColor);
					battleText.push_back(temp);
					for(int j = 0; j < (int)inOrder->size();j++)
						if((*mobs)[i] == (*inOrder)[j])
							inOrder->erase(inOrder->begin()+j);
					delete (*mobs)[i];
					mobs->erase(mobs->begin()+i);
					i--;
					//add to exp gained this fight
					}
			}
			break;
		}
		default:
			break;
	}
}
void BattleHandler::magicHeal(Magic selectedMagic,std::vector<Entity*>* inOrder){
	SDL_Surface* temp;
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",30);
	SDL_Color fgColor = {0,255,50};
	switch(selectedMagic.getMagicTargetType()){
		case Magic::SINGLE:{
			std::ostringstream oss;
			oss << player->getName() << " healed " << player->getName() << " for " << selectedMagic.getMagicDamage() << " health!";
			temp = TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
			battleText.push_back(temp);
			player->setHP(player->getHP()+selectedMagic.getMagicDamage());
			cout << player->getHP() << endl;
			break;
		}
		case Magic::AOE:
			break;
		default:
			break;
	}
}
void BattleHandler::magicBuff(Magic selectedMagic,std::vector<Entity*>* inOrder){
	switch(selectedMagic.getMagicTargetType()){
		case Magic::SINGLE:
			break;
		case Magic::AOE:
			break;
		default:
			break;
	}

}
void BattleHandler::magicDebuff(Magic selectedMagic,std::vector<Entity*>* inOrder){
	switch(selectedMagic.getMagicTargetType()){
		case Magic::SINGLE:
			break;
		case Magic::AOE:
			break;
		default:
			break;
	}
}

//Modifier for the battle display via incrementing a counter
void BattleHandler::battlePhaseUpdate(int& battleMenu){
	if(drawingComplete){
		drawingText = false;
		bpLoopCheck++;
	}
	else if(drawingText){
		drawingComplete = true;
	}
}
//For Display
void BattleHandler::battleDisplayUpdate(int& battleMenu){
	if(battleMenu == isFight || battleMenu == battlePhase)
		monsterSelectDisplay(battleMenu);
	else if(battleMenu == isMagic){
		magicMenuDisplay();
	}
	else if(battleMenu == magicTargetSelect){
		magicSelectDisplay();
	}
	if(battleMenu == battlePhase){
		battlePhaseDisplay(battleMenu);	
	}
	else if(battleMenu == endPhase){
		endPhaseDisplay(battleMenu);
	}
	else if(battleMenu == battleEnd){
		battleMenu = FIGHT;
		scene->setGameScene(SceneManager::NORMAL); //temporary
	}
}
void BattleHandler::monsterSelectDisplay(int& battleMenu){
	int x = 0, y = 0;
	SDL_Rect* mobRect = new SDL_Rect[mobs->size()];
	for(int i = 0; i < (int)mobs->size(); i++){
		mobRect[i].x = i*150; mobRect[i].y = 0;
		if(mobSelected == i)
			SDL_BlitSurface((*mobs)[i]->getEnemyText()[0],NULL,scene->getScreen(),&mobRect[i]);
		else
			SDL_BlitSurface((*mobs)[i]->getEnemyText()[1],NULL,scene->getScreen(),&mobRect[i]);
	}
}

void BattleHandler::magicSelectDisplay(){
	int x = 0, y = 0;
	SDL_Rect* mobRect = new SDL_Rect[mobs->size()];
	Magic selectedMagic = player->getMagicAbilities()[magicSelected];
		if(selectedMagic.getMagicTargetType() == Magic::SINGLE && selectedMagic.getMagicType() == Magic::DAMAGE){
		for(int i = 0; i < (int)mobs->size(); i++){
			mobRect[i].x = i*150; mobRect[i].y = 0;
			if(mobSelected == i)
				SDL_BlitSurface((*mobs)[i]->getEnemyText()[0],NULL,scene->getScreen(),&mobRect[i]);
			else
				SDL_BlitSurface((*mobs)[i]->getEnemyText()[1],NULL,scene->getScreen(),&mobRect[i]);
		}
	}
	else if(selectedMagic.getMagicTargetType() == Magic::AOE && selectedMagic.getMagicType() == Magic::DAMAGE){
		for(int i = 0; i < (int)mobs->size(); i++){
			mobRect[i].x = i*150; mobRect[i].y = 0;
			SDL_BlitSurface((*mobs)[i]->getEnemyText()[0],NULL,scene->getScreen(),&mobRect[i]);
		}
	}
	else if(selectedMagic.getMagicTargetType() == Magic::SINGLE && selectedMagic.getMagicType() == Magic::HEAL){
		mobRect[0].x = 0; mobRect[0].y = 0;
		SDL_Surface* temp;
		font = TTF_OpenFont("../Fonts/Manga Temple.ttf",25);
		SDL_Color fgColor = {255,255,0};
		temp = TTF_RenderText_Blended(font,player->getName().c_str(), fgColor);
		SDL_BlitSurface(temp,NULL,scene->getScreen(),&mobRect[0]);
		SDL_FreeSurface(temp);
	}
}
int BattleHandler::indexScrollDeteminer(int& startingIndex, int currentIndex, int scrollLimit){
	if(currentIndex >= startingIndex+scrollLimit)
		return startingIndex++;
	else if(currentIndex < startingIndex && startingIndex >= 0)
		return startingIndex--;
	return startingIndex;
}
void BattleHandler::magicMenuDisplay(){
	int x = 0, y = 0,  j = 0, scrollLimit =5;
	SDL_Rect* mobRect = new SDL_Rect[player->getMagicAbilities().size()];
	for(int i = indexScrollDeteminer(prevmagicSelected,magicSelected,scrollLimit) ; i < (int)player->getMagicAbilities().size() && j < 5; i++){
		mobRect[i].x = 315; mobRect[i].y = 405+j*35;
		if(magicSelected == i)
			SDL_BlitSurface(player->getMagicAbilities()[i].getMagicTextImage()[0],NULL,scene->getScreen(),&mobRect[i]);
		else
			SDL_BlitSurface(player->getMagicAbilities()[i].getMagicTextImage()[1],NULL,scene->getScreen(),&mobRect[i]);
		j++;
	}
}
void BattleHandler::textScrollDisplay(std::vector<SDL_Surface*> &textVector,int index,bool& drawingText,bool& drawingComplete, SDL_Rect startPos){
	if(!drawingText){
			drawingText = true; drawingComplete = false;
			textScroller.x = 0; textScroller.y = 0;
			textScroller.w = 0;
			textScroller.h = textVector[index]->h;
		}
		if(textScroller.w >= textVector[index]->w && drawingComplete == false){
			drawingComplete = true;
		}
		else if(!drawingComplete){
				textScroller.w++;
				SDL_BlitSurface(textVector[index],&textScroller,scene->getScreen(),&startPos);
		}
		else
				SDL_BlitSurface(textVector[index],NULL,scene->getScreen(),&startPos);
}
void BattleHandler::battlePhaseDisplay(int& battleMenu){
	SDL_Rect bText;
	bText.x = 50;
	bText.y = 400;
	if(bpLoopCheck == -1)
		bpLoopCheck = 0;
	if(bpLoopCheck < (int)battleText.size()){
		textScrollDisplay(battleText,bpLoopCheck,drawingText,drawingComplete,bText);
	}
	else{
		for(int i = 0; i < (int)battleText.size(); i++)
			SDL_FreeSurface(battleText[i]);
		if(prevPhase == magicTargetSelect)
			battleMenu = MAGIC;
		else
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
		if(battleText.size() == 0 && (int)mobs->size() == 0)
			battleMenu = endPhase;
	}
}
void BattleHandler::endPhaseDisplay(int& battleMenu){
	SDL_Rect bText;
	bText.x = 50;
	bText.y = 400;
	//makes sure that all the battleText are displayed
	if(battleText.size() !=0){
		battlePhaseDisplay(battleMenu);
		battleMenu = battlePhase;
		return;
	}
	if(bpLoopCheck == -1)
		bpLoopCheck = 0;
	if(bpLoopCheck < (int)endBattleText.size())
			textScrollDisplay(endBattleText,bpLoopCheck,drawingText,drawingComplete,bText);
	else{
		for(int i = 0; i < (int)endBattleText.size(); i++)
			SDL_FreeSurface(endBattleText[i]);
		battleMenu = battleEnd;
		endBattleText.clear();
	}
	if(bpLoopCheck == (int)endBattleText.size()){
		for(int i = 0; i < (int)endBattleText.size(); i++)
			SDL_FreeSurface(endBattleText[i]);
		battleMenu = battleEnd;
		endBattleText.clear();
		bpLoopCheck = -1;
	}
}

//Sets players and monsters in turn order for battle phase
void BattleHandler::turnOrder(std::vector<Entity*>* inOrder){
	inOrder->push_back((Entity*)player);
	for(int i = 0; i < (int)mobs->size(); i++)
		inOrder->push_back((Entity*)(*mobs)[i]);
	std::sort(inOrder->begin(),inOrder->end(),compareEntity_SPD);
}

//Input Handler
void BattleHandler::inputHandler(){

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
//Magic Selection
void BattleHandler::magicUp(){
	if(magicSelected > 0)
		magicSelected--;
}
void BattleHandler::magicDown(){
	if(magicSelected < (int)player->getMagicAbilities().size()-1)
		magicSelected++;
}
//Flow State of battle
void BattleHandler::battleHandler(int& battleMenu){
	switch(battleMenu){
		case FIGHT:
			battleMenu = isFight;
			break;
		case MAGIC:
			battleMenu = isMagic;
			MagicMenu();
			break;
		case ITEM:
			cout << "ITEMS WHERE R U" << endl;
			break;
		case RUN:
			run(battleMenu);
			break;
		case isFight:
			if(!startFight(battleMenu,MUTAL)){
				//call EXP EVENT?
				battleMenu = endPhase;
			}
			break;
		case isMagic:
			battleMenu = magicTargetSelect;
			break;
		case magicTargetSelect:
			if(!startFight(battleMenu,MUTAL)){
				//call EXP EVENT?
				battleMenu = endPhase;
			}
			break;
		case battlePhase:
			break;
		case endPhase:
			break;
		case battleEnd:
			break;
		default:
			cerr << "STOP PRESSING ENTER" << endl;
			break;
	}
}