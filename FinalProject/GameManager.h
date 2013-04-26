#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
#include <SDL.h>
class GameManager{
	private:

	public:
		GameManager();
		void GameLoop();
		void GameDisplay();
		int onExecute();
};
#endif
