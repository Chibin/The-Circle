#include "NewCharacterScene.h"
#include "../Entity/Player.h"
//64 width 64 height for male
NewCharScreen::NewCharScreen(SDL_Surface* screen){
	type = GameManager::CHARACTERCREATION;
	currentTick = SDL_GetTicks();
	lastTick = 0;
	char1Tick = 0;
	char2Tick = 0;
	back = false;
	selected = true;
	std::cout << "Creating Character Creation Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	//male portrait
	malebg = load_imageWhite("../Images/charCreation/maleBG.bmp");
	maleBgRect.h = 1024;
	maleBgRect.w = 800;
	maleBgRect.y = 0;
	maleBgRect.x = 0;
	//female portait
	femalebg = load_imageWhite("../Images/charCreation/femaleBG1.bmp");
	femaleBgRect.h = 600;
	femaleBgRect.w = 469;
	femaleBgRect.y = 0;
	femaleBgRect.x = 0;

	//background image
	bg = load_imageWhite("../Images/charCreation/bgChar2.bmp");
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.h = (Sint16)game->getWindowHeight();
	bgRect.w = (Sint16)game->getWindowWidth();

	bg1 = load_imageWhite("../Images/charCreation/bgChar3.bmp");
	bgRect1.x = 0;
	bgRect1.y = 0;
	bgRect1.h = (Sint16)game->getWindowHeight();
	bgRect1.w = (Sint16)game->getWindowWidth();

	//male animation selected
	maleChar = load_imageBlue("../Images/charCreation/maleStanding1.bmp");
	maleChar1 = load_imageBlue("../Images/charCreation/maleStanding2.bmp");
	//clip the male animation
	maleCharRect[0].x = 0;
	maleCharRect[0].y = 0;
	maleCharRect[0].w = 64;
	maleCharRect[0].h = 64;

	maleCharRect[1].x = 64;
	maleCharRect[1].y = 0;
	maleCharRect[1].w = 64;
	maleCharRect[1].h = 64;

	maleCharRect[2].x = 128;
	maleCharRect[2].y = 0;
	maleCharRect[2].w = 64;
	maleCharRect[2].h = 64;

	femaleChar = load_imageBlue("../Images/charCreation/girlStanding1.bmp");
	femaleChar1 = load_imageBlue("../Images/charCreation/girlStanding2.bmp");
	//clip the female animation
	femaleCharRect[0].x = 0;
	femaleCharRect[0].y = 0;
	femaleCharRect[0].w = 64;
	femaleCharRect[0].h = 64;

	femaleCharRect[1].x = 64;
	femaleCharRect[1].y = 0;
	femaleCharRect[1].w = 64;
	femaleCharRect[1].h = 64;

	femaleCharRect[2].x = 128;
	femaleCharRect[2].y = 0;
	femaleCharRect[2].w = 64;
	femaleCharRect[2].h = 64;

	char1.x = 500;
	char1.y = 300;

	char2.x = 650;
	char2.y = 300;
	SDL_BlitSurface(bg,NULL,screen,&bgRect);
	SDL_BlitSurface(malebg,NULL,screen,&maleBgRect);
	//SDL_BlitSurface(femalebg,NULL,screen,&femaleBgRect);
	SDL_BlitSurface(maleChar,&maleCharRect[char1Tick],screen,&char1);
	SDL_BlitSurface(femaleChar,&femaleCharRect[char2Tick],screen,&char2);
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
				selected = true;
				break;
			case SDLK_RIGHT:
				selected = false;
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
	currentTick = SDL_GetTicks();
	if(currentTick - lastTick > 150)
	{
		lastTick = currentTick;
		//update animation
		if(selected){
			char2Tick = 0;
			if(char1Tick == 0)
				back = false;
			if(!back)
				char1Tick++;
			else
				char1Tick--;
			if(char1Tick == 2){
				back = !back;
			}	
			if(char1Tick == 0)
				back = !back;
		}
		else{
			char1Tick = 0;
			if(char2Tick == 0) 
				back = false;
			if(!back)
				char2Tick++;
			else
				char2Tick--;
			if(char1Tick == 2)
				back = !back;	
			if(char1Tick == 0)
				back = !back;

		}
	}
	

	if (selected){
		SDL_BlitSurface(bg,NULL,screen,&bgRect);
		SDL_BlitSurface(malebg,NULL,screen,&maleBgRect);
	}
	else{
		SDL_BlitSurface(bg1,NULL,screen,&bgRect1);
		SDL_BlitSurface(femalebg,NULL,screen,&femaleBgRect);
	}
	SDL_BlitSurface(maleChar,&maleCharRect[char1Tick],screen,&char1);
	SDL_BlitSurface(femaleChar,&femaleCharRect[char2Tick],screen,&char2);
	SDL_Flip(screen);	
}
void NewCharScreen::disposeResources(){
	std::cout << "Cleaning Character Creation Scene" << std::endl;
	SDL_FreeSurface( malebg );
	SDL_FreeSurface( bg );
	std::cout << "Cleaning Finished!" << std::endl;
}