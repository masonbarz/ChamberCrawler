#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "tilestate.h"
#include "tileinfo.h"
class Tile;

// board constants
    const int WIDTH = 79;
    const int HEIGHT = 25;

// printing constants
    const char EMPTY = ' ';

    const char DRAGON = 'D';
    const char WEREWOLF = 'W';
    const char TROLL = 'T';
    const char GOBLIN = 'N';
    const char VAMPIRE = 'V';
    const char MERCHANT = 'M';
    const char PHOENIX = 'X';

    const char PLAYER = '@';
    const char POTION = 'P';
    const char TREASURE = 'G';
    const char COMPASS = 'C';
    const char BARRIER = 'B';

    const char EXIT = '\\'; 

    const char DOOR = '+';
    const char FLOOR = '.';
    const char PASSAGE = '#';

    // colour codes
    const std::string RESET = "\033[0m";
    const std::string YELLOW =  "\033[33m"; // gold
    const std::string GREEN = "\033[32m"; // exit, compass, barrier suit
    const std::string BLUE = "\033[36m"; // player
    const std::string RED = "\033[31m"; // monsters
    const std::string PINK = "\033[35m"; // potions

class TextDisplay: public Observer<Info, State> { 
    std::vector<std::vector<char>> theDisplay;

    // keeping track of game stats
    std::string race;
    int gold;
    int hp;
    int atk;
    int def;
    int floornum;
    std::string action;

 public: 
    // setting up the vector and removing it
    void init(const std::string race);
    void clearDisplay();

    // functions for setting up the text display for a new game - one character set up at a time
    void setChar(const char toDisplay, const int w, const int h);

    // use to update the printable stats for << operator
    void updateStats(const int gold, const int hp, const int atk, const int def);

    void updateAction(std::string action);

    // when something changes on the board
    void notify(Subject<Info, State> &whoNotified) override;

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

};

#endif
