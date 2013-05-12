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
		protected:
	std::string ItemName;
	itemType type;
	itemActiveType active;
	itemEffect effect;
	SDL_Surface *ItemTextImage[2], *ItemAmountTextImage[2];
	int amount;
	public:
		Item(){}
		void setItemAmount(int _amount){ amount = _amount;}
		void setItemName(std::string _Name){	ItemName = _Name;}
		void setItemActive(itemActiveType _active){	active = _active;	}
		void setItemEffect(itemEffect _effect){effect = _effect;	}
		void setItemType(itemType _type){	type = _type;}
		int getItemAmount(){ return amount;}
		itemType getItemType(){return type;}
		itemActiveType getItemActive(){return active;}
		itemEffect getItemEffect(){return effect;}
		std::string getItemName(){return ItemName;}
		void freeAmountTextImage(){
			SDL_FreeSurface(ItemAmountTextImage[0]);
			SDL_FreeSurface(ItemAmountTextImage[1]);
		}
		void setItemAmountTextImage(){
			TTF_Font* font;
			font = TTF_OpenFont("../Fonts/coolvetica.ttf",35); //used to be 30 for manga temple
			SDL_Color fgColor = {255,255,0};
			std::ostringstream oss;
			std::cout << "SETTING AMOUNT " << amount << std::endl;
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
class Potion : public HealingItem{
public:
	Potion() : HealingItem(){
		std::cout << "MAKING" << std::endl;
		setItemName("Potion");
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
		
	private:
};
#endif