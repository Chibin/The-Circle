#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include <iostream>
#include <SDL.h>
#include "OpeningScene.h"
#include "NormalScene.h"
#include "BattleScene.h"
#include "GameManager.h"
using namespace std;


class SceneManager{
	private:
		SDL_Surface* screen;
		OpeningScene* opening;
		NormalScene* normal;
		BattleScene* battle;
	public:
		//enum gameState{NORMAL,MENU,BATTLE,OPENINGMENU};
		SceneManager(SDL_Surface* _screen);			
		void eventHandler(SDL_Event& event);
		void sceneHandler(GameManager::GameState gameState);
};
#endif
