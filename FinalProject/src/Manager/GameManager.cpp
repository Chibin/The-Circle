#include <iostream>
#include "GameManager.h"
#include "SceneManager.h"
using namespace std;

GameManager& GameManager::getInstance(){
	static GameManager instance;
	return instance;
}
GameManager::GameManager(){
	gameOver = false;
	didLoad = false;
	SDL_EnableKeyRepeat(70, 70);
	updateFrequency = 30;
	//we want to intialize all the manager here
	sManager = &SceneManager::getInstance();
	
}


//Game loop: stuff that runs the whole game.
void GameManager::GameLoop(){
	int timeLast = 0, timeCurrent = 0, timeDelta = 0, timeAccumulated = 0;
	int timeStep = (int)(1000.0f/updateFrequency); //30 FPS
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
	//All the calculations are in milliseconds
	while(!gameOver){
		//add frame limiter here
		timeLast = timeCurrent;
		timeCurrent = SDL_GetTicks();
		timeDelta = timeCurrent - timeLast;
		timeAccumulated += timeDelta;
		while(timeAccumulated >= timeStep){ //Process events only if it's within the 30 FPS
			eventHandler(events);
			timeAccumulated -= timeStep;
		}
		sManager->sceneHandler(sManager->getGameScene());
	}
}

void GameManager::eventHandler(SDL_Event& event){
	//handles the close event if user click X on top right
	if(event.type==SDL_QUIT)
		setGameOver(true);
	sManager->eventHandler(event);

}

/*************************
Getters
**************************/

bool GameManager::isLoaded(){
	return didLoad;
}

/*************************
Setters
**************************/
void GameManager::setGameOver(bool state){
	gameOver = state;
}



/*************************
Save and Load game
**************************/
void GameManager::loadGame()
{
	std::cout << "Loading game..." << std::endl;
	didLoad = true;
	sManager->setGameScene(SceneManager::BATTLE);

	std::cout << "Loading Done!" << std::endl;
}
void GameManager::saveGame()
{
	std::cout << "Saving game..." << std::endl;
	//save current level
	//save character position
	//save character info
	//write into file
	std::cout << "Saving Done!" << std::endl;
}