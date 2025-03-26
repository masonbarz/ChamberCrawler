#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemies.h"

class Merchant: public Enemy {
    bool isHostile;
public:
	Merchant(bool isHostile);
    ~Merchant();
    bool isMerchantHostile() const;
    void setHostile();
};

#endif
