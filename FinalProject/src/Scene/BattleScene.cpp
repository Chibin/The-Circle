#include <sstream>
#include "BattleScene.h"
#include "../Manager/GameManager.h"
BattleScene::BattleScene(){
	TTF_Init();
	type = SceneManager::BATTLE;
	battleMenu = FIGHT;
	fightVal = 0; runVal = 1;
	font = TTF_OpenFont("../Fonts/coolvetica.ttf",40);
	SDL_Color fgColor = {255,255,0};
	SDL_Color bgColor = {255,255,255};
	bgItemMagicMenu = SDL_LoadBMP("../Images/battle/ItemMagicMenu.bmp");
	SDL_SetColorKey(bgItemMagicMenu,SDL_SRCCOLORKEY,SDL_MapRGB(bgItemMagicMenu->format,255,0,255));
	bgBattleMenu = SDL_LoadBMP("../Images/battle/MenuBox.bmp");
	SDL_SetColorKey(bgBattleMenu, SDL_SRCCOLORKEY, SDL_MapRGB(bgBattleMenu->format, 255,0,255));
	textBox = SDL_LoadBMP("../Images/battle/TextBox.bmp");
	SDL_SetColorKey(textBox, SDL_SRCCOLORKEY, SDL_MapRGB(textBox->format, 255,0,255));
	charInfo = SDL_LoadBMP("../Images/battle/CharacterBattleInfo.bmp");
	SDL_SetColorKey(charInfo, SDL_SRCCOLORKEY, SDL_MapRGB(charInfo->format, 255,0,255));
	textFight[0] = TTF_RenderText_Blended(font, "Fight",fgColor);
	textRun[0] = TTF_RenderText_Blended(font,"Run",fgColor);
	textItem[0] = TTF_RenderText_Blended(font,"Item",fgColor);
	textMagic[0] = TTF_RenderText_Blended(font,"Skill",fgColor);
	textFight[1] = TTF_RenderText_Blended(font, "Fight",bgColor);
	textRun[1] = TTF_RenderText_Blended(font, "Run",bgColor);
	textItem[1] = TTF_RenderText_Blended(font,"Item",bgColor);
	textMagic[1] = TTF_RenderText_Blended(font,"Skill",bgColor);
	bgBattleMenuLoc.x = 0; bgBattleMenuLoc.y = 473; //463 = height(600) - 127(height of picture) + 10
	itemMagicMenuLoc.x = 195; itemMagicMenuLoc.y = 360;
	textBoxLoc.x = 0; textBoxLoc.y = 473;
	fightLoc.x = 25; fightLoc.y = 485;
	magicLoc.x = 25; magicLoc.y = 535;
	itemLoc.x = 165; itemLoc.y = 485;
	runLoc.x = 165; runLoc.y = 535;
	charInfoLoc.x = 0+594; charInfoLoc.y = 0;
	//player = &Player::getInstance(); //just added this to test the battle sequence
	bManager = new BattleHandler();
	loadMobs();
}

void BattleScene::loadMobs(){
	std::vector<Mob*>* mobs;
	mobs = new std::vector<Mob*>();
	Mob* temp = new Mob();
	temp->setName("Mob1");
	temp->setSPD(5);
	Mob* temp2 = new Mob();
	temp2->setName("Mob2");
	Mob* temp3 = new Mob();
	temp2->setSPD(7);
	mobs->push_back(temp);
	temp3->setName("Mob3");
	mobs->push_back(temp2);
	mobs->push_back(temp3);
	bManager->loadMobs(mobs);
}

