#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
#include <SDL.h>
//#include "SceneManager.h"
class SceneManager;
class GameManager{
	private:
		bool gameOver;
		int updateFrequency;
	   	int gameState;
		float winHeight, winWidth;
		SDL_Event events;
		SDL_Surface* screen;
		SceneManager* sManager;
		GameManager();
		//disable copy constructors
		GameManager(GameManager const& copy);
		GameManager& operator = (GameManager const& copy);
	public:
		//variables
		enum gameState{NORMAL,MENU,BATTLE,OPENINGMENU};
		//functions
		static GameManager& getInstance();
		void GameLoop();
		void GameDisplay();
		void eventHandler(SDL_Event& event);
		float getWindowHeight();
		float getWindowWidth();
		void setGameOver(int);
		};
#endif
