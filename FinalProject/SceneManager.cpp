#include "SceneManager.h"

SceneManager::SceneManager(SDL_Surface* _screen,int* _gameOver){
	screen = _screen;
	gameOver = _gameOver;
	opening = new OpeningScene(gameOver, screen);
	normal = new NormalScene(gameOver, screen);
	battle = new BattleScene();
}

void SceneManager::eventHandler(SDL_Event& event,int& gameState){
	switch(gameState){
		case OPENINGMENU:
			opening->eventHandler(event, gameState);
			break;
		case NORMAL:
			normal->eventHandler(event, gameState);
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
		default:
			cerr << "ERROR" << endl;
			break;
	}	
}

