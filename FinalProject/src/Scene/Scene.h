#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <queue>
using namespace std;
#include "../Manager/GameManager.h"
#include "../Entity//Player.h"
#include "../Manager/SceneManager.h"
#include "../Manager/LevelManager.h"
class Player;
class SceneManager;
class LevelManager;
class Scene{
	private:
		
	public:
		GameManager* game;
		SceneManager::GameScene type;
		Player* player;
		SceneManager* scene;
		LevelManager* level;
		//SDL_Surface* screen;
		Scene();
		SDL_Surface *load_imageWhite( std::string file );
		SDL_Surface *load_imageBlue( std::string file );
		void SetSurfaceAlpha(SDL_Surface *surface, Uint8 alpha);
		void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
		virtual void eventHandler(SDL_Event& event) = 0;
		virtual void display() = 0;
		// TODO: properly remove resource we dont need
		virtual void disposeResources() = 0;
};

class Animation  {
	int NumberOfFrames;
	int CurrentFrame;
	SDL_Rect* rectangles;
public:
	void Init( int number_of_frames );
	SDL_Rect* GetFrame(void);
	void SetFrame( int frame_number, int x, int y, int w, int h);
	void NextFrame(void);
	void LastFrame(void);
	friend class Scene;
};

class textAnimation{
	public:
		textAnimation();
		void drawNextFrame();
		bool isLastFrame();
	private:
		std::queue<SDL_Surface*> textList;
		SDL_Rect textPos;
		SDL_Rect textAnimator;

};


#endif