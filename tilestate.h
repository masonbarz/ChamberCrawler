#ifndef TILESTATE_H
#define TILESTATE_H

/*
  Actions: 
  - MovePlayer: the player moves towards a blank tile
  - EnemyDefeat: an enemy has been defeated and needs to be erased off the board. 
    There is no action if the enemy is not defeated. 
  - Use Stairs: the player uses the stairs and forces the entire board to redraw
  - Use Compass: the player uses the compass. Replace C with the player symbol. 
  - Use Gold: the player uses the gold. Replace G with the player symbol. 
  - Use Potion: the player uses the potion. Replace the potion symbol with the player symbol. 
  - Use Barrier Suit: same as above
  - Stairs Revealed: the stairs appear. Replace . with the stairs slash. 
*/

enum class Direction { NW, N, NE, W, E, SW, S, SE };
enum class Type {Wall, Floor, Door, Passage, Blank};
enum class TileState {Empty, Player, Potion, Enemy, Gold, Barrier, Stairs, Compass};
enum class Action {MovePlayer, EnemyDefeat, UseStairs, UseCompass, UseGold, UsePotion, UseBarrierSuit, StairsRevealed};

struct State {
  Direction direction;  // which direction to me is the tile that just called me? 
  Action action; // what action was just performed?
  Type type; // what was the type of the tile that just called me?
  TileState tilestate; // what was the state of the tile that just called me?
};

#endif
