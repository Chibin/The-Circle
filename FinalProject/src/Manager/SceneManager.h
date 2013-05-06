#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"
using namespace std;

class Scene;
class SceneManager{
private:
	SDL_Surface* screen;	
	Scene* currentScene;
	float winHeight, winWidth;
	SceneManager();
	//static SceneManager instance;
	//disable copy constructors
	SceneManager(SceneManager const& copy);
	SceneManager& operator = (SceneManager const& copy);
public:
	static SceneManager& getInstance();	
	void eventHandler(SDL_Event& event);
	void sceneHandler(GameManager::GameState gameState);
	float getWindowHeight();
	float getWindowWidth();
	void setWindowSize(float, float);
	SDL_Surface* getScreen();
};
#endif
