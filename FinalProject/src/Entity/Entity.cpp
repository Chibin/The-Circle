#include "Entity.h"
Entity::Entity(){};
void Entity::setHP(int _HP){ stats.HP = _HP >= stats.MAXHP? stats.MAXHP : _HP;}
void Entity::setMP(int _MP){stats.MP = _MP;}
void Entity::setSTR(int _STR){ stats.STR = _STR;}
void Entity::setDEF(int _DEF){ stats.PDEF = _DEF;}
void Entity::setSPD(int _SPD){ stats.SPD = _SPD;}
void Entity::setINT(int _INT){ stats.INT = _INT;}
void Entity::setMaxMP(int _MaxMP){ stats.MAXMP = _MaxMP; stats.MP += _MaxMP;}
void Entity::setStats(int _STR,int _CON, int _DEX,int _AGI, int _INT, int _LCK){
	stats.STR = _STR;
	stats.DEX = _DEX;
	stats.INT = _INT;
	stats.MAXHP = _CON*1.5;
	stats.HP = stats.MAXHP;
	stats.MAXMP = _INT*15;
	stats.MP = stats.MAXMP;
	stats.PDEF = (int)(_STR*1.1);
	stats.SPD = (int)(_DEX*1.5);
	stats.LCK = _LCK;
}
void Entity::setName(std::string _Name){Name = _Name;}
std::string Entity::getName(){return Name;}
int Entity::getHP(){return stats.HP;}
int Entity::getMP(){return stats.MP;}
int Entity::getSTR(){return stats.STR;}
int Entity::getDEF(){return stats.PDEF;}
int Entity::getSPD(){return stats.SPD;}
int Entity::getINT(){return stats.INT;}
int Entity::getMaxHP(){return stats.MAXHP;}
int Entity::getMaxMP(){return stats.MAXMP;}
void Entity::learnMagicAbility(Magic mSkill){mAbilities.push_back(mSkill);}
Entity::status Entity::getStats(){return stats;}