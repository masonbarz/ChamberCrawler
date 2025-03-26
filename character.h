#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

class Character {
 protected:
	int hp;
	int atk;
	int def;
	bool barrierSuit;
	std::string race;
 public:
	Character(int hp, int atk, int def, std::string race);
	~Character();

	int getHP() const;
	virtual int getAtk() const;
	virtual int getDef() const;

	void setHP(const int hp);
	std::string getRace() const;

	virtual void attack(Character *character, const int missRate) = 0;

	bool hasBarrierSuit() const;
	void setBarrierSuit();
};

#endif
