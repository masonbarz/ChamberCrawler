#include "character.h"
using namespace std;

Character::Character(int hp, int atk, int def, string race):
 hp{hp}, atk{atk}, def {def}, barrierSuit{false}, race {race} {}

Character::~Character() {};

int Character::getHP() const {
	return this->hp;
}

int Character::getAtk() const {
	return this->atk;
}

int Character::getDef() const {
	return this->def;
}

void Character::setHP(const int hp) {
	this->hp = hp;
}

string Character::getRace() const{
	return race;
}

bool Character::hasBarrierSuit() const {
	return barrierSuit;
}

void Character::setBarrierSuit() {
	barrierSuit = true;
}
