#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "Magic.h"

class Entity{
protected:
	struct status{
		int HP, MP, STR, CON, DEX, AGI, INT, LCK, PDEF, MDEF, ACU, MAXHP, MAXMP, CRIT, EVA, SPD;
	};
	status stats;
	//current level
	int level;
	int gold; //or whatever our currency is
	int	experience, maxExperience;
	std::vector<Magic> mAbilities;
	std::string Name;
	TTF_Font* font;
public:
	// need x and y coor vars for location of the image
	Entity();
	void setHP(int _HP);
	void setMP(int _MP);
	void setSTR(int _STR);
	void setDEF(int _DEF);
	void setSPD(int _SPD);
	void setDEX(int _DEX);
	void setINT(int _INT);
	void setLCK(int _LCK);
	void setMaxMP(int _MaxMP);
	void setStats(int _STR,int _CON, int _DEX,int _AGI, int _INT, int _LCK);
	virtual void setName(std::string _Name);
	std::string getName();
	int getHP();
	int getMP();
	int getSTR();
	int getDEF();
	int getSPD();
	int getINT();
	int getLCK();
	int getMaxHP();
	int getMaxMP();
	void forgetAllMagicAbilities(){mAbilities.clear();}
	void learnMagicAbility(Magic mSkill);
	std::vector<Magic> getMagicAbilities(){return mAbilities;}
	status getStats();
};
#endif
