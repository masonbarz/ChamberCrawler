#ifndef DRAGON_H
#define DRAGON_H
#include "enemies.h"
#include "treasure.h"

class Dragon: public Enemy {
 Treasure *guardedTreasure;
public:
	Dragon();
    ~Dragon();
    void setTreasure(Treasure *treasure);
};

#endif
