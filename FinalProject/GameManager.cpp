#include <iostream>
#include "GameManager.h"
using namespace std;

GameManager::GameManager(){
	gameOver = 0;
	updateFrequency = 30;
	SDL_Init(SDL_INIT_VIDEO);	
	if(!SDL_SetVideoMode(800,600,0,0)){
		SDL_Quit();
		exit(-1);
	}
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
	
}

void GameManager::eventHandler(SDL_Event& event){
	Uint8* keystate =SDL_GetKeyState(NULL);
	if( keystate[SDLK_UP])
		cout << "UP" << endl;
	if( keystate[SDLK_DOWN])
		cout << "DOWN" << endl;
	if( keystate[SDLK_LEFT])
		cout << "LEFT" << endl;
	if( keystate[SDLK_RIGHT])
		cout << "RIGHT" << endl;

	//Runs through all the queued events
	//Note: we can create our own events
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_RETURN:
						cout << "STOP PRESSING ENTER" << endl;
						break;
					case SDLK_ESCAPE:
						gameOver = 1;
						SDL_Quit();
						break;
					default:
					break;
				}
				break;
			default:
				break;
		}
	}

}
