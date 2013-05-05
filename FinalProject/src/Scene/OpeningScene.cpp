#include "OpeningScene.h"
#include "../Manager/SceneManager.h"
OpeningScene::OpeningScene(SDL_Surface* screen){
	maxButton = 2;
	count = 0;
	type = GameManager::OPENINGMENU;
	std::cout << "Creating Menu Scene" << std::endl;
	std::cout << "Loading OpeningScene Resources..." << std::endl; 
	//Loads NewGame Button
	newGame[1] =  load_imageWhite("../Images/opening/newGame.bmp");
	newGame[0] =  load_imageWhite("../Images/opening/newGame1.bmp");
	newGameRect.x = (Sint16)(game->getWindowWidth()/2) - (newGame[0]->w)/2;
	newGameRect.y = (Sint16)(game->getWindowHeight()/2- (newGame[0]->h)/2) - newGame[0]->h;

	//Loads Background
	bg = SDL_LoadBMP("../Images/opening/bg3.bmp");
	bgRectSrc.x = 0;
	bgRectSrc.y = 0;
	bgRectSrc.h = 600;
	bgRectSrc.w = 800;
	bgRectDest.x = 0;
	bgRectDest.y = 0;
	bgRectDest.h = (Sint16)game->getWindowHeight();
	bgRectDest.w = (Sint16)game->getWindowWidth();

	//Loads the load button
	load[1] = load_imageWhite("../Images/opening/load.bmp");
	load[0] = load_imageWhite("../Images/opening/load1.bmp");
	loadRect.x = (Sint16)(game->getWindowWidth()/2) - (load[0]->w)/2;
	loadRect.y = (Sint16)(game->getWindowHeight()/2- (load[0]->h)/2);	

	//Loads quit button
	quit[1] = load_imageWhite("../Images/opening/quit.bmp");
	quit[0] = load_imageWhite("../Images/opening/quit1.bmp");
	quitRect.x = (Sint16)(game->getWindowWidth()/2) - (quit[0]->w)/2;
	quitRect.y = (Sint16)(game->getWindowHeight()/2- (quit[0]->h)/2) + quit[0]->h;	


	//loads it on screen
	SDL_BlitSurface(load[0], NULL, screen, &loadRect);
	SDL_BlitSurface(newGame[1], NULL, screen, &newGameRect);
	SDL_BlitSurface(quit[0],NULL,screen,&quitRect);
	SDL_BlitSurface(bg,&bgRectSrc,screen,&bgRectDest);

	std::cout << "Finished loading!" << std::endl;
	SDL_Flip(screen);	
}

void OpeningScene::eventHandler(SDL_Event& event){

	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			//case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_UP:
				count--;
				break;
			case SDLK_DOWN:
				count++;	
				break;
			case SDLK_RETURN:	
				switch(count){
				case 0:
					game->setGameState(GameManager::CHARACTERCREATION);
					break;
				case 1:
					game->setGameState(GameManager::BATTLE);
					break;
				default:
					game->setGameOver(true);
					break;
				}
				break;
			case SDLK_z:	
				switch(count){
				case 0:
					game->setGameState(GameManager::CHARACTERCREATION);
					break;
				case 1:
					game->setGameState(GameManager::BATTLE);
					break;
				default:
					game->setGameOver(true);
					break;
				}
				break;
			case SDLK_ESCAPE:
				game->setGameOver(true);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	if(count < 0)
		count = maxButton;
	if(count > maxButton)
		count = 0;

}

void OpeningScene::display(SDL_Surface* screen){
	SDL_BlitSurface(bg,&bgRectSrc,screen,&bgRectDest);
	switch(count){
	case 0:
		SDL_BlitSurface(newGame[1], NULL, screen, &newGameRect);
		SDL_BlitSurface(load[0], NULL, screen, &loadRect);
		SDL_BlitSurface(quit[0],NULL,screen,&quitRect);
		break;
	case 1:
		SDL_BlitSurface(newGame[0], NULL, screen, &newGameRect);
		SDL_BlitSurface(load[1], NULL, screen, &loadRect);
		SDL_BlitSurface(quit[0],NULL,screen,&quitRect);
		break;
	case 2:
		SDL_BlitSurface(newGame[0], NULL, screen, &newGameRect);
		SDL_BlitSurface(load[0], NULL, screen, &loadRect);
		SDL_BlitSurface(quit[1],NULL,screen,&quitRect);
		break;
	}

	SDL_Flip(screen);
}

void OpeningScene::disposeResources(){
	std::cout << "Cleaning Menu Scene" << std::endl;
	for(int i = 0; i <2; i++){
		SDL_FreeSurface(newGame[i]);
		SDL_FreeSurface(quit[i]);
		SDL_FreeSurface(load[i]);
	}
	SDL_FreeSurface(bg);
	std::cout << "Cleaning Finished!" << std::endl;
}