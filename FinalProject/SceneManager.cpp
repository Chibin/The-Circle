#include "SceneManager.h"

SceneManager::SceneManager(SDL_Surface* _screen){
	screen = _screen;
	opening = new OpeningScene(screen);
	normal = new NormalScene(screen);
	battle = new BattleScene(screen);
}

void SceneManager::eventHandler(SDL_Event& event,int& gameState){
	switch(gameState){
		case OPENINGMENU:
			opening->eventHandler(event, gameState);
			break;
		case NORMAL:
			normal->eventHandler(event, gameState);
			break;
		case BATTLE:
			battle->eventHandler(event, gameState);
			break;
		default:
			cerr << "ERROR" << endl;
			break;
	}	
}

void SceneManager::sceneHandler(int gameState){
	switch(gameState){
		case OPENINGMENU:
			opening->display(screen);
			break;
		case NORMAL:
			normal->display(screen);
			break;
		case BATTLE:
			battle->display(screen);
			break;
		default:
			cerr << "ERROR" << endl;
			break;
	}
}

