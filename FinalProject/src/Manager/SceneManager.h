#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"

using namespace std;
class Player;
class Scene;
class SceneManager{
public:
	//Different Game Scene
	enum GameScene{NORMAL,MENU,BATTLE,OPENINGMENU, CHARACTERCREATION, EVENT, CHARINFO};
	//Instance of SceneManager
	static SceneManager& getInstance();	
	//handle the events
	void eventHandler(SDL_Event& event);
	//switch scene depends on demand
	void sceneHandler(GameScene );
	//Getters
	float getWindowHeight();
	float getWindowWidth();
	GameScene getGameScene();
	SDL_Surface* getScreen();
	SDL_Rect* getCamera();
	//Setters
	void setWindowSize(float, float);
	void setGameScene(GameScene );
	void updateCamera(float, float);
	void setCamera();
private:
	SDL_Surface* screen;	
	SDL_Rect camera;
	Scene* currentScene;
	Player* player;
	float winHeight, winWidth;
	SceneManager();
	GameScene gameScene;
	//disable copy constructors
	SceneManager(SceneManager const& copy);
	SceneManager& operator = (SceneManager const& copy);

};
#endif
