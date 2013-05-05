#include "NewCharacterScene.h"
#include "../Entity/Player.h"
//64 width 64 height for male
NewCharScreen::NewCharScreen(SDL_Surface* screen){
	type = GameManager::CHARACTERCREATION;
	std::cout << "Creating Character Creation Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	//male portrait
	malebg = load_image("../Images/charCreation/maleBG.bmp");
	maleBgRect.h = 1024;
	maleBgRect.w = 800;
	maleBgRect.x = 0;
	maleBgRect.y = 0;
	//background image
	bg = load_image("../Images/charCreation/bgChar1.bmp");
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.h = (Sint16)game->getWindowHeight();
	bgRect.w = (Sint16)game->getWindowWidth();
	//male animation
	maleChar = load_image("../Images/charCreation/maleStanding.bmp");
	//clip the male animation
	makeCharRect[0].x = 0;
	makeCharRect[0].y = 0;
	makeCharRect[0].w = 64;
	makeCharRect[0].h = 64;
	makeCharRect[1].x = 64;
	makeCharRect[1].y = 0;
	makeCharRect[1].w = 64;
	makeCharRect[1].h = 64;
	makeCharRect[2].x = 64*2;
	makeCharRect[2].y = 0;
	makeCharRect[2].w = 64;
	makeCharRect[2].h = 64;
	
	SDL_BlitSurface(bg,NULL,screen,&bgRect);
	SDL_BlitSurface(malebg,NULL,screen,&maleBgRect);
	std::cout << "Finished Loading!" << std::endl;
	SDL_Flip(screen);	
}
void NewCharScreen::eventHandler(SDL_Event& event){
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			//case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_ESCAPE:
				game->setGameState(GameManager::OPENINGMENU);
				break;
			default:
				break;
			}
		}
	}
}

void NewCharScreen::display(SDL_Surface* screen){
	SDL_BlitSurface(bg,NULL,screen,&bgRect);
	
	SDL_BlitSurface(malebg,NULL,screen,&maleBgRect);
	
	SDL_Flip(screen);	
}
void NewCharScreen::disposeResources(){
	std::cout << "Cleaning Character Creation Scene" << std::endl;
	SDL_FreeSurface( malebg );
	SDL_FreeSurface( bg );
	std::cout << "Cleaning Finished!" << std::endl;
}