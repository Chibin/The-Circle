#include "Entity.h"


Entity::Entity(){};
void Entity::setHP(int _HP){ stats.HP = _HP;}
void Entity::setMP(int _MP){stats.MP = _MP;}
void Entity::setSTR(int _STR){ stats.STR = _STR;}
void Entity::setDEF(int _DEF){ stats.DEF = _DEF;}
void Entity::setSPD(int _SPD){ stats.SPD = _SPD;}
void Entity::setINT(int _INT){ stats.INT = _INT;}
void Entity::setStats(int _STR,int _DEX,int _INT){
	stats.STR = _STR;
	stats.DEX = _DEX;
	stats.INT = _INT;
	stats.HP = _STR*10;
	stats.MP = _INT*15;
	stats.DEF = _STR*1.1;
	stats.SPD = _DEX*1.5;
}
void Entity::setName(std::string _Name){Name = _Name;}
std::string Entity::getName(){return Name;}
int Entity::getHP(){return stats.HP;}
int Entity::getMP(){return stats.MP;}
int Entity::getSTR(){return stats.STR;}
int Entity::getDEF(){return stats.DEF;}
int Entity::getSPD(){return stats.SPD;}
int Entity::getINT(){return stats.INT;}
Entity::status Entity::getStats(){return stats;}

