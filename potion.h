#ifndef POTION_H
#define POTION_H
#include "player.h"
#include <string>

class Potion {
	std::string potionType;
 public:
	Potion(std::string potionType);
	~Potion();
	virtual void setStatus(Player *player);
	std::string getPotionType();
};

class RestoreHP: public Potion {
public:
	RestoreHP();
	~RestoreHP() = default;
	void setStatus(Player* player) override;
};

class BoostAtk: public Potion {
public:
	BoostAtk();
	~BoostAtk() = default;
	void setStatus(Player* player) override;
};

class BoostDef: public Potion {
public:
	BoostDef();
	~BoostDef() = default;
	void setStatus(Player* player) override;
};

class PoisonHP: public Potion {
public:
	PoisonHP();
	~PoisonHP() = default;
	void setStatus(Player* player) override;
};

class WoundAtk: public Potion {
public:
	WoundAtk();
	~WoundAtk() = default;
	void setStatus(Player* player) override;
};

class WoundDef: public Potion {
public:
	WoundDef();
	~WoundDef() = default;
	void setStatus(Player* player) override;
};

#endif
