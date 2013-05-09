#include "SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/BattleScene.h"
#include "../Scene/OpeningScene.h"
#include "../Scene/NormalScene.h"
#include "../Scene/NewCharacterScene.h"
#include "../Scene/EventScene.h"

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
	SDL_EnableKeyRepeat(50 ,125);
	currentScene = new OpeningScene();
	gameScene = OPENINGMENU;
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

void SceneManager::sceneHandler(GameScene _gameScene){

	//check if we are changing gamestate.
	if(currentScene->type != _gameScene){
		//clear the old scene resource
		currentScene->disposeResources();
		std::cout << "Switching gameState from " << currentScene->type<< " to " << _gameScene << std::endl;
		delete currentScene;
		switch(_gameScene){
		case OPENINGMENU:
			currentScene = new OpeningScene();
			break;
		case NORMAL:
			currentScene = new NormalScene();
			break;
		case BATTLE:
			currentScene = new BattleScene();
			break;
		case CHARACTERCREATION:
			currentScene = new NewCharScreen();
			break;
		case EVENT:
			currentScene = new EventScene();
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

SceneManager::GameScene SceneManager::getGameScene(){
	return gameScene;
}
/*************************
Setters
**************************/
void SceneManager::setGameScene(SceneManager::GameScene _gameScene){
	gameScene = _gameScene;
}