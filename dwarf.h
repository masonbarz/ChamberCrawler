#ifndef DWARF_H
#define DWARF_H
#include "player.h"

class Dwarf: public Player {
public:
	Dwarf();
    ~Dwarf();

    void setGold(int goldAmt) override;
};

#endif
