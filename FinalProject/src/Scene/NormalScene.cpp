#include "NormalScene.h"
#include "../Manager/GameManager.h"
NormalScene::NormalScene(){
	type = GameManager::NORMAL;
		std::cout << "Entering Normal Screen..." << std::endl;
		std::cout << "Loading Resources..." << std::endl;
		std::cout << "\tLoading Level " ;
		if(game->isLoaded()){
			std::cout << "from a save." << std::endl;;
		}
		else{

		}
		std::cout << "\tLoading Character..." ;
		//if()	
		std::cout << "Done!" << std::endl;;
		std::cout << "Finished Loading!" << std::endl << std::endl;
}
void NormalScene::eventHandler(SDL_Event& event){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP]){
		cout << "UP" << endl;
	}
	if( keystate[SDLK_DOWN]){
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

}
void NormalScene::display(){
	SDL_FillRect(scene->getScreen(),NULL,0x221122);
	SDL_Flip(scene->getScreen());
}
void NormalScene::disposeResources(){
}