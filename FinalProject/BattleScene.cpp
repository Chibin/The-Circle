#include <sstream>
#include "BattleScene.h"
BattleScene::BattleScene(int* _gameOver,SDL_Surface* _screen){
	TTF_Init();
	screen = _screen;
	gameOver = _gameOver;
	battleMenu = FIGHT;
	fightVal = 0; runVal = 1;
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",45);
	SDL_Color fgColor = {0,0,0};
	SDL_Color bgColor = {255,255,255};
	textFight[0] = TTF_RenderText_Blended(font, "Fight",bgColor);
	string test = "test";
	std::ostringstream oss;
	//a way to add integers for the text
	oss << test << 4;
	textRun[0] = TTF_RenderText_Shaded(font,oss.str().c_str(),fgColor,bgColor);
	bgColor.r = bgColor.g = bgColor.b = 150;
	textFight[1] = TTF_RenderText_Shaded(font, "Fight",fgColor,bgColor);
	textRun[1] = TTF_RenderText_Shaded(font, " Run ",fgColor,bgColor);
	fightLoc.x = 0; fightLoc.y = 450;
	runLoc.x = 0;
	runLoc.y = 550;
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
						if(battleMenu == RUN)
							battleMenu = FIGHT;
						break;
					case SDLK_DOWN:
						if(battleMenu == FIGHT)
							battleMenu = RUN;
						break;
					case SDLK_LEFT:
						if(battleMenu == isFight)
							bManager->moveLeft();
						break;
					case SDLK_RIGHT:
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
							gameState = OPENINGMENU; //temporary
						}
						else if(battleMenu == battlePhase)
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
	fightVal = runVal = 1;
	switch(battleMenu){
		case FIGHT:
			fightVal = 0;
			break;
		case ITEM:
			break;
		case RUN:
			runVal = 0;
			break;
		default:
			break;
	}
	SDL_BlitSurface(textFight[fightVal],NULL,screen,&fightLoc);
	SDL_BlitSurface(textRun[runVal],NULL,screen,&runLoc);
	SDL_Flip(screen);
}
BattleScene::~BattleScene(){
	TTF_CloseFont(font);
}
