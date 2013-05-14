#include <iostream>
#include "GameManager.h"
#include "SceneManager.h"
#include "../Entity/Player.h"
#include <fstream>
using namespace std;

GameManager& GameManager::getInstance(){
	static GameManager instance;
	return instance;
}
GameManager::GameManager(){
	gameOver = false;
	didLoad = false;
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
	Player::getInstance().setPlayer(didLoad = true);
	sManager->setGameScene(SceneManager::BATTLE);
	std::cout << "\tLoading Level..." ;
	std::ifstream load( "game_save" );
	LevelManager::getInstance().loadMap("testLevel2");
	std::cout << "Done!" << std::endl;
	Player::getInstance().setPosition((int)SceneManager::getInstance().getWindowWidth()/2 - 12, (int)SceneManager::getInstance().getWindowHeight()/2 - 16);
	std::cout << "Loading Done!" << std::endl;
}
void GameManager::saveGame()
{
	std::cout << "Saving game..." << std::endl;
	std::ofstream save;
	save.open(( "game_save") );
	save << LevelManager::getInstance().getLevelName() << "\n";
	save << Player::getInstance().getPositionX() << "\n";
	save << Player::getInstance().getPositionY() << "\n";
	save << Player::getInstance().getType() << "\n";
	save << Player::getInstance().getLevel() << "\n";
	save << Player::getInstance().getXP() << "\n";
	save << Player::getInstance().getMaxXp() << "\n";
	save << Player::getInstance().getHP() << "\n";
	save << Player::getInstance().getMP() << "\n";
	save << Player::getInstance().getSTR() << "\n";
	save << Player::getInstance().getCON() << "\n";
	save << Player::getInstance().getDEX() << "\n";
	save << Player::getInstance().getAGI() << "\n";
	save << Player::getInstance().getINT() << "\n";
	save << Player::getInstance().getLCK() << "\n";
	save.close();
	//save current level
	//save character position
	//save character info
	//write into file
	std::cout << "Saving Done!" << std::endl;
}