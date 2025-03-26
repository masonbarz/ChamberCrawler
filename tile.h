#ifndef TILE_H
#define TILE_H
#include <cstddef>
#include "tilestate.h"
#include "subject.h"
#include "observer.h"
#include "tileinfo.h"

#include "player.h"
#include "enemies.h"
#include "treasure.h"
#include "potion.h"

class Tile : public Subject<Info, State>, public Observer<Info, State>{
    Info info;

    int position = 0;
    int nextPosition = 0;

 public: 
    // constructor, destructor - DONE
    Tile(int height, int width, Type type);
    ~Tile(); 
    
    // notify
    void notify(Subject<Info, State> &whoFrom) override;

    // get info- done
    Info getInfo() const override;

    // position "pointer" info - DONE
    void setPosition(const int position);
    int getPosition() const;
    void setNextPosition(const int next);
    int getNextPosition() const;

    // updating the info - DONE 
    void setTileState(TileState tileState);
    void setTileNextState(TileState tileNext);
    
    // update positions
    void update();
};

#endif
