#include <string>
#include "potion.h"
#include <iostream>
using namespace std;

Potion::Potion(string potionType): potionType{potionType} {}

Potion::~Potion() {}

void Potion::setStatus(Player *player) {
    // literally do nothing.
}

string Potion::getPotionType() {
    return potionType;
}

RestoreHP::RestoreHP(): Potion{"RestoreHP"} {};

void RestoreHP::setStatus(Player* player) {
    int currentHP = player->getHP();
    int playerMaxHP = player->getMaxHP();

	// ensure player HP does not exceed the races MaxHP
	int newHP = (currentHP + 10 > playerMaxHP) ? playerMaxHP : currentHP + 10;	

	player->setHP(newHP);
}

BoostAtk::BoostAtk(): Potion{"BoostAtk"} {};

void BoostAtk::setStatus(Player* player) {
	player->raiseAtkModifier();
}

BoostDef::BoostDef(): Potion{"BoostDef"} {};

void BoostDef::setStatus(Player* player) {
	player->raiseDefModifier();
}

PoisonHP::PoisonHP(): Potion{"PoisonHP"} {};

void PoisonHP::setStatus(Player* player) {
	int currentHP = player->getHP();
    std::string race = player->getRace();

    int newHP;
    if (race == "Elf") {
        int playerMaxHP = player->getMaxHP();
        newHP = (currentHP + 10 > playerMaxHP) ? playerMaxHP : currentHP + 10;
    } else {
        // ensure player HP does not go below 0
	    newHP = (currentHP - 10 < 0) ? 0 : currentHP - 10;
    }

    // update players HP
	player->setHP(newHP);
}

WoundAtk::WoundAtk(): Potion{"WoundAtk"} {};

void WoundAtk::setStatus(Player* player) {
	player->lowerAtkModifier();
}

WoundDef::WoundDef(): Potion{"WoundDef"} {};

void WoundDef::setStatus(Player* player) {
	player->lowerDefModifier();
}
