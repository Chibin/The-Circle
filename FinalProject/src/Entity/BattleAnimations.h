#ifndef BATTLEANIMATION_H_
#define BATTLEANIMATION_H_
#include <string>
#include <SDL.h>
class Animation;
class BattleAnimations{
public:
	enum animationState{IDLE,ATTACK};
protected:
	int timeStep;
	SDL_Rect position;
	int animationCounter;
	Animation *idle;
	Animation *attack;
public:
	BattleAnimations();
	SDL_Surface* getIdleImage();
	void drawFrameUpdate(int timeLapsed);
	void BattleAnimations::setIdleImage(std::string path,int maxNumFrames, int r, int g, int b);
	void setFrame(BattleAnimations::animationState state,  int frame_number, int x, int y, int w, int h);
	void drawAnimation(BattleAnimations::animationState state,SDL_Surface* screen, int timeStep);
	void setAnimationPosition(int x, int y);
};
#endif