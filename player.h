#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "character.h"

class Player: public Character {
 protected:
	int maxhp;
	int gold;
	int atkModifier;
	int defModifier;

 public:
	Player(int atk, int def, int hp, std::string race, int maxhp);
	~Player();
		
	virtual void setGold(int goldAmt);
	int getGold() const;
	
	int getMaxHP() const;

	int getAtk() const override;
	int getDef() const override;

	void resetModifiers();

	virtual void lowerAtkModifier();
	void raiseAtkModifier();
	virtual void lowerDefModifier();
	void raiseDefModifier();

	int getAtkModifier() const;
	int getDefModifier() const;

	virtual void attack(Character *enemy, int missRate) override;
};

#endif
