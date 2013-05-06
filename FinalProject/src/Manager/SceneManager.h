#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"
#include "../Scene/Scene.h"
using namespace std;


class SceneManager{
	private:
		SDL_Surface* screen;	
		Scene* currentScene;

	public:
		SceneManager(SDL_Surface* _screen);			
		void eventHandler(SDL_Event& event);
		void sceneHandler(GameManager::GameState gameState);

};
#endif
