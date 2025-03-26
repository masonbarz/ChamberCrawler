#ifndef ELF_H
#define ELF_H
#include "player.h"

class Elf: public Player {
public:
	Elf();
    ~Elf();

    void lowerAtkModifier() override;
    void lowerDefModifier() override;
};

#endif
