#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "../Scene/BattleScene.h"
#include "../Scene/OpeningScene.h"
#include "../Scene/NormalScene.h"
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
		void LoadOpeningScene();
		void loadNormalScene();
		void loadBattleScene();
		void loadNewCharScene();
};
#endif
