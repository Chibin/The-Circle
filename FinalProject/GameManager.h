#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
#include <SDL.h>
//#include "SceneManager.h"
class SceneManager;
class GameManager{
	private:
		int gameOver;
		int updateFrequency;
	   	int gameState;
		float winHeight, winWidth;
		SDL_Event events;
		SDL_Surface* screen;
		SceneManager* sManager;
	public:
		//variables
		static GameManager singleton;
		enum gameState{NORMAL,MENU,BATTLE,OPENINGMENU};
		//functions
		GameManager();
		void GameLoop();
		void GameDisplay();
		void eventHandler(SDL_Event& event);
		float getWindowHeight();
		float getWindowWidth();
		};
#endif
