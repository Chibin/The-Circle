#include "CharInfoScene.h"

CharInfoScene::CharInfoScene(){
	type = SceneManager::CHARINFO;
	std::cout << "Entering CharInfo Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;
	SDL_Surface* loadedImage = IMG_Load("../Images/menu/bg.bmp");
	bg = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface(loadedImage);

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
	bgRect.x = 0;
	bgRect.y = 0;
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
			case SDLK_RETURN:

				break;
			case SDLK_LEFT:
				switch (currentChoice){
				case MAIN:
					break;
				case ITEMS:

				}
				break;

			case SDLK_RIGHT:
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
	SDL_BlitSurface( menuTop, NULL, scene->getScreen(), &menuTopRect);
	SDL_Flip(scene->getScreen());
}

void CharInfoScene::disposeResources(){

}