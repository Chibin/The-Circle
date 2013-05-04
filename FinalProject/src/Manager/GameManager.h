#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
#include <SDL.h>
//#include "SceneManager.h"
class SceneManager;
class GameManager{
public:
	//variables
	enum GameState{NORMAL,MENU,BATTLE,OPENINGMENU, CHARACTERCREATION};
	//functions
	static GameManager& getInstance();
	void GameLoop();
	void GameDisplay();
	void eventHandler(SDL_Event& event);
	//setters
	void setWindowSize(float, float);
	void setGameOver(bool);
	void setGameState(GameState);
	//getters
	float getWindowHeight();
	float getWindowWidth();
	GameState getGameState();


private:
	bool gameOver;
	int updateFrequency;
	GameState gameState;
	float winHeight, winWidth;
	SDL_Event events;
	SDL_Surface* screen;
	SceneManager* sManager;
	GameManager();
	//disable copy constructors
	GameManager(GameManager const& copy);
	GameManager& operator = (GameManager const& copy);

};
#endif
