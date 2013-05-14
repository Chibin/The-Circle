#ifndef MOB_H
#define MOB_H
#include "Entity.h"

class Mob: public Entity{
private:
		SDL_Rect enemyLoc;
		SDL_Surface* enemyText[2], enemyImage;
protected:
		int maxFrame;
public:
	Mob();
	void setName(std::string);
	int getMaxFrame(){return maxFrame;}
	SDL_Surface** getEnemyText();
	~Mob();

};

class Arachnia : public Mob{
public:
		virtual void drawAnimation(BattleAnimations::animationState state, SDL_Surface* screen, int _timeStep){
		bAnim.drawAnim(state,screen,_timeStep,1);
	}
	Arachnia(){
		maxFrame = 4;
		setName("Arachnia");
		setAnimation(BattleAnimations::IDLE,"../Images/battle/ArachniaIdle.bmp",4,255,255,255);
		for(int i = 3; i > -1; i--)
			getBattleAnimations().setFrame(BattleAnimations::IDLE,3-i,59*i,0,59,getBattleAnimations().getIdleImage()->h);
	}
};
class Bat : public Mob{
	public:
	void drawAnimation(BattleAnimations::animationState state, SDL_Surface* screen, int _timeStep){
		bAnim.drawAnim(state,screen,_timeStep,2);
	}
	Bat(){
		maxFrame = 4;
		setName("Bat");
		setAnimation(BattleAnimations::IDLE,"../Images/battle/BatIdle.bmp",maxFrame,255,255,255);
		for(int i = 3; i > -1; i--)
			getBattleAnimations().setFrame(BattleAnimations::IDLE,maxFrame-1-i,36*i,0,36,getBattleAnimations().getIdleImage()->h);
	}
};
#endif