#include "dwarf.h"

Dwarf::Dwarf(): Player{20, 30, 100, "Dwarf", 100} {}

Dwarf::~Dwarf() {}

void Dwarf::setGold(int goldAmt) {
    goldAmt *= 2; // dwarves get double gold
    this->gold += goldAmt;
}
