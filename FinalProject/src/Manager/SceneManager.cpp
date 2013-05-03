#include "SceneManager.h"

SceneManager::SceneManager(SDL_Surface* _screen){
	screen = _screen;
	opening = new OpeningScene(screen);
	normal = new NormalScene(screen);
	battle = new BattleScene(screen);
}

void SceneManager::eventHandler(SDL_Event& event){
	switch(GameManager::getInstance().getGameState()){
	case GameManager::OPENINGMENU:
		opening->eventHandler(event);
		break;
	case GameManager::NORMAL:
		normal->eventHandler(event);
		break;
	case GameManager::BATTLE:
		battle->eventHandler(event);
		break;
	default:
		cerr << "ERROR" << endl;
		break;
	}	
}

void SceneManager::sceneHandler(GameManager::GameState gameState){
	switch(gameState){
	case GameManager::OPENINGMENU:
		opening->display(screen);
		break;
	case GameManager::NORMAL:
		normal->display(screen);
		break;
	case GameManager::BATTLE:
		battle->display(screen);
		break;
	default:
		cerr << "ERROR" << endl;
		break;
	}
}

