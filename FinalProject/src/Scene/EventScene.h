#ifndef EVENT_SCENE_H_
#define EVENT_SCENE_H_
#include "Scene.h"

class EventScene : public Scene{
private:
	SDL_Surface *bg, *portait, *sideRight, *sideLeft, *textbg;
	SDL_Rect bgRect, portaitRect, bgRectSrc, portaitRectSrc, sideRect, textbgRect;

public:
	EventScene();
	void eventHandler(SDL_Event& event);
	void display();
	void disposeResources();
};





#endif