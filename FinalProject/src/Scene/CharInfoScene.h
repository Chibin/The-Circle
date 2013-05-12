#ifndef CHARINFOSCENE_H_
#define CHARINFISCENE_H_
#include "Scene.h"

class CharInfoScene : public Scene{

public:
	CharInfoScene();
	void eventHandler(SDL_Event& event);
	void display();
	void disposeResources();
};


#endif

