#include <fstream>
#include <iomanip>
#include "grid.h"
using namespace std;

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

// constructor - default init stuff that will be updated in init anyways each game - done
Grid::Grid(): floorNum{1}, playerLocation{0, 0} {}

// destructor - done
Grid::~Grid(){
    theGrid.clear();
}

// random number generator - done
int Grid::randomNumber() {
    std::default_random_engine rng{seed};

    int rngseed;
    string rngstring = "";

    if (seedCount >= 10000) {seedCount = 0;}

    for (int i = 0; i < seedCount + 1; i++ ) {
        std::shuffle( v.begin(), v.end(), rng );

        if (i == seedCount) {
            // add those numbers into a string so it can be converted into an int
            for ( int j : v ) {
                rngstring += to_string(j);
            }

            istringstream rngss{rngstring};
            rngss >> rngseed;
        }
        
	} // for

    ++seedCount;
    return rngseed;
}

void Grid::cleanup() {
    // RNG  
    seed = std::chrono::system_clock::now().time_since_epoch().count(); 
    seedCount = 0;
    floorNum = 1; // reset floor count

    // clear the previous game if it existed
    td->clearDisplay(); // clear text display
    player.clear();

    // clear all tiles
    for (int i = 0; i < theGrid.size(); ++i) { 
        theGrid[i].clear();
    }

    // clear potions, enemies, treasures
    potions.clear();
    enemies.clear();
    treasures.clear();

    for (int i = 0; i < 6; ++i) {
        isPotionKnown[i] = false;
    }
}

Coord Grid::directionCoords(int x, int y, Direction direction) {
    Coord toReturn{0, 0};

    switch (direction) {
        case Direction::NW: // NW
             toReturn.sety(y - 1);
             toReturn.setx(x - 1);
             break;
        case Direction::N: // N
            toReturn.sety(y - 1);
            toReturn.setx(x);
            break;
        case Direction::NE: // NE
            toReturn.sety(y - 1);
            toReturn.setx(x + 1);
        case Direction::W:  // W
            toReturn.sety(y);
            toReturn.setx(x - 1);
            break;
        case Direction::E: // E
            toReturn.sety(y);
            toReturn.setx(x + 1);
            break;
        case Direction::SW: // SW
            toReturn.sety(y + 1);
            toReturn.setx(x - 1);
            break;
        case Direction::S: // S
            toReturn.sety(y + 1);
            toReturn.setx(x);
            break;
        case Direction::SE: // SE
            toReturn.sety(y + 1);
            toReturn.setx(x + 1);
            break;
    }

    return toReturn;
}

string Grid::directionToString(Direction direction) {
    switch (direction) {
        case Direction::NW: // NW
             return "Northwest";
        case Direction::N: // N
            return "North";
        case Direction::NE: // NE
            return "Northeast";
        case Direction::W:  // W
            return "West";
        case Direction::E: // E
            return "East";
        case Direction::SW: // SW
            return "Southwest";
        case Direction::S: // S
            return "South";
        case Direction::SE: // SE
            return "Southeast";
    }
    return "";
}

// set up the grid - performed once across all games - done
void Grid::setupGrid() {
    // read in the chambers
    ifstream coordinatefile{COORDFILE};
    string floor;

    // for each row/string of the file, read in the coordinates consisting of that chamber
    while ( getline(coordinatefile, floor)) {
    	if (!floor.empty() && floor.back() == '\r') {
    		floor.pop_back();
    	}
    	
        // get each individual row of coordinates
        istringstream floorcoords{ floor };
        string floorrow;

        vector<Coord> tempvec;
        
        while ( getline( floorcoords, floorrow, '~' ) ) {
            // get the start and ending coordinates for each row
            size_t split1 = floorrow.find(',');
            size_t split2 = floorrow.find('-');

            string rowstr = floorrow.substr(0, split1);
            string firsthalf = floorrow.substr(split1 + 1, split2 - split1 - 1);
            string secondhalf = floorrow.substr(split2 + 1);
            
            // conversions
            istringstream rowss {rowstr};
            istringstream row1 {firsthalf};
            istringstream row2 {secondhalf};

            int temp_row;
            int temp1;
            int temp2;

            rowss >> temp_row;
            row1 >> temp1;
            row2 >> temp2;

            //cout << "DEBUG: " << rowstr << endl;

            // generate the coordinates
            for (int i = temp1; i <= temp2; ++i) {
                tempvec.emplace_back(i, temp_row);

                tempvec[i - temp1].setx(i);
                tempvec[i - temp1].sety(temp_row);
            }

        }

        chambers.emplace_back(tempvec);

        // set up some vectors
        td = make_unique<TextDisplay>(); // textdisplay

        // creating vectors to store the tiles
        for (int i = 0; i < HEIGHT; ++i) {
            vector<Tile> coordvec;
            theGrid.emplace_back(coordvec);
        }
    }
}

