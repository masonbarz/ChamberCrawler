#ifndef ORC_H
#define ORC_H
#include "player.h"

class Orc: public Player {
    int actualGold;
public:
	Orc();
    ~Orc();

    void setGold(int goldAmt) override;
};

#endif
