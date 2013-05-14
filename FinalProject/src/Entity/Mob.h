#ifndef MOB_H
#define MOB_H
#include "Entity.h"

class Mob: public Entity{
private:
		SDL_Rect enemyLoc;
		SDL_Surface* enemyText[2], enemyImage;
public:
	Mob();
	void setName(std::string);
	SDL_Surface** getEnemyText();
	~Mob();
};

class Arachnia : public Mob{
public:
	Arachnia(){
		setName("Arachnia");
		setAnimation(BattleAnimations::IDLE,"../Images/battle/ArachniaIdle.bmp",4,255,255,255);
		for(int i = 3; i > -1; i--)
			getBattleAnimations().setFrame(BattleAnimations::IDLE,3-i,59*i,0,59,getBattleAnimations().getIdleImage()->h);
	}
};
#endif