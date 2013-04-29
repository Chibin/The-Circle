#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <SDL.h>

using namespace std;
class Scene{
	private:
	public:
		SDL_Surface* screen;
		int* gameOver;
		enum gameState{NORMAL,MENU,BATTLE,OPENINGMENU};
		Scene(){}
		virtual void eventHandler(SDL_Event& event, int& gameState) = 0;
		virtual void display(SDL_Surface* screen) = 0;
};
#endif
