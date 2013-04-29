#include "BattleScene.h"
BattleScene::BattleScene(int* _gameOver){
	TTF_Init();
	gameOver = _gameOver;
	fightVal = 0; runVal = 1;
	font = TTF_OpenFont("../Fonts/Manga Temple.ttf",45);
	SDL_Color fgColor = {0,0,0};
	SDL_Color bgColor = {255,255,255};
	textFight[0] = TTF_RenderText_Shaded(font, "Fight",fgColor,bgColor);
	textRun[0] = TTF_RenderText_Shaded(font, " Run ",fgColor,bgColor);
	bgColor.r = bgColor.g = bgColor.b = 150;
	textFight[1] = TTF_RenderText_Shaded(font, "Fight",fgColor,bgColor);
	textRun[1] = TTF_RenderText_Shaded(font, " Run ",fgColor,bgColor);
	fightLoc.x = fightLoc.y = 0;
	runLoc.x = 0;
	runLoc.y = 54;
	
}

void BattleScene::eventHandler(SDL_Event& event, int& gameState){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP]){
		cout << "UP" << endl;
		runVal = 1;
		fightVal = 0;
	}
	if( keystate[SDLK_DOWN]){
		runVal = 0;
		fightVal = 1;
		cout << "DOWN" << endl;
	}
	if( keystate[SDLK_LEFT]){
		cout << "LEFT" << endl;
	}
	if( keystate[SDLK_RIGHT]){
		cout << "RIGHT" << endl;
	}
	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_RETURN:
						cout << "STOP PRESSING ENTER" << endl;
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
	SDL_BlitSurface(textFight[fightVal],NULL,screen,&fightLoc);
	SDL_BlitSurface(textRun[runVal],NULL,screen,&runLoc);
	SDL_Flip(screen);
}
BattleScene::~BattleScene(){
	TTF_CloseFont(font);
}