//change the gameState to transition to a different Scene
void BattleScene::eventHandler(SDL_Event& event){
	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_UP:
						if(battleMenu == MAGIC)
							battleMenu = FIGHT;
						else if(battleMenu == RUN)
							battleMenu = ITEM;
						if(battleMenu == isMagic)
							bManager->magicUp();
						break;
					case SDLK_DOWN:
						if(battleMenu == ITEM)
							battleMenu = RUN;
						else if(battleMenu == FIGHT)
							battleMenu = MAGIC;
						if(battleMenu == isMagic)
							bManager->magicDown();
						break;
					case SDLK_LEFT:
						if(battleMenu == ITEM)
							battleMenu = FIGHT;
						else if(battleMenu == RUN)
							battleMenu = MAGIC;
						if(battleMenu == isFight || battleMenu == magicTargetSelect)
							bManager->moveLeft();
						break;
					case SDLK_RIGHT:
						if(battleMenu == FIGHT)
							battleMenu = ITEM;
						else if(battleMenu == MAGIC)
							battleMenu = RUN;
						if(battleMenu == isFight || battleMenu == magicTargetSelect)
							bManager->moveRight();
						break;
					case SDLK_RETURN:
						bManager->battleHandler(battleMenu);
						if(battleMenu == battlePhase)
							bManager->textUpdate(battleMenu);
						else if(battleMenu == endPhase)
							bManager->textUpdate(battleMenu);
						break;
					case SDLK_z:
						bManager->battleHandler(battleMenu);
						if(battleMenu == battlePhase)
							bManager->textUpdate(battleMenu);
						else if(battleMenu == endPhase)
							bManager->textUpdate(battleMenu);
						break;
					case SDLK_x: //basically a cancel action command, goes back to the previous state
						if(battleMenu == isFight)
							battleMenu = FIGHT;
						else if(battleMenu == isMagic)
							battleMenu = MAGIC;
						else if(battleMenu == magicTargetSelect)
							battleMenu = isMagic;
						break;
					case SDLK_ESCAPE:
						scene->setGameScene(SceneManager::NORMAL);
						//game->setGameOver(true);
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}
void BattleScene::displayCharacterInfo(){
	SDL_Surface *temp;
	TTF_Font *tempFont;
	SDL_Rect tempLoc;
	tempFont = TTF_OpenFont("../Fonts/coolvetica.ttf",25);
	SDL_Color fgColor = {255,255,255};
	std::ostringstream oss;
	oss << player->getName();
	temp = TTF_RenderText_Blended(tempFont,oss.str().c_str(),fgColor);
	tempLoc.x = 10+594; tempLoc.y = 0;
	SDL_BlitSurface(temp,NULL,scene->getScreen(),&tempLoc);
	SDL_FreeSurface(temp);
	oss.str("");
	oss << "HP: ";
	temp = TTF_RenderText_Blended(tempFont,oss.str().c_str(),fgColor);
	tempLoc.x = 10+594; tempLoc.y = 30;
	SDL_BlitSurface(temp,NULL,scene->getScreen(),&tempLoc);
	//change color of HP	
	oss.str("");
	oss	<< player->getHP() << "/" << player->getMaxHP();
	if(player->getHP() == player->getMaxHP()){
		fgColor.r = 0; fgColor.g = 255; fgColor.b = 50;
	}
	else if(player->getHP() <= player->getMaxHP()/4){
		fgColor.g = 255; fgColor.g = 10; fgColor.b = 0;
	}
	else if(player->getHP() <= player->getMaxHP()/2){
		fgColor.r = 255; fgColor.g = 150; fgColor.b = 0;
	}
	else{
		fgColor.g = 255; fgColor.g = 255; fgColor.b = 255;
	}
	temp = TTF_RenderText_Blended(tempFont,oss.str().c_str(),fgColor);
	tempLoc.x = 90+594; tempLoc.y = 30;
	SDL_BlitSurface(temp,NULL,scene->getScreen(),&tempLoc);
	SDL_FreeSurface(temp);
	fgColor.r = 255; fgColor.g = 255; fgColor.b = 255;
	oss.str("");
	oss << "MP: ";
	temp = TTF_RenderText_Blended(tempFont,oss.str().c_str(),fgColor);
	tempLoc.x = 10+594; tempLoc.y = 60;
	SDL_BlitSurface(temp,NULL,scene->getScreen(),&tempLoc);
	//change color of HP	
	oss.str("");
	oss << player->getMP() << "/" << player->getMaxMP();
	if(player->getMP() == player->getMaxMP()){
		fgColor.r = 0; fgColor.g = 100; fgColor.b = 255;
	}
	else if(player->getMP() <= player->getMaxMP()/4){
		fgColor.g = 255; fgColor.g = 50; fgColor.b = 0;
	}
	else if(player->getMP() <= player->getMaxMP()/2){
		fgColor.r = 192; fgColor.g = 255; fgColor.b = 0;
	}
	else{
		fgColor.r = 0; fgColor.g = 255; fgColor.b = 126;
	}
	temp = TTF_RenderText_Blended(tempFont,oss.str().c_str(),fgColor);
	tempLoc.x = 90+594; tempLoc.y = 60;
	temp = TTF_RenderText_Blended(tempFont,oss.str().c_str(),fgColor);
	SDL_BlitSurface(temp,NULL,scene->getScreen(),&tempLoc);
	SDL_FreeSurface(temp);
	TTF_CloseFont(tempFont);
}
void BattleScene::display(){
	SDL_FillRect(scene->getScreen(),NULL,0x554455);
	fightVal = runVal = itemVal = magicVal = 1;
	switch(battleMenu){
		case FIGHT:
			fightVal = 0;
			break;
		case MAGIC:
			magicVal = 0;
			break;
		case ITEM:
			itemVal = 0;
			break;
		case RUN:
			runVal = 0;
			break;
		default:
			break;
	}
	SDL_BlitSurface(charInfo,NULL,scene->getScreen(),&charInfoLoc);
	SDL_BlitSurface(bgBattleMenu,NULL,scene->getScreen(),&bgBattleMenuLoc);
	SDL_BlitSurface(textFight[fightVal],NULL,scene->getScreen(),&fightLoc);
	SDL_BlitSurface(textMagic[magicVal],NULL,scene->getScreen(),&magicLoc);
	SDL_BlitSurface(textItem[itemVal],NULL,scene->getScreen(),&itemLoc);
	SDL_BlitSurface(textRun[runVal],NULL,scene->getScreen(),&runLoc);
	displayCharacterInfo();
	if(battleMenu == isMagic || battleMenu == isItem)
		SDL_BlitSurface(bgItemMagicMenu,NULL,scene->getScreen(),&itemMagicMenuLoc);
	else if(battleMenu == battlePhase || battleMenu == endPhase)
		SDL_BlitSurface(textBox,NULL,scene->getScreen(),&textBoxLoc);
	bManager->battleDisplayUpdate(battleMenu);
	SDL_Flip(scene->getScreen());
}
BattleScene::~BattleScene(){
	TTF_CloseFont(font);
}

void BattleScene::disposeResources(){
}
