#ifndef GRID_H
#define GRID_H
// general includes
#include <vector>
#include <string>
#include <iostream>
#include <memory>

// for RNG
#include <chrono>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <sstream>

// tiles
#include "coord.h"
#include "textdisplay.h"
#include "tile.h"

// observer pattern
#include "observer.h"

class Character;

// board constants
const std::string DEFAULTFILE = "defaultfile.txt";
const std::string COORDFILE = "coordfile.txt";

// race constants
const std::string HUMAN = "Human";
const std::string ELF = "Elf";
const std::string DWARF = "Dwarf";
const std::string ORC = "Orc";

class Grid: public Observer<Info, State> {
    // random number generator - DONE
    unsigned seed;
    int seedCount = 0;
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // having to do with display - DONE
    std::unique_ptr<TextDisplay> td = nullptr; // pointer to text display (initialize in setup)
    std::string filename; // filename to either read the base map from or the user-specified map (initialize in init)
    bool usedExternalFile;

    // setting up the floors
    int floorNum; // DONE

    // store the coordinates of the tiles that belong to each chamber - DONE (initialize in setup)
    std::vector<std::vector<Coord>> chambers;

    // special things
    bool isMerchantHostile;
    Coord playerLocation;
    bool isPotionKnown[6] = {false, false, false, false, false, false};
    std::string action;

    // characters, items, enemies
    std::vector<Player> player;
    std::vector<Enemy> enemies;
    std::vector<Potion> potions;
    std::vector<Treasure> treasures;

    // having to do with the tiles
    std::vector<std::vector<Tile>> theGrid;  // the entire grid of tiles

    // pre-generated floor and coordinates of the barrier suit, generated at start of game
    // so when the floor that the barrier suit is reached, this is added in
    int bSuitFloor;

    // for RNG - DONE
    int randomNumber();

    // cleanup function for old games - DONE
    void cleanup();

    // giving the board coordinates for a certain direction
    Coord directionCoords(int x, int y, Direction direction);

    // convert direction to strings - for action output - DONE
    std::string directionToString(Direction direction);

public:
    // constructor and destructor - DONE
    Grid();
    ~Grid();

    // initial setup - only has to be done once - DONE
    void setupGrid();

    // initialize the grid - has to be done every time a new game is played
    void init(const char race, const std::string filename);
    void init(const char race);

    // ending the game - DONE
    bool endGame(); // did the player reach the stairs on the 5th floor or lose all health?
    int playerScore(); // if the game ended, return their score

    // different player actions
    void attack(Direction dir);
    void use(Direction dir);
    void move(Direction dir); // DONE

    void moveEnemies(); // after the player attacks, move the enemies
    void nextFloor(); // next floor

    // observer pattern
    void notify(Subject<Info, State> &whoFrom) override;

    friend std::ostream &operator<<(std::ostream &out, const Grid &g);
}; 

#endif
