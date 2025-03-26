#include "coord.h"

// constructor for a coordinate object
Coord::Coord(int x, int y): x{x}, y{y}  {}

// destructor
Coord::~Coord() {}

// mutator functions
void Coord::setx(const int x) {
    this->x = x;
}

void Coord::sety(const int y) {
    this->y = y;
}

// accessor functions
int Coord::getx() const {
    return x;
}

int Coord::gety() const{
    return y;
}
