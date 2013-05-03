#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;
#include "GameManager.h"
class Scene{
	private:
		GameManager instance;
	public:
		SDL_Surface* screen;
		Scene(){ instance = GameManager::getInstance();}
		virtual void eventHandler(SDL_Event& event) = 0;
		virtual void display(SDL_Surface* screen) = 0;
};
#endif
