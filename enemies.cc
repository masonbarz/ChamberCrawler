#include "enemies.h"
using namespace std;

Enemy::Enemy(int atk, int def, int hp, string race): Character{hp, atk, def, race}, hasCompass{false} {}

Enemy::~Enemy() {};

void Enemy::setCompassStat(const bool compass) {
	this->hasCompass = compass;
}

bool Enemy::getCompassStat() const {
	return this->hasCompass;
}

void Enemy::attack(Character *player, const int missRate) {
	// implement 50% miss
	if (missRate % 2) {
		return;				//Enemy missed
	}

	// calculate attack
	int playerDef = player->getDef();
	int playerHP = player->getHP();
	int enemyAtk = this->getAtk();

	// Damage (Defender) = ceiling (100 / (100 + Def(defender)) * Atk(Attacker))
	int damage = (100 * enemyAtk * 10) / playerDef;

	if (damage % 10) { // do not need to ceiling (ex. 15 is 15)
		damage /= 10;
	} else { // requires a ceiling (ex. 15.5 becomes 16)
		damage /= 10;
		damage += 1;
	}

	if (player->hasBarrierSuit()) {
		if (damage % 2) { // multiple of 2
			damage /= 2;
		} else {
			damage /= 2;
			damage += 1;
		}
	}

	// ensure that player HP never goes below 0
	playerHP = (playerHP - damage <= 0) ? 0 : playerHP - damage;

	// attack the player by changing their HP
	player->setHP(playerHP);
}
