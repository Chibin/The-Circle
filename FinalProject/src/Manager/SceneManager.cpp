#include "SceneManager.h"
#include "../Scene/BattleScene.h"
#include "../Scene/OpeningScene.h"
#include "../Scene/NormalScene.h"
#include "../Scene/NewCharacterScene.h"


SceneManager::SceneManager(SDL_Surface* _screen){
	screen = _screen;
	currentScene = new OpeningScene(screen);
}


void SceneManager::eventHandler(SDL_Event& event){
	currentScene->eventHandler(event);
}

void SceneManager::sceneHandler(GameManager::GameState gameState){

	//check if we are changing gamestate.
	if(currentScene->type != gameState){
		//clear the old scene resource
		currentScene->disposeResources();
		std::cout << "Switching gameState from " << currentScene->type<< " to " << gameState << std::endl;
		delete currentScene;
		switch(gameState){
		case GameManager::OPENINGMENU:
			currentScene = new OpeningScene(screen);
			break;
		case GameManager::NORMAL:
			currentScene = new NormalScene(screen);
			break;
		case GameManager::BATTLE:
			currentScene = new BattleScene(screen);
			break;
		case GameManager::CHARACTERCREATION:
			currentScene = new NewCharScreen(screen);
			break;
		default:
			cerr << "SCENE DOES NOT EXIST" << endl;
			break;
		}	
	}
	currentScene->display(screen);

}
