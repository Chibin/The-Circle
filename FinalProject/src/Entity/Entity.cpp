#include "Entity.h"
Entity::Entity(){};
void Entity::setHP(int _HP){ stats.HP = _HP < 0 ? 0 : _HP >= stats.MAXHP? stats.MAXHP : _HP;}
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
	stats.MAXHP = (int)(_CON*1.5);
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
bool Entity::isUsedItemRemoved(int itemToUse){
	if(bag[itemToUse].getItemAmount() > 1){
		bag[itemToUse].setItemAmount(bag[itemToUse].getItemAmount() - 1);
		return false;
	}
	else{
		bag.erase(bag.begin()+itemToUse);
		return true;
	}
}
void Entity::storeItem(Item newItem){ 
	bool isThere = false;
	for(unsigned int i = 0; i < bag.size(); i++)
		if(bag[i].getItemName() == newItem.getItemName() && bag[i].getItemType() != Item::EQUIPMENT){
			bag[i].setItemAmount(bag[i].getItemAmount()+1);
			bag[i].freeAmountTextImage();
			bag[i].setItemAmountTextImage();
			isThere = true;
		}
	if(!isThere)
		bag.push_back(newItem);
}
Entity::status Entity::getStats(){return stats;}

	void Entity::setAnimation(BattleAnimations::animationState state, std::string path, int maxNumOfFrames, int r, int g, int b){
		if(state == BattleAnimations::IDLE){
			bAnim.setIdleImage(path,maxNumOfFrames,r,g,b);
		}
	}
	SDL_Surface* Entity::getImage(BattleAnimations::animationState state){
		if(state == BattleAnimations::IDLE)
			return bAnim.getIdleImage();
		return NULL;
	}
	BattleAnimations& Entity::getBattleAnimations(){ return bAnim;}