#include <sstream>
#include "BattleScene.h"
BattleScene::BattleScene(int* _gameOver,SDL_Surface* _screen){
	TTF_Init();
	screen = _screen;
	gameOver = _gameOver;
	battleMenu = FIGHT;
	fightVal = 0; runVal = 1;
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",40);
	SDL_Color fgColor = {255,255,0};
	SDL_Color bgColor = {255,255,255};
	textFight[0] = TTF_RenderText_Blended(font, "Fight",fgColor);
	textRun[0] = TTF_RenderText_Blended(font,"Run",fgColor);
	textItem[0] = TTF_RenderText_Blended(font,"Item",fgColor);
	textMagic[0] = TTF_RenderText_Blended(font,"Magic",fgColor);
	textFight[1] = TTF_RenderText_Blended(font, "Fight",bgColor);
	textRun[1] = TTF_RenderText_Blended(font, "Run",bgColor);
	textItem[1] = TTF_RenderText_Blended(font,"Item",bgColor);
	textMagic[1] = TTF_RenderText_Blended(font,"Magic",bgColor);
	fightLoc.x = 10; fightLoc.y = 500;
	magicLoc.x = 10; magicLoc.y = 550;
	itemLoc.x = 150; itemLoc.y = 500;
	runLoc.x = 150; runLoc.y = 550;
	player = new Player(); //just added this to test the battle sequence
	bManager = new BattleManager(player);
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
void BattleScene::eventHandler(SDL_Event& event, int& gameState){
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
						break;
					case SDLK_DOWN:
						if(battleMenu == ITEM)
							battleMenu = RUN;
						else if(battleMenu == FIGHT)
							battleMenu = MAGIC;
						break;
					case SDLK_LEFT:
						if(battleMenu == ITEM)
							battleMenu = FIGHT;
						else if(battleMenu == RUN)
							battleMenu = MAGIC;
						if(battleMenu == isFight)
							bManager->moveLeft();
						break;
					case SDLK_RIGHT:
						if(battleMenu == FIGHT)
							battleMenu = ITEM;
						else if(battleMenu == MAGIC)
							battleMenu = RUN;
						if(battleMenu == isFight)
							bManager->moveRight();
						break;
					case SDLK_RETURN:
						bManager->battleHandler(battleMenu,screen);
						if(battleMenu == battleEnd)
							gameState = OPENINGMENU; //temporary
						else if(battleMenu == battlePhase)
							bManager->battlePhaseUpdate(battleMenu,screen);
						break;
					case SDLK_z:
						bManager->battleHandler(battleMenu,screen);
						if(battleMenu == battleEnd){
							battleMenu = FIGHT;
							gameState = OPENINGMENU; //temporary
						}
						else if(battleMenu == battlePhase)
							bManager->battlePhaseUpdate(battleMenu,screen);
						else if(battleMenu == endPhase)
							bManager->battlePhaseUpdate(battleMenu,screen);
						break;
					case SDLK_x:
						if(battleMenu == isFight)
							battleMenu = FIGHT;
						break;
					case SDLK_ESCAPE:
						*gameOver = 1;
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

void BattleScene::display(SDL_Surface* screen){
	SDL_FillRect(screen,NULL,0x554455);
	if(battleMenu == isFight || battleMenu == battlePhase)
		bManager->battleUpdate(battleMenu,screen);
	if(battleMenu == battlePhase){
		bManager->battlePhaseLoop(battleMenu,screen);	
	}
	if(battleMenu == endPhase){
		bManager->endPhaseLoop(battleMenu,screen);
	}
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
	SDL_BlitSurface(textFight[fightVal],NULL,screen,&fightLoc);
	SDL_BlitSurface(textMagic[magicVal],NULL,screen,&magicLoc);
	SDL_BlitSurface(textItem[itemVal],NULL,screen,&itemLoc);
	SDL_BlitSurface(textRun[runVal],NULL,screen,&runLoc);
	SDL_Flip(screen);
}
BattleScene::~BattleScene(){
	TTF_CloseFont(font);
}