#ifndef BATTLEANIMATION_H_
#define BATTLEANIMATION_H_
#include "../Scene/Scene.h"
class BattleAnimations{
public:
	enum animationState{IDLE,ATTACK};
protected:
	Animation *idle;
	Animation *attack;
public:
	BattleAnimations();
	void drawFrameUpdate(int timeLapsed);
};
#endif