// initialization function when the filename is provided
void Grid::init(const char race, const std::string filename) {
    // initialize parameters
    this->filename = filename;
    usedExternalFile = true;

    // clean up the old game
    this->cleanup();

    // set up the new game
    ifstream file{filename}; // for reading in everything
    isMerchantHostile = false;

    // textdisplay setup
    char toDisplay;
    file >> noskipws;

    // create a new board and player
    switch (race) {
        case 'h':
            td->init(HUMAN);
            player.emplace_back(Human());
            break;
        case 'e':
            td->init(ELF);
            player.emplace_back(Elf());
            break;
        case 'd':
            td->init(DWARF);
            player.emplace_back(Dwarf());
            break;
        case 'o':
            td->init(ORC);
            player.emplace_back(Orc());
            break;
    }

	string line;
    // set up the textdisplay and new tiles
    for (int i = 0; i < HEIGHT; ++i) {
    	getline(file, line);
    	if (!line.empty() && line.back() == '\r') {
    		line.pop_back();
    	}
    	
    	if (line.size() < WIDTH) {
    		cout << "DEBUG: WARNING: Line " << i << " only has " << line.size() << " characters!" << endl;
    	}
    	
        for (int j = 0; j < WIDTH; ++j) {
            toDisplay = line[j];

			if (toDisplay == '\n') {
				cout << "DEBUG: Found newline in display data at (" << i << "," << j << ")" << endl;
			}
            // set up the base tile first
            Type tileType;
            switch (toDisplay) {
                case ' ':
                    tileType = Type::Blank;
                    break;
                case '|':
                case '-':
                    tileType = Type::Wall;
                    break;
                case '+':
                    tileType = Type::Door;
                    break;
                case '#':
                    tileType = Type::Passage;
                    break;
                default: // . and all other letters
                    tileType = Type::Floor;
                    break;
            }

            Tile newTile{i, j, tileType};
            theGrid[i].emplace_back(newTile);

            // not-random item generation
			switch (toDisplay) {
                case '0': // Restore HP
                    {
                        int itemposition = potions.size();
                        toDisplay = POTION;

                        potions.emplace_back(RestoreHP{});
                        theGrid[i][j].setTileState(TileState::Potion);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                    
                case '1': // Boost Attack
                    {   
                        int itemposition = potions.size();
                        toDisplay = POTION;

                        potions.emplace_back(BoostAtk{});
                        theGrid[i][j].setTileState(TileState::Potion);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case '2': // Boost Defense
                    {
                        int itemposition = potions.size();
                        toDisplay = POTION;

                        potions.emplace_back(BoostDef{});
                        theGrid[i][j].setTileState(TileState::Potion);
                        theGrid[i][j].setPosition(itemposition);

                        break; 
                    }
                case '3': // Poison HP
                    {
                        int itemposition = potions.size();
                        toDisplay = POTION;

                        potions.emplace_back(PoisonHP{});
                        theGrid[i][j].setTileState(TileState::Potion);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case '4': // Wound Attack
                    {
                        int itemposition = potions.size();
                        toDisplay = POTION;

                        potions.emplace_back(WoundAtk{});
                        theGrid[i][j].setTileState(TileState::Potion);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case '5': // Wound Defense
                    {
                        int itemposition = potions.size();
                        toDisplay = POTION;

                        potions.emplace_back(WoundDef{});
                        theGrid[i][j].setTileState(TileState::Potion);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case '6': // normal gold
                    {
                        int itemposition = treasures.size();
                        toDisplay = TREASURE;

                        treasures.emplace_back(Normal{j, i});
                        theGrid[i][j].setTileState(TileState::Gold);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case '7':  // small gold
                    {
                        int itemposition = treasures.size();
                        toDisplay = TREASURE;

                        treasures.emplace_back(SmallHorde{j, i});
                        theGrid[i][j].setTileState(TileState::Gold);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case '8': // merchant horde
                    {
                        int itemposition = treasures.size();
                        toDisplay = TREASURE;

                        treasures.emplace_back(MerchantHorde{j, i});
                        theGrid[i][j].setTileState(TileState::Gold);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case '9': // dragon horde
                    {
                        int itemposition = treasures.size();
                        toDisplay = TREASURE;

                        treasures.emplace_back(DragonHorde{j, i});
                        theGrid[i][j].setTileState(TileState::Gold);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case DRAGON:
                    {
                        int enemyposition = enemies.size();

                        enemies.emplace_back(Dragon{});
                        theGrid[i][j].setTileState(TileState::Enemy);
                        theGrid[i][j].setPosition(enemyposition);

                        break;
                    }
                case WEREWOLF:
                    {
                        int enemyposition = enemies.size();

                        enemies.emplace_back(Werewolf{});
                        theGrid[i][j].setTileState(TileState::Enemy);
                        theGrid[i][j].setPosition(enemyposition);

                        break;
                    }
                case TROLL:
                    {
                        int enemyposition = enemies.size();

                        enemies.emplace_back(Troll{});
                        theGrid[i][j].setTileState(TileState::Enemy);
                        theGrid[i][j].setPosition(enemyposition);

                        break;
                    }
                case VAMPIRE:
                    {
                        int enemyposition = enemies.size();

                        enemies.emplace_back(Vampire{});
                        theGrid[i][j].setTileState(TileState::Enemy);
                        theGrid[i][j].setPosition(enemyposition);

                        break;
                    }
                case GOBLIN:
                    {
                        int enemyposition = enemies.size();

                        enemies.emplace_back(Goblin{});
                        theGrid[i][j].setTileState(TileState::Enemy);
                        theGrid[i][j].setPosition(enemyposition);

                        break;
                    }
                case PHOENIX:
                    {
                        int enemyposition = enemies.size();

                        enemies.emplace_back(Phoenix{});
                        theGrid[i][j].setTileState(TileState::Enemy);
                        theGrid[i][j].setPosition(enemyposition);

                        break;
                    }
                case MERCHANT:
                    {
                        int enemyposition = enemies.size();

                        enemies.emplace_back(Merchant{isMerchantHostile});
                        theGrid[i][j].setTileState(TileState::Enemy);
                        theGrid[i][j].setPosition(enemyposition);

                        break;
                    }
                case BARRIER:
                    {
                        int itemposition = treasures.size();

                        treasures.emplace_back(BarrierSuit{j, i});
                        theGrid[i][j].setTileState(TileState::Barrier);
                        theGrid[i][j].setPosition(itemposition);

                        break;
                    }
                case PLAYER:
                    {
                        int ourposition = 0; 
                    
                        playerLocation.setx(j);
                        playerLocation.sety(i);

                        theGrid[i][j].setTileState(TileState::Player);
                        theGrid[i][j].setPosition(ourposition);

                        break;
                    }
                case COMPASS:
                    {
                        theGrid[i][j].setTileState(TileState::Compass);
                        break;
                    }
                case EXIT:
                    {
                        theGrid[i][j].setTileState(TileState::Stairs);
                        break;
                    }
            }

            // have dragons set pointers to their gold and barrier suits

            td->setChar(toDisplay, j, i); // j is width, i is height
        }

        //file >> toDisplay; // get rid of the newline
    } // for loop ends here

    file >> skipws;
    action = "";
    action += "Player character has spawned.";

    // player may want to check the surrounding tiles for what they see

    td->updateAction(action);
    td->updateStats(player[0].getGold(), player[0].getHP(), player[0].getAtk(), player[0].getDef());
}

// initialization function when everything must be generated by the game
void Grid::init(const char race) {
    // initialize parameters
    this->filename = DEFAULTFILE;
    usedExternalFile = false;

    // clean up the old game
    this->cleanup();

    // set up the new game
    ifstream file{filename}; // for reading in the base map
    isMerchantHostile = false;

    // textdisplay setup
    char toDisplay;
    file >> noskipws;

    // init - create a new empty board and player race
    switch (race) {
        case 'h':
            td->init(HUMAN);
            player.emplace_back(Human());
            break;
        case 'e':
            td->init(ELF);
            player.emplace_back(Elf());
            break;
        case 'd':
            td->init(DWARF);
            player.emplace_back(Dwarf());
            break;
        case 'o':
            td->init(ORC);
            player.emplace_back(Orc());
            break;
    }

    // set up text display, basic tiles
    string line;
    for (int i = 0; i < HEIGHT; ++i) {
    	getline(file, line);
    	if (!line.empty() && line.back() == '\r') {
    		line.pop_back();
    	}
    	
        for (int j = 0; j < WIDTH; ++j) {
            toDisplay = line[j];
            Type tileType;

            switch (toDisplay) {
                case ' ':
                    tileType = Type::Blank;
                    break;
                case '|':
                case '-':
                    tileType = Type::Wall;
                    break;
                case '+':
                    tileType = Type::Door;
                    break;
                case '#':
                    tileType = Type::Passage;
                    break;
                case '.':
                    tileType = Type::Floor;
                    break;
            }
			//cout << "DEBUG: " << toDisplay << endl;
            Tile newTile{i, j, tileType};
            theGrid[i].emplace_back(newTile);
            td->setChar(toDisplay, j, i); // j is width, i is height
        }
    }

    // random number generation time!
    // generate player location
    int randomNum = randomNumber(); // player chamber

    // generate exact tile of the chamber
    int playerChamber = randomNum % 5;
    int numberOfTiles = chambers[playerChamber].size();
    randomNum = randomNumber();
    int playerTile = randomNum % numberOfTiles;

    int tileCoordx = chambers[playerChamber][playerTile].getx();
    int tileCoordy = chambers[playerChamber][playerTile].gety();
    
    playerLocation.setx(tileCoordx);
    playerLocation.sety(tileCoordy);
    theGrid[tileCoordy][tileCoordx].setPosition(0);
    theGrid[tileCoordy][tileCoordx].setTileState(TileState::Player);

    td->setChar(PLAYER, tileCoordx, tileCoordy);

    // stairway location
    bool goodStairGeneration = false;

    while (!goodStairGeneration) {
        randomNum = randomNumber(); // stairway chamber
        int stairsChamber = randomNum % 5;
        if (stairsChamber == playerChamber) {continue;} // pick another chamber

        // generate exact tile in the chamber
        int numberOfTiles = chambers[stairsChamber].size();
        randomNum = randomNumber();
        int stairsTile = randomNum % numberOfTiles;

        int tileCoordx = chambers[stairsChamber][stairsTile].getx();
        int tileCoordy = chambers[stairsChamber][stairsTile].gety();

        theGrid[tileCoordy][tileCoordx].setTileState(TileState::Stairs);
        td->setChar(EXIT, tileCoordx, tileCoordy);
        goodStairGeneration = true;
    }

    // generate potions
    int potionsGenerated = 0;
    while (potionsGenerated < 10) {
        randomNum = randomNumber(); // potion chamber
        int potionChamber = randomNum % 5; // random chamber

        // generate exact tile in the chamber
        int numberOfTiles = chambers[potionChamber].size();
        randomNum = randomNumber();
        int potionTile = randomNum % numberOfTiles;

        int tileCoordx = chambers[potionChamber][potionTile].getx();
        int tileCoordy = chambers[potionChamber][potionTile].gety();

        // is there already something here? 
        Info potionTileInfo = theGrid[tileCoordy][tileCoordx].getInfo();
        if (potionTileInfo.tilestate == TileState::Potion) {continue;}
        if (potionTileInfo.tilestate == TileState::Player) {continue;}
        if (potionTileInfo.tilestate == TileState::Stairs) {continue;}

        int itemposition = potions.size();
        td->setChar(POTION, tileCoordx, tileCoordy);
        theGrid[tileCoordy][tileCoordx].setPosition(itemposition);
        theGrid[tileCoordy][tileCoordx].setTileState(TileState::Potion);

        // set the kind of potion
        randomNum = randomNumber();
        int potionType = randomNum % 6;

        switch (potionType) {
            case 0:
                potions.emplace_back(RestoreHP{});
                break;
            case 1:
                potions.emplace_back(BoostAtk{}); 
                break;
            case 2: 
                potions.emplace_back(BoostDef{});
                break;
            case 3: 
                potions.emplace_back(PoisonHP{});
                break;
            case 4: 
                potions.emplace_back(WoundAtk{});
                break;
            case 5:
                potions.emplace_back(WoundDef{});
                break;
        }
         
        ++potionsGenerated;
    }

    // generate gold


    // generate dragons


    // generate barrier suit floor
    randomNum = randomNumber();
    bSuitFloor = (randomNum % 5) + 1;

    if (bSuitFloor == floorNum) {

    }

    // generate enemies

    // pick an enemy to hold the compass

    // potentially have a function where the player sees the 8 squares around it.

    file >> skipws;
    action = "Player character has spawned.";
    td->updateAction(action);
    td->updateStats(player[0].getGold(), player[0].getHP(), player[0].getAtk(), player[0].getDef());
}

// should the game end? - DONE
bool Grid::endGame() {
    int playerHP = player[0].getHP();

    // no health
    if (playerHP == 0) {return true;}

    // no 6th floor, means 'exceeded 5th'
    if (floorNum == 6) {return true;}

    return false;
}

// returns the gold the player obtained - DONE
int Grid::playerScore() {
    int gold = player[0].getGold();

    if (player[0].getRace() == "Human") {
        return gold * 2;
    } 
    return gold;
}

void Grid::attack(Direction dir) {
    // check if the tile in the chosen direction can be attacked
        // else return
    // attack them

    // bool isMerchantHostile;

    // get our current location
    int playerx = playerLocation.getx();
    int playery = playerLocation.gety();

    // where do we want to go?
    Coord nextTile = directionCoords(playerx, playery, dir);
    int nextTilex = nextTile.getx();
    int nextTiley = nextTile.gety();

    // it cannot be a wall or a random empty space
    Info nextTileInfo = theGrid[nextTiley][nextTilex].getInfo();
    if (nextTileInfo.type == Type::Wall || nextTileInfo.type == Type::Blank) {
        return;
    }
}

void Grid::use(Direction dir) {
    // get our current location
    int playerx = playerLocation.getx();
    int playery = playerLocation.gety();

    // where do we want to go?
    Coord nextTile = directionCoords(playerx, playery, dir);
    int nextTilex = nextTile.getx();
    int nextTiley = nextTile.gety();

    // it cannot be a wall or a random empty space
    Info nextTileInfo = theGrid[nextTiley][nextTilex].getInfo();
    if (nextTileInfo.type == Type::Wall || nextTileInfo.type == Type::Blank) {
        // update action message
        // enemies
        return;
    }

    // we can't use on a passage or a door
    if (nextTileInfo.type == Type::Passage || nextTileInfo.type == Type::Door) {
        // update action message
        // enemies
        return;
    }

    if (nextTileInfo.tilestate == TileState::Potion) {
        // get the potion, apply it to the player
        int toRemoveIndex = theGrid[nextTiley][nextTilex].getPosition(); // get the index of the potion
        string potionName = potions[toRemoveIndex].getPotionType();

        if (potionName == "RestoreHP") {
            
        } else if (potionName == "BoostAtk") {
            
        } else if (potionName == "BoostDef") {
            
        } else if (potionName == "PoisonHP") {
            
        } else if (potionName == "WoundAtk") {
            
        } else {
            
        }

        // potions[toRemoveIndex].setStatus(&(player[0])); // apply the effects to the player

        
        // get rid of the potion
        potions.erase(potions.begin() + toRemoveIndex);

        // move the player to where the potion was
        // what was this tile before the player stepped on it?
        Info currentTileInfo = theGrid[playery][playerx].getInfo();
        char changeCurrentTile = FLOOR;

        if (currentTileInfo.type == Type::Door) {
            changeCurrentTile = DOOR;
        } else if (currentTileInfo.type == Type::Passage) {
            changeCurrentTile = PASSAGE;
        }

        // remove player from current tile, move to next tile
        playerLocation.setx(nextTilex);
        playerLocation.sety(nextTiley);
        theGrid[playery][playerx].setTileState(TileState::Empty);
        
        // the player is on the next tile now
        theGrid[nextTiley][nextTilex].setTileState(TileState::Player);

         // set up the text display
        td->setChar(PLAYER, nextTilex, nextTiley);
        td->setChar(changeCurrentTile, playerx, playery);

        td->updateStats(player[0].getGold(), player[0].getHP(), player[0].getAtk(), player[0].getDef());
        action = "";
        action += "PC uses " + potionName + ".";

        // does the player see something?
        // move enemies

        td->updateAction(action);

    } else if (nextTileInfo.tilestate == TileState::Compass) {
        // do some stuff for the compass

        
    } else {
        // make sure to update action and move enemies
        return;
    }

}

void Grid::move(Direction dir) {
    // get our current location
    int playerx = playerLocation.getx();
    int playery = playerLocation.gety();

    // where do we want to go?
    Coord nextTile = directionCoords(playerx, playery, dir);
    int nextTilex = nextTile.getx();
    int nextTiley = nextTile.gety();

    // it cannot be a wall or a random empty space
    Info nextTileInfo = theGrid[nextTiley][nextTilex].getInfo();
    if (nextTileInfo.type == Type::Wall || nextTileInfo.type == Type::Blank) {
        return;
    }

    // it cannot be occupied by enemies, potions, compass (use or attack)
    // make sure to update action and move enemies
    if(nextTileInfo.tilestate == TileState::Enemy) {return;}
    if(nextTileInfo.tilestate == TileState::Potion) {return;}
    if(nextTileInfo.tilestate == TileState::Compass) {return;}

    // is it a dragon hoard or barrier suit? make sure it's unguarded
    if(nextTileInfo.tilestate == TileState::Barrier || nextTileInfo.tilestate == TileState::Gold) {
        for (Treasure i : treasures) {
            if (i.getHLocation() == nextTilex && i.getWLocation() == nextTiley) {
                if (i.getIsGuarded()) {return;} // can't walk on a guarded treasure
                // make sure to update action and move enemies
                break;
            }
        }
    }

    // are there stairs?
    if (nextTileInfo.nextState == TileState::Stairs) {
        this->nextFloor(); // generate a blank floor and return.
        return;
    }

    // else we can walk on it! yay
    Info currentTileInfo = theGrid[playery][playerx].getInfo();
    char changeCurrentTile = FLOOR;

    // what was this tile before the player stepped on it?
    if (currentTileInfo.type == Type::Door) {
        changeCurrentTile = DOOR;
    } else if (currentTileInfo.type == Type::Passage) {
        changeCurrentTile = PASSAGE;
    }

    // remove player from current tile, move to next tile
    playerLocation.setx(nextTilex);
    playerLocation.sety(nextTiley);
    theGrid[playery][playerx].setTileState(TileState::Empty);

    // if it's a passage or a door, just walk onto it, no checks necessary
    if (nextTileInfo.type == Type::Passage || nextTileInfo.type == Type::Door) {
        theGrid[nextTiley][nextTilex].setTileState(TileState::Player);
    } else {
        // if it's a floor, there's more things to consider: 
        // is there gold that is pick up able? pick it up
        if (nextTileInfo.tilestate == TileState::Gold) {

            // pick up the gold
            int toRemoveIndex = 0;
            for (Treasure i : treasures) {
                if (i.getHLocation() == nextTilex && i.getWLocation() == nextTiley) {
                    int newGold = player[0].getGold() + i.getValue();
                    player[0].setGold(newGold);
                    break;
                }
                ++toRemoveIndex;
            }

            treasures.erase(treasures.begin() + toRemoveIndex); // remove that gold
            theGrid[nextTiley][nextTilex].setTileState(TileState::Player);

        } else if (nextTileInfo.tilestate == TileState::Barrier) {

            // pick up barrier suit
            int toRemoveIndex = 0;
            for (Treasure i : treasures) {
                if (i.getHLocation() == nextTilex && i.getWLocation() == nextTiley) {
                    player[0].hasBarrierSuit();
                    break;
                }
                ++toRemoveIndex;
            }

            treasures.erase(treasures.begin() + toRemoveIndex); // remove that barrier suit
            theGrid[nextTiley][nextTilex].setTileState(TileState::Player);
        } else { // empty tile
            theGrid[nextTiley][nextTilex].setTileState(TileState::Player);
        }
    }

    // set up the text display
    td->setChar(PLAYER, nextTilex, nextTiley);
    td->setChar(changeCurrentTile, playerx, playery);
    td->updateStats(player[0].getGold(), player[0].getHP(), player[0].getAtk(), player[0].getDef());
    action = "";
    action += "PC moves " + directionToString(dir) + ".";

    // does the player see something?
    // move enemies

    td->updateAction(action);
}

void Grid::moveEnemies() {

}

void Grid::nextFloor() {
    ++floorNum;
    if (floorNum > 5) { // deal with reaching the top floor
    }

    // different floor generation for file vs no file
    if (usedExternalFile) {

    } else {

    }
}

void Grid::notify(Subject<Info, State> &whoFrom) {

}

// output operator - DONE       
std::ostream &operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
