#include <iomanip>
#include "textdisplay.h"
#include "tile.h"
using namespace std;

// set up a blank board of HEIGHT vectors with WIDTH items each - done
void TextDisplay::init(const string race) {
	theDisplay.clear();
    for (int i = 0; i < HEIGHT; ++i) {
        vector<char> temp (WIDTH, EMPTY); // for each row, create the col's
        theDisplay.emplace_back(temp);
    	//cout << "DEBUG: Adding row " << i << " of length " << temp.size() << endl;
    }

    this->race = race;
    floornum = 1;
}

// clear the theDisplay vector - reset the game board to be 0 x 0 - done
void TextDisplay::clearDisplay() {
    int displaySize = theDisplay.size();

    for (int i = 0; i < displaySize; ++i) {
        theDisplay[i].clear();
    }
    theDisplay.clear();
}

// set the character of any given square in the textdisplay - done
void TextDisplay::setChar(const char toDisplay, const int w, const int h) {
	if (toDisplay == '\r' || toDisplay == '\t') return;		//don't store control chars
    theDisplay[h][w] = toDisplay; // row h, col w
}

// update the stats that should print - done
void TextDisplay::updateStats(const int gold, const int hp, const int atk, const int def) {
    this->gold = gold;
    this->hp = hp;
    this->atk = atk;
    this->def = def;
}

// update the action that should print - done
void TextDisplay::updateAction(string action) {
    this->action = action;
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    // get the state and info of the tile that notified
    State state = whoNotified.getState();
    Info info = whoNotified.getInfo();

    // depending on the state of the tile, modify elements of the board differently
    if (state.action == Action::MovePlayer) {
        // the tile that called is 'losing' its player (reset)

    } else if (state.action == Action::EnemyDefeat) {
        // the tile that called is 'losing' its enemy (reset)
    } else if (state.action == Action::UseStairs) {
        // state will take care of redrawing the entire board, just increment the floor.
        ++floornum;
    } else if (state.action == Action::UseCompass) {
        // the tile that just called 'lost' its compass (reset)
    } else if (state.action == Action::UseGold) {
        
    } else if (state.action == Action::UsePotion) {

    } else if (state.action == Action::UseBarrierSuit) {
        // the tile that just called 'lost' its barrier suit, 
    } else if (state.action == Action::StairsRevealed) {
        // the tile that just called gained stairs - reveal stairs
    }
}

// output operator - done
std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			char toDisplay = td.theDisplay[i][j];

            switch (toDisplay) {
                case TREASURE:
                    out << YELLOW;
                    break;
                case EXIT:
                case COMPASS:
                case BARRIER:
                    out << GREEN;
                    break;
                case PLAYER:
                    out << BLUE;
                    break;
                case DRAGON:
                case WEREWOLF:
                case TROLL:
                case GOBLIN:
                case VAMPIRE:
                case MERCHANT:
                case PHOENIX:
                    out << RED;
                    break;
                case POTION:
                    out << PINK;
                    break;
                default:
                    out << RESET;
                    break;
            }

            out << toDisplay; // for each row, print the successive col's in that rowchar c = td.theDisplay[i][j];
//			if (isprint(c)) out << '.';
//			else out << '?';
			//out << td.theDisplay[i][j];
		}
		out << endl;
	}

	out << left << setw(WIDTH - 10) << "Race: " + td.race + " Gold: " + to_string(td.gold);
    out << left << setw(10) << "Floor: " + to_string(td.floornum) << endl;

    // remaining rows
    out << left << setw(WIDTH) << "HP: " + to_string(td.hp) << endl;
    out << left << setw(WIDTH) << "Atk: " + to_string(td.atk) << endl;
    out << left << setw(WIDTH) << "Def: " + to_string(td.def) << endl;

    out << left << setw(WIDTH) << "Action: " + td.action << endl;

    return out;
    // print the dungeon
///    for (int i = 0; i < HEIGHT; ++i) {
///    	//cout << "DEBUG: " << WIDTH << endl;
///        for (int j = 0; j < WIDTH; ++j) {
///            char toDisplay = td.theDisplay[i][j];
///
///            switch (toDisplay) {
///                case TREASURE:
///                    out << YELLOW;
///                    break;
///                case EXIT:
///                case COMPASS:
///                case BARRIER:
///                    out << GREEN;
///                    break;
///                case PLAYER:
///                    out << BLUE;
///                    break;
///                case DRAGON:
///                case WEREWOLF:
///                case TROLL:
///                case GOBLIN:
///                case VAMPIRE:
///                case MERCHANT:
///                case PHOENIX:
///                    out << RED;
///                    break;
///                case POTION:
///                    out << PINK;
///                    break;
///                default:
///                    out << RESET;
///                    break;
///            }

///            out << toDisplay; // for each row, print the successive col's in that row
///        }
        //cout << "DEBUG: Line " << i << " size: " << td.theDisplay[i].size() << endl;
///        out << endl;
///    }

    // print the first row
///    out << left << setw(WIDTH - 10) << "Race: " + td.race + " Gold: " + to_string(td.gold);
///    out << left << setw(10) << "Floor: " + to_string(td.floornum) << endl;
///
    // remaining rows
///    out << left << setw(WIDTH) << "HP: " + to_string(td.hp) << endl;
///    out << left << setw(WIDTH) << "Atk: " + to_string(td.atk) << endl;
///    out << left << setw(WIDTH) << "Def: " + to_string(td.def) << endl;
    
///    out << left << setw(WIDTH) << "Action: " + td.action << endl;

///    return out;
}
