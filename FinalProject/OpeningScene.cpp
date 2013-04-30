#include "OpeningScene.h"
OpeningScene::OpeningScene(int* _gameOver,SDL_Surface* screen){
	gameOver = _gameOver;
	startValue = 0;
	quitValue = 1;
	start[0] = SDL_LoadBMP("../Images/start.bmp");
	start[1] = SDL_LoadBMP("../Images/start1.bmp");
	startRect.x = 0;
	startRect.y = 0;
	quit[0] = SDL_LoadBMP("../Images/quit.bmp");
	quit[1] = SDL_LoadBMP("../Images/quit1.bmp");
	quitRect.x = 0;
	quitRect.y = 50;	
	SDL_BlitSurface(start[startValue],NULL,screen,&startRect);
	SDL_BlitSurface(quit[quitValue],NULL,screen,&quitRect);
	SDL_Flip(screen);
}

void OpeningScene::eventHandler(SDL_Event& event, int& gameState){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP]){
		startValue = 0;
		quitValue = 1;
		cout << "UP" << endl;
	}
	if( keystate[SDLK_DOWN]){
		startValue = 1;
		quitValue = 0;
		cout << "DOWN" << endl;
	}
	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_RETURN:
						if(startValue == 0)
							gameState = BATTLE;
						else if(!quitValue)
							*gameOver = 1;
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

void OpeningScene::display(SDL_Surface* screen){
	SDL_FillRect(screen,NULL,0x221122);
	SDL_BlitSurface(start[startValue],NULL,screen,&startRect);
	SDL_BlitSurface(quit[quitValue],NULL,screen,&quitRect);
	SDL_Flip(screen);
}