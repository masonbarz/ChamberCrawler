#include "treasure.h"

Treasure::Treasure(int value, bool isGuarded, std::string type, int w_location, int h_location):
 value{value}, isGuarded{isGuarded}, type{type}, w_location{w_location}, h_location{h_location} {}

int Treasure::getValue() {
	return this->value;
}

bool Treasure::getIsGuarded() {
	return this->isGuarded;
}

void Treasure::removeGuarded() {
	isGuarded = false;
}

std::string Treasure::getType() {
	return this->type;
}

int Treasure::getWLocation() {
	return w_location;
}

int Treasure::getHLocation() {
	return h_location;
}

Normal::Normal(int w_location, int h_location): Treasure{1, false, "Normal", w_location, h_location} {}

SmallHorde::SmallHorde(int w_location, int h_location): Treasure{2, false, "SmallHorde", w_location, h_location} {}

MerchantHorde::MerchantHorde(int w_location, int h_location): Treasure{4, false, "MerchantHorde", w_location, h_location} {}

DragonHorde::DragonHorde(int w_location, int h_location): Treasure{6, true, "DragonHorde", w_location, h_location} {}

BarrierSuit::BarrierSuit(int w_location, int h_location): Treasure{0, true, "BarrierSuit", w_location, h_location} {}

Compass::Compass(int w_location, int h_location): Treasure{0, false, "Compass", w_location, h_location} {}
