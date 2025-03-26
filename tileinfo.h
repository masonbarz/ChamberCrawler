#ifndef TILEINFO_H
#define TILEINFO_H
#include "tilestate.h"

struct Info {
    int w, h; // w is x, h is y
    Type type;
    TileState tilestate; // only used if the type is walkable
    TileState nextState; // used for updating
};

#endif
