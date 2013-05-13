#ifndef BATTLEANIMATION_H_
#define BATTLEANIMATION_H_

class Animation;
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