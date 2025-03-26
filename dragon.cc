#include "dragon.h"

Dragon::Dragon(): Enemy{20, 20, 150, "Dragon"}  {}

Dragon::~Dragon() {}

void Dragon::setTreasure(Treasure *treasure) {
    guardedTreasure = treasure;
}
