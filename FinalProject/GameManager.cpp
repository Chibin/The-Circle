#include <iostream>
#include "GameManager.h"
using namespace std;

GameManager::GameManager(){
	winHeight = 600;
	winWidth = 800;
	gameOver = 0;
	gameState = OPENINGMENU;
	updateFrequency = 30;
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO);	
	if(!(screen = SDL_SetVideoMode(winWidth,winHeight,32,SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT))){
		SDL_Quit();
		exit(-1);
	}
	sManager = new SceneManager(screen,&gameOver);
}

//Game loop: stuff that runs the whole game.
void GameManager::GameLoop(){
	int timeLast = 0, timeCurrent = 0, timeDelta = 0, timeAccumulated = 0;
	int timeStep = 1000.0f/updateFrequency; //30 FPS
	//SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
	//All the calculations are in milliseconds
	while(!gameOver){
		//add frame limiter here
		timeLast = timeCurrent;
		timeCurrent = SDL_GetTicks();
		timeDelta = timeCurrent - timeLast;
		timeAccumulated += timeDelta;
		while(timeAccumulated >= timeStep){ //Process events only if it's within the 30 FPS
			eventHandler(events);
			timeAccumulated -= timeStep;
		}
		GameDisplay();
	}
}

//will handle all the drawing
void GameManager::GameDisplay(){
	sManager->sceneHandler(gameState);
}

void GameManager::eventHandler(SDL_Event& event){
	sManager->eventHandler(event,gameState);
}
