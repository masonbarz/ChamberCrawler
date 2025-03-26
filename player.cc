#include "player.h"
using namespace std;

Player::Player(int atk, int def, int hp, string race, int maxhp):
 Character{hp, atk, def, race}, maxhp{maxhp}, gold{0}, atkModifier{0}, defModifier{0} {}

Player::~Player() {}

void Player::setGold(int goldAmt)
{
	this->gold = gold;
}

int Player::getGold() const {
	return this->gold;
}

int Player::getMaxHP() const {
	return this->maxhp;
}

int Player::getAtk() const {
	if (atk + atkModifier < 0) {return 0;}
	return atk + atkModifier;
}

int Player::getDef() const {
	if (def + defModifier < 0) {return 0;}

	return def + defModifier;
}

void Player::resetModifiers() {
	atkModifier = 0;
	defModifier = 0;
}

void Player::lowerAtkModifier() {
	atkModifier -= 5;
}

void Player::raiseAtkModifier() {
	atkModifier += 5;
}

void Player::lowerDefModifier() {
	defModifier -= 5;
}	

void Player::raiseDefModifier() {
	defModifier += 5;
}

int Player::getAtkModifier() const {
	return atkModifier;
}

int Player::getDefModifier() const {
	return defModifier;
}

void Player::attack(Character *enemy, int missRate) {
	// the miss rate doesn't apply here, but variations of the game may want the PC to miss. 

	// calculate attack amount
	int enemyDef = enemy->getDef();
	int enemyHP = enemy->getHP();
	int playerAtk = this->getAtk();

	// Damage (Defender) = ceiling (100 / (100 + Def(defender)) * Atk(Attacker))
	int damage = (100 * playerAtk * 10) / enemyDef;

	if (damage % 10) { // do not need to ceiling (ex. 15 is 15)
		damage /= 10;
	} else { // requires a ceiling (ex. 15.5 becomes 16)
		damage /= 10;
		damage += 1;
	}

	// ensure enemy HP never goes below 0
	enemyHP = (enemyHP - damage < 0) ? 0 : enemyHP - damage;

	// apply damage to enemy by modifying their HP
	enemy->setHP(enemyHP);
}
