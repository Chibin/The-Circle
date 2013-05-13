#include "BattleAnimations.h"
///battleanimation
BattleAnimations::BattleAnimations(){
	idle = new Animation;
	idle->Init(6);
	idle->setImage("../Images/battle/LloydIdle.bmp",10,98,106);
}