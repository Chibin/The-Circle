#ifndef ITEM_H_
#define ITEM_H_
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>    
class Item{
			public:
		enum itemActiveType{BATTLE,NORMAL,BATTLE_NORMAL,NOTACTIVE};
		enum itemType{USABLE,EQUIPMENT,ETC};
		enum itemEffect{HEAL,DAMAGE,BUFF,DEBUFF,NOEFFECT};
		enum itemTargetType{SINGLE,AOE};
		protected:
	std::string ItemName;
	std::string ItemDescription;
	itemType type;
	itemActiveType active;
	itemEffect effect;
	itemTargetType tType;
	SDL_Surface *ItemTextImage[2], *ItemAmountTextImage[2];
	int amount;
	int healAmount, damageAmount;
	public:
		Item(){}
		void setItemAmount(int _amount){ amount = _amount;}
		void setItemName(std::string _Name){	ItemName = _Name;}
		void setItemDesc(std::string desc){ ItemDescription = desc;}
		void setItemActive(itemActiveType _active){	active = _active;	}
		void setItemEffect(itemEffect _effect){effect = _effect;	}
		void setItemType(itemType _type){	type = _type;}
		void setHealAmount(int heal){ healAmount = heal;}
		void setItemTargetType(itemTargetType _tType){ tType = _tType;}
		int getHealAmount(){ return healAmount;}
		int getItemAmount(){ return amount;}
		itemType getItemType(){return type;}
		itemActiveType getItemActive(){return active;}
		itemEffect getItemEffect(){return effect;}
		itemTargetType getItemTargetType(){return tType;}
		std::string getItemName(){return ItemName;}
		std::string getItemDesc(){ return ItemDescription;}
		bool isItemUsable(){ return type == USABLE;}
		bool isItemHeal(){return effect == HEAL;}
		bool isItemDamage(){return effect == DAMAGE;}
		void freeAmountTextImage(){
			SDL_FreeSurface(ItemAmountTextImage[0]);
			SDL_FreeSurface(ItemAmountTextImage[1]);
		}
		void setItemAmountTextImage(){
			TTF_Font* font;
			font = TTF_OpenFont("../Fonts/coolvetica.ttf",35); //used to be 30 for manga temple
			SDL_Color fgColor = {255,255,0};
			std::ostringstream oss;
			oss << amount;
			ItemAmountTextImage[0] =TTF_RenderText_Blended(font,oss.str().c_str(),fgColor);
			fgColor.b = 255;
			ItemAmountTextImage[1] =TTF_RenderText_Blended(font,oss.str().c_str(),fgColor); 
			TTF_CloseFont(font);
		}
		void setItemTextImage(){
			TTF_Font* font;
			font = TTF_OpenFont("../Fonts/coolvetica.ttf",35); //used to be 30 for manga temple
			SDL_Color fgColor = {255,255,0};
			ItemTextImage[0] =TTF_RenderText_Blended(font,ItemName.c_str(),fgColor);
			fgColor.b = 255;
			ItemTextImage[1] =TTF_RenderText_Blended(font,ItemName.c_str(),fgColor); 
			TTF_CloseFont(font);
		}
		SDL_Surface** getItemTextImage(){ return ItemTextImage; }
		SDL_Surface** getItemAmountTextImage(){return ItemAmountTextImage;}

};
class HealingItem : public Item{
public:
	HealingItem(){
		setItemActive(BATTLE_NORMAL);
		setItemEffect(HEAL);
		setItemType(USABLE);
	}
};
class Herb : public HealingItem{
public:
	Herb() : HealingItem(){
		setItemDesc("Recovers 15 Health Points.");
		setItemName("Herb");
		setItemTargetType(SINGLE);
		setHealAmount(15);
		setItemAmount(1);
		setItemTextImage();
		setItemAmountTextImage();
	}
};
class Potion : public HealingItem{
public:
	Potion() : HealingItem(){
		setItemDesc("A terrible brew of animal parts. Recovers 30 Health Points.");
		setItemName("Potion");
		setItemTargetType(SINGLE);
		setHealAmount(30);
		setItemAmount(1);
		setItemTextImage();
		setItemAmountTextImage();
	}
};
class TriggerItem : public Item{
public:
	TriggerItem(){	}
private:
};
class Equipment : public Item{
	public:
		Equipment(){
		setItemActive(NOTACTIVE);
		setItemEffect(NOEFFECT);
		setItemType(EQUIPMENT);
		}
	private:
};
class WoodenStick : public Equipment{
	public:
		WoodenStick() : Equipment(){
			setItemDesc("A wooden stick...");
			setItemName("Wooden Stick");
			setItemAmount(1);
			setItemTextImage();
			setItemAmountTextImage();
		}
};
#endif