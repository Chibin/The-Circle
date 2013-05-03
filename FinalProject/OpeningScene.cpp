#include "OpeningScene.h"
#include "SceneManager.h"
OpeningScene::OpeningScene(SDL_Surface* screen){
	startValue = 0;
	quitValue = 1;
	bg = SDL_LoadBMP("../Images/bg1.bmp");
	bgRectSrc.x = 0;
	bgRectSrc.y = 0;
	bgRectSrc.h = 600;
	bgRectSrc.w = 800;
	bgRectDest.x = 0;
	bgRectDest.y = 0;
	//std::cout << GameManager::getInstance().getWindowHeight() << std:: endl;
	bgRectDest.h = game->getWindowHeight();
	bgRectDest.w = game->getWindowWidth();
	
	start[0] = SDL_LoadBMP("../Images/starta1.bmp");
	start[1] = SDL_LoadBMP("../Images/start1.bmp");
	startRect.x = game->getWindowWidth()/2;
	startRect.y = game->getWindowHeight()/2;
	quit[0] = SDL_LoadBMP("../Images/quit.bmp");
	quit[1] = SDL_LoadBMP("../Images/quit1.bmp");
	quitRect.x = 0;
	quitRect.y = 50;	
	SDL_BlitSurface(start[startValue],NULL,screen,&startRect);
	SDL_BlitSurface(quit[quitValue],NULL,screen,&quitRect);
	SDL_BlitSurface(bg,&bgRectSrc,screen,&bgRectDest);
	SDL_Flip(screen);
}

void OpeningScene::eventHandler(SDL_Event& event){
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
						std::cout << "enter was pressed" << std::endl;
						if(startValue == 0)
							GameManager::getInstance().setGameState(GameManager::BATTLE);
						else if(!quitValue)
							GameManager::getInstance().setGameOver(true);
						break;
					case SDLK_ESCAPE:
						GameManager::getInstance().setGameOver(true);
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
	//SDL_FillRect(screen,NULL,0x221122);
	SDL_BlitSurface(bg,&bgRectSrc,screen,&bgRectDest);
	SDL_BlitSurface(start[startValue],NULL,screen,&startRect);
	SDL_BlitSurface(quit[quitValue],NULL,screen,&quitRect);
	SDL_Flip(screen);
}