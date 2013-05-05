#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
using namespace std;
#include "../Manager/GameManager.h"
class Scene{
	private:
		
	public:
		GameManager* game;
		GameManager::GameState type;
		SDL_Surface* screen;
		Scene();
		SDL_Surface *load_image( std::string file );
		void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
		virtual void eventHandler(SDL_Event& event) = 0;
		virtual void display(SDL_Surface* screen) = 0;
		//TODO: properly remove resource we dont need
		virtual void disposeResources() = 0;
};
#endif
