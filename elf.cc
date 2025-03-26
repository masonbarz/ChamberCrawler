#include "elf.h"

Elf::Elf(): Player{30, 10, 140, "Elf", 140} {}

Elf::~Elf() {}

void Elf::lowerAtkModifier() {
    this->raiseAtkModifier();
}

void Elf::lowerDefModifier() {
    this->raiseDefModifier();
}
