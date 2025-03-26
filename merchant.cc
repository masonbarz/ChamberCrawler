#include "merchant.h"

Merchant::Merchant(bool isHostile): Enemy{70, 5, 30, "Merchant"}, isHostile{isHostile} {}

Merchant::~Merchant() {}

bool Merchant::isMerchantHostile() const{
    return isHostile;
}

void Merchant::setHostile() {
    isHostile = true;
}
