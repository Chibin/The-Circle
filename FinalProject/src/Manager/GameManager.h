#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
#include <SDL.h>
#include <fstream>
class SceneManager;
class GameManager{
public:	
	//functions
	static GameManager& getInstance();
	void GameLoop();
	void GameDisplay();
	void eventHandler(SDL_Event& event);
	//setters
	void setGameOver(bool);
	void saveGame();
	void loadGame();
	//getters
	bool isLoaded();



private:
	bool gameOver, didLoad;
	int updateFrequency;
	//float winHeight, winWidth;
	SDL_Event events;
	//SDL_Surface* screen;
	SceneManager* sManager;
	GameManager();
	//disable copy constructors
	GameManager(GameManager const& copy);
	GameManager& operator = (GameManager const& copy);

};
#endif
