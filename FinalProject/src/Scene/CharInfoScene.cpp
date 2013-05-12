#include "CharInfoScene.h"

CharInfoScene::CharInfoScene(){
	type = SceneManager::CHARINFO;
	std::cout << "Entering CharInfo Screen..." << std::endl;
	std::cout << "Loading Resources..." << std::endl;

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
	printf("Press esc to go back to normal scene! going to quit or go to main screen? it will be handled here!\n");
}

void CharInfoScene::disposeResources(){

}