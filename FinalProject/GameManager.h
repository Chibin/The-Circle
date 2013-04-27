#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
#include <SDL.h>
class GameManager{
	private:
		int gameOver;
		int updateFrequency;
	   	int gameState;
		SDL_Event events;

	public:
		//variables
		enum gameState{NORMAL,MENU,BATTLE};
		//functions
		GameManager();
		void GameLoop();
		void GameDisplay();
		void eventHandler(SDL_Event& event);
};
#endif
