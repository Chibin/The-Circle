#include "NormalScene.h"
#include "../Manager/GameManager.h"
NormalScene::NormalScene(SDL_Surface* _screen){
	screen = _screen;
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
void NormalScene::display(SDL_Surface* screen){
	SDL_FillRect(screen,NULL,0x221122);
	SDL_Flip(screen);
}
void NormalScene::disposeResources(){
}