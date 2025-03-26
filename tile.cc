#include "tile.h"
#include "subject.h"

// include the various characters
#include "human.h"
#include "elf.h"
#include "orc.h"
#include "dwarf.h"

#include "dragon.h"
#include "goblin.h"
#include "merchant.h"
#include "phoenix.h"
#include "troll.h"
#include "vampire.h"
#include "werewolf.h"

// constructor and destructor
Tile::Tile(int height, int width, Type type): info{width, height, type, TileState::Empty} {}

Tile::~Tile() {}

void Tile::notify(Subject<Info, State> &whoFrom) {

}

// return the tile's information- done
Info Tile::getInfo() const {
    return info;
}

// set position
void Tile::setPosition(const int position) {
    this->position = position;
}

// get position
int Tile::getPosition() const {
    return position;
}

// set next position
void Tile::setNextPosition(const int next) {
    this->nextPosition = next;
}

// get next position
int Tile::getNextPosition() const {
    return nextPosition;
}

// set the state of the tile
void Tile::setTileState(TileState tileState) {
    Info newInfo = this->getInfo();
    newInfo.tilestate = tileState;

    info = newInfo;
}

// set the next state of the tile
void Tile::setTileNextState(TileState tileNext) {
    Info newInfo = this->getInfo();
    newInfo.nextState = tileNext;

    info = newInfo;
}

void Tile::update() {
    position = nextPosition;
    nextPosition = 0;

    Info newInfo = this->getInfo();
    newInfo.tilestate = newInfo.nextState;
    newInfo.nextState = TileState::Empty;
}
