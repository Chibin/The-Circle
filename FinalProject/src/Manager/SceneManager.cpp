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
		switch(gameState){
		case GameManager::OPENINGMENU:
			LoadOpeningScene();
			break;
		case GameManager::NORMAL:
			loadNormalScene();
			break;
		case GameManager::BATTLE:
			loadBattleScene();
			break;
		case GameManager::CHARACTERCREATION:
			loadNewCharScene();
			break;
		default:
			cerr << "SCENE DOES NOT EXIST" << endl;
			break;
		}

		
	}
	currentScene->display(screen);

}

void SceneManager::LoadOpeningScene(){
	delete currentScene;
	currentScene = new OpeningScene(screen);
}
void SceneManager::loadNormalScene(){
	delete currentScene;
	currentScene = new NormalScene(screen);
}
void SceneManager::loadBattleScene(){	
	delete currentScene;
	currentScene = new BattleScene(screen);
}
void SceneManager::loadNewCharScene(){
	delete currentScene;
	currentScene = new NewCharScreen(screen);
}