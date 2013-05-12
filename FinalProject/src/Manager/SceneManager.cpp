#include "SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/BattleScene.h"
#include "../Scene/OpeningScene.h"
#include "../Scene/NormalScene.h"
#include "../Scene/NewCharacterScene.h"
#include "../Scene/EventScene.h"
#include "../Scene/CharInfoScene.h"
#include "../Manager/LevelManager.h"
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
	SDL_ShowCursor(SDL_DISABLE);  
	SDL_EnableKeyRepeat(50 ,125);
	currentScene = new OpeningScene();
	player = &Player::getInstance();
	gameScene = OPENINGMENU;
	camera.h = (Uint16)winHeight;
	camera.w = (Uint16)winWidth;
	camera.x = 0;
	camera.y = 0;
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
		case CHARINFO:
			currentScene = new CharInfoScene();
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

SDL_Rect* SceneManager::getCamera(){
	return &camera;
}

/*************************
Setters
**************************/
void SceneManager::setGameScene(SceneManager::GameScene _gameScene){
	gameScene = _gameScene;
}
void SceneManager::updateCamera(float x, float y){
	camera.x += (Sint16)x;
	camera.y += (Sint16)y;
}
void SceneManager::setCamera(){
	camera.x = (Sint16) ((player->getMapOffsetX() + 8) - winWidth/2);
	camera.y = (Sint16) ((player->getMapOffsetY() + 16) - winHeight/2);

	if( camera.x < 0 )
	{
		camera.x = 0;    
	}
	if( camera.y < 0 )
	{
		camera.y = 0;    
	}
	if( camera.x > LevelManager::getInstance().getWidth() - camera.w )
    {
        camera.x = LevelManager::getInstance().getWidth() - camera.w;    
    }
    if( camera.y > LevelManager::getInstance().getHeight() - camera.h )
    {
        camera.y = LevelManager::getInstance().getHeight() - camera.h;    
    }    

}