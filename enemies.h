#ifndef ENEMIES_H
#define ENEMIES_H
#include "character.h"
#include <string>

class Enemy: public Character {
 protected:
	bool hasCompass;
 public:
	Enemy(int atk, int def, int hp, std::string race);
	~Enemy();

	bool getCompassStat() const;
	void setCompassStat(const bool compass);

	virtual void attack(Character *player, const int missRate) override;
};

#endif
