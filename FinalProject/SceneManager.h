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
		int* gameOver;
		SDL_Surface* screen;
		OpeningScene* opening;
		NormalScene* normal;
		BattleScene* battle;
	public:
		enum gameState{NORMAL,MENU,BATTLE,OPENINGMENU};
		SceneManager(SDL_Surface* _screen,int* _gameOver);			
		void eventHandler(SDL_Event& event,int& gameState);
		void sceneHandler(int gameState);
};
#endif
