#include "CharInfoScene.h"

CharInfoScene::CharInfoScene(){
	type = SceneManager::CHARINFO;
	std::cout << "Entering CharInfo Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	//loads background
	SDL_Surface* loadedImage = IMG_Load("../Images/menu/bg.jpg");
	bg = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	bgRect.x = 0;
	bgRect.y = 0;
	//loads the top menu
	loadedImage = IMG_Load("../Images/menu/menuTop.png");
	menuTop = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/menuTop1.png");
	menuTop1 = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/menuTop2.png");
	menuTop2 = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	loadedImage = IMG_Load("../Images/menu/menuTop3.png");
	menuTop3 = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	menuTopRect.x = 100;
	menuTopRect.y = 25;
	//loads status
	loadedImage = IMG_Load("../Images/menu/status1.png");
	status1 =  SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);
	status1Rect.x = 100;
	status1Rect.y = 210;
	if(player->getType() == 1){
		loadedImage = IMG_Load("../Images/menu/bgCollete.png");
		bgChar =  SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
		bgCharRect.x = 400;
		bgCharRect.y = 150;
	}
	else{
		loadedImage = IMG_Load("../Images/menu/bgLloyd.png");
		bgChar =  SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
		bgCharRect.x = 400;
		bgCharRect.y = 210;
	}

	//loads all message here
	SDL_Color black = {0,0,0}, yellow = {255,255,0};
	font =  TTF_OpenFont("../Fonts/Viner.ttf",40);	
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	string txt = "Status";
	statusTitle =  TTF_RenderText_Blended( font, txt.c_str(), black );
	statusTitleRect.x = 300;
	statusTitleRect.y = 150;

	currentChoice = MAIN;
	mainMenuChoice = 0;
	std::cout << "Finished Loading!" << std::endl;
}

void CharInfoScene::eventHandler(SDL_Event& event){

	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				scene->setGameScene(SceneManager::NORMAL);
				break;
			case SDLK_k:
				switch (currentChoice){
				case MAIN:
					if(mainMenuChoice == 0)
						currentChoice = STATUS;
					if(mainMenuChoice == 1)
						currentChoice = SKILLS;
					if(mainMenuChoice == 2)
						currentChoice = EQUIPS;
					if(mainMenuChoice == 3)
						currentChoice = OPTIONS;
					break;
				case STATUS:
					
					break;
				}
				break;

			case SDLK_RETURN:
				switch (currentChoice){
				case MAIN:
					if(mainMenuChoice == 0)
						currentChoice = STATUS;
					if(mainMenuChoice == 1)
						currentChoice = SKILLS;
					if(mainMenuChoice == 2)
						currentChoice = EQUIPS;
					if(mainMenuChoice == 3)
						currentChoice = OPTIONS;
					break;
				case STATUS:
					
					break;
				}
				break;
			case SDLK_x:
				switch (currentChoice){
				case MAIN:
					scene->setGameScene(SceneManager::NORMAL);
					break;
				case STATUS:
					currentChoice = MAIN;
					break;
				}
				break;
			case SDLK_LEFT:
				switch (currentChoice){
				case MAIN:
					mainMenuChoice--;
					if(mainMenuChoice <0)
						mainMenuChoice = 0;
					break;
				case STATUS:
					break;
				}
				break;

			case SDLK_RIGHT:
				switch (currentChoice){
				case MAIN:
					mainMenuChoice++;
					if(mainMenuChoice > 3)
						mainMenuChoice = 3;
					break;
				case STATUS:
					break;
				}
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


void CharInfoScene::display(){
	//	SDL_FillRect(scene->getScreen(),NULL,0x221122);
	SDL_BlitSurface( bg, NULL, scene->getScreen(), &bgRect);

	switch(mainMenuChoice){
	case 0:
		SDL_BlitSurface( menuTop, NULL, scene->getScreen(), &menuTopRect);
		break;
	case 1:
		SDL_BlitSurface( menuTop1, NULL, scene->getScreen(), &menuTopRect);
		break;
	case 2:
		SDL_BlitSurface( menuTop2, NULL, scene->getScreen(), &menuTopRect);
		break;
	case 3:
		SDL_BlitSurface( menuTop3, NULL, scene->getScreen(), &menuTopRect);
		break;
	default:
		break;
	}
	if(currentChoice == STATUS){
		SDL_BlitSurface( statusTitle, NULL, scene->getScreen(), &statusTitleRect);
		SDL_BlitSurface( bgChar, NULL, scene->getScreen(), &bgCharRect);
		SDL_BlitSurface( status1, NULL, scene->getScreen(), &status1Rect);

	}

	SDL_Flip(scene->getScreen());
}

void CharInfoScene::disposeResources(){

}