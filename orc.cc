#include "orc.h"

Orc::Orc(): Player{30, 25, 180, "Orc", 180}, actualGold{0} {}

Orc::~Orc() {}

void Orc::setGold(int goldAmt) {
    actualGold += goldAmt;

    this->gold = actualGold / 2;
}
