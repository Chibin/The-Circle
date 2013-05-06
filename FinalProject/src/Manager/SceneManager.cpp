#include "SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/BattleScene.h"
#include "../Scene/OpeningScene.h"
#include "../Scene/NormalScene.h"
#include "../Scene/NewCharacterScene.h"

SceneManager::SceneManager(){
	winHeight = 600;
	winWidth = 800;
	//TTF_Init();
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);	
	if(!(screen = SDL_SetVideoMode((int)winWidth,(int)winHeight,32,SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT))){
		SDL_Quit();
		exit(-1);
	}
	SDL_WM_SetCaption( "Tales of Breakers - Pre-alpha v.01a", NULL );
	currentScene = new OpeningScene();
}
SceneManager& SceneManager::getInstance(){
	static SceneManager instance;
	return instance;
}

void SceneManager::eventHandler(SDL_Event& event){
	if (currentScene !=0)
		currentScene->eventHandler(event);
	else
		std::cout << "There are no scene to process the event" << std::endl;
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
			currentScene = new OpeningScene();
			break;
		case GameManager::NORMAL:
			currentScene = new NormalScene();
			break;
		case GameManager::BATTLE:
			currentScene = new BattleScene();
			break;
		case GameManager::CHARACTERCREATION:
			currentScene = new NewCharScreen();
			break;
		default:
			cerr << "SCENE DOES NOT EXIST" << endl;
			break;
		}	
	}
	currentScene->display();

}

/*************************
Getters
**************************/
float SceneManager::getWindowHeight(){
	return winHeight;
}

float SceneManager::getWindowWidth(){
	return winWidth;
}

SDL_Surface* SceneManager::getScreen(){
	return screen;
}