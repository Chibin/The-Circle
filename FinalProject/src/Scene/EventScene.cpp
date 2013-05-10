#include "EventScene.h"
EventScene::EventScene(){
	type = SceneManager::EVENT;
	std::cout << "Entering Event Scene" << std::endl;
	std::cout << "Loading Event Resources..." << std::endl; 
	SDL_Surface *temp;
	temp = IMG_Load("../Images/event/bg.png");
	bg = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	temp = IMG_Load("../Images/event/face.bmp");
	portait = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	sideRight = load_imageWhite("../Images/event/male.png");
	sideLeft = load_imageWhite("../Images/event/actor.png");
	sideRect.x = 0;
	sideRect.y = 100;
	bgRectSrc.x = 0;
	bgRectSrc.y = 0;
	bgRectSrc.h = bg->h;
	bgRectSrc.w = bg->w;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 600;
	bgRect.h = 450;

	portaitRectSrc.x = 0;
	portaitRectSrc.y = 0;
	portaitRectSrc.h = portait->h;
	portaitRectSrc.w = portait->w;
	portaitRect.x = 400-75;
	portaitRect.y = 300-150;
	portaitRect.w = 150;
	portaitRect.h = 150;
	SDL_Surface* loadedImage = IMG_Load("../Images/event/bgtext.png");
	textbg = SDL_DisplayFormatAlpha(loadedImage);
	SDL_FreeSurface( loadedImage );
	textbgRect.x = 0;
	textbgRect.y = 400;	
	printf("Resources loaded!\n");
}

void EventScene::eventHandler(SDL_Event& event){
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
			case SDLK_z:
				scene->setGameScene(SceneManager::NORMAL);
				break;
			case SDLK_ESCAPE:
				scene->setGameScene(SceneManager::NORMAL);
				//game->setGameOver(true);
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

void EventScene::display(){

	//SDL_FillRect(scene->getScreen(),&temp,0x221122);
	//SDL_BlitSurface(bg, &bgRectSrc, scene->getScreen(),&bgRect);
		SDL_BlitSurface(sideRight,NULL,scene->getScreen(),&sideRect );
	SDL_BlitSurface(textbg,NULL, scene->getScreen(), &textbgRect);
	//	SDL_BlitSurface(sideRight,NULL,scene->getScreen(),&sideRect );
//	SDL_BlitSurface(portait, &portaitRectSrc, scene->getScreen(),&portaitRect);
	SDL_Flip(scene->getScreen());
}

void EventScene::disposeResources(){
	std::cout << "Cleaning Event Scene" << std::endl;
	SDL_FreeSurface(bg);
	SDL_FreeSurface(portait);
	std::cout << "Cleaning Finished!" << std::endl << std::endl;
}