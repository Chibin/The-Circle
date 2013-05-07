#ifndef MAGIC_H_
#define MAGIC_H_
class Magic{
	private:
	protected:
		enum magicType{DAMAGE,HEAL,BUFF,DEBUFF};
		enum targetType{SINGLE,AOE}; //area of effect: no credit to john
		SDL_Surface* magicTextImage;
		SDL_Rect magicLoc;
		enum magicType mType;
		enum targetType tType;
		int magicDamage;
	public:
		Magic();
		void setMagicType(enum magicType _mType){
			mType = _mType;
		}
		void setTargetType(enum targetType _tType){
			tType = _tType;
		}
		void setMagicDamage(int mDamage){
			magicDamage = mDamage;
		}
		int getMagicDamage(){
			return magicDamage;
		}
		void setTextLocation(Sint16 x, Sint16 y){
			magicLoc.x = x;
			magicLoc.y = y;
		}
		SDL_Surface* getMagicTextImage(){
			return magicTextImage;
		}
};

class FireBall: public Magic{
	public:
		FireBall(){
			setMagicType(DAMAGE);
			setTargetType(SINGLE);
			setMagicDamage(10);
		}
};
class AngelFeathers : public Magic{
	AngelFeathers(){
		setMagicType(DAMAGE);
		setTargetType(AOE);
		setMagicDamage(10);
	}
};
class PowHammer : public Magic{
	PowHammer(){
		setMagicType(DAMAGE);
		setTargetType(SINGLE);
		setMagicDamage(8);
	}
};
class Heal : public Magic{
};

class Item{
	private:
	public:

};
#endif
