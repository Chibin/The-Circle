#include <iostream>
#include "GameManager.h"
#include "SceneManager.h"
using namespace std;

GameManager& GameManager::getInstance(){
	static GameManager instance;
	return instance;
}
GameManager::GameManager(){
	gameOver = false;
	gameState = OPENINGMENU;
	updateFrequency = 30;
	winHeight = 600;
	winWidth = 800;

	//TTF_Init();
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);	
	if(!(screen = SDL_SetVideoMode((int)winWidth,(int)winHeight,32,SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT))){
		SDL_Quit();
		exit(-1);
	}
	SDL_WM_SetCaption( "Tales of Breakers - Pre-alpha v.01a", NULL );

	sManager = new SceneManager(screen);
}


//Game loop: stuff that runs the whole game.
void GameManager::GameLoop(){
	int timeLast = 0, timeCurrent = 0, timeDelta = 0, timeAccumulated = 0;
	int timeStep = (int)(1000.0f/updateFrequency); //30 FPS
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
	//handles the close event if user click X on top right
	if(event.type==SDL_QUIT)
		setGameOver(true);
	sManager->eventHandler(event);

}

/*************************
Getters
**************************/
float GameManager::getWindowHeight(){
	return winHeight;
}

float GameManager::getWindowWidth(){
	return winWidth;
}

GameManager::GameState GameManager::getGameState(){
	return gameState;
}
/*************************
Setters
**************************/
void GameManager::setGameOver(bool state){
	gameOver = state;
}

void GameManager::setGameState(GameState state){
	gameState = state;
}

SDL_Surface* GameManager::load_image( std::string file )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( file.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}
