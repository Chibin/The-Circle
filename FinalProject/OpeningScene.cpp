#include "OpeningScene.h"
#include "SceneManager.h"
OpeningScene::OpeningScene(SDL_Surface* screen){
	startValue = 0;
	loadValue = 0;
	quitValue = 0;
	newValue = 1;
	maxButton = 3;
	count = 1;

	//Loads NewGame Button
	newGame[0] =  SDL_LoadBMP("../Images/newGame.bmp");
	newGame[1] =  SDL_LoadBMP("../Images/newGame1.bmp");
	SDL_SetColorKey(newGame[0], SDL_SRCCOLORKEY, SDL_MapRGB(newGame[0]->format, 255, 255, 255) );
	SDL_SetColorKey(newGame[1], SDL_SRCCOLORKEY, SDL_MapRGB(newGame[1]->format, 255, 255, 255) );
	newGameRect.x = (game->getWindowWidth()/2) - (newGame[0]->w)/2;
	newGameRect.y = (game->getWindowHeight()/2- (newGame[0]->h)/2) - newGame[0]->h;

	//Loads Background
	bg = SDL_LoadBMP("../Images/bg1.bmp");
	bgRectSrc.x = 0;
	bgRectSrc.y = 0;
	bgRectSrc.h = 600;
	bgRectSrc.w = 800;
	bgRectDest.x = 0;
	bgRectDest.y = 0;
	bgRectDest.h = game->getWindowHeight();
	bgRectDest.w = game->getWindowWidth();

	//Loads the load button
	load[0] = SDL_LoadBMP("../Images/load.bmp");
	load[1] = SDL_LoadBMP("../Images/load1.bmp");
	SDL_SetColorKey(load[0], SDL_SRCCOLORKEY, SDL_MapRGB(load[0]->format, 255, 255, 255) );
	SDL_SetColorKey(load[1], SDL_SRCCOLORKEY, SDL_MapRGB(load[1]->format, 255, 255, 255) );
	loadRect.x = (game->getWindowWidth()/2) - (load[0]->w)/2;
	loadRect.y = (game->getWindowHeight()/2- (load[0]->h)/2);	

	//start[0] = SDL_LoadBMP("../Images/starta1.bmp");
	//start[1] = SDL_LoadBMP("../Images/start1.bmp");
	//startRect.x = game->getWindowWidth()/2;
	//startRect.y = game->getWindowHeight()/2;

	//Loads quit button
	quit[0] = SDL_LoadBMP("../Images/quit.bmp");
	quit[1] = SDL_LoadBMP("../Images/quit1.bmp");
	SDL_SetColorKey(quit[0], SDL_SRCCOLORKEY, SDL_MapRGB(quit[0]->format, 255, 255, 255) );
	SDL_SetColorKey(quit[1], SDL_SRCCOLORKEY, SDL_MapRGB(quit[1]->format, 255, 255, 255) );
	quitRect.x = (game->getWindowWidth()/2) - (quit[0]->w)/2;
	quitRect.y = (game->getWindowHeight()/2- (quit[0]->h)/2) + quit[0]->h;	



	SDL_BlitSurface(load[loadValue], NULL, screen, &loadRect);
	SDL_BlitSurface(newGame[newValue], NULL, screen, &newGameRect);
	//SDL_BlitSurface(start[startValue],NULL,screen,&startRect);
	SDL_BlitSurface(quit[quitValue],NULL,screen,&quitRect);
	SDL_BlitSurface(bg,&bgRectSrc,screen,&bgRectDest);
	SDL_Flip(screen);	
}

void OpeningScene::eventHandler(SDL_Event& event){

	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYUP:
			//case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_UP:
				count--;
				//std::cout << "count: " << count << std::endl;
				break;
			case SDLK_DOWN:
				count++;	
				//std::cout << "count: " << count << std::endl;
				break;
			case SDLK_RETURN:	
				//std::cout << "enter was pressed" << std::endl;
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
	if(count <= 0)
		count = maxButton;
	if(count > maxButton)
		count = 1;
	switch(count){
	case 1:
		newValue = 0;
		loadValue = 1;
		quitValue = 1;
		break;
	case 2:
		newValue = 1;
		loadValue = 0;
		quitValue = 1;
		break;
	case 3:
		newValue = 1;
		loadValue = 1;
		quitValue = 0;
		break;
	default:
		break;
	}
}

void OpeningScene::display(SDL_Surface* screen){
	//SDL_FillRect(screen,NULL,0x221122);
	
	//SDL_BlitSurface(start[startValue],NULL,screen,&startRect);
	SDL_BlitSurface(bg,&bgRectSrc,screen,&bgRectDest);
	SDL_BlitSurface(load[loadValue], NULL, screen, &loadRect);
	SDL_BlitSurface(newGame[newValue], NULL, screen, &newGameRect);
	SDL_BlitSurface(quit[quitValue],NULL,screen,&quitRect);
	SDL_Flip(screen);
}