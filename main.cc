#include <iostream>
#include <string>
#include "tilestate.h"
#include "grid.h"
using namespace std;

// is the player's next move an attack, a use, or are they walking? call the appropriate function - done
void playerNextMove(const bool attackFlag, const bool useFlag, const Direction direction, Grid &g) {
    if (attackFlag) { // atack in direction
        g.attack(direction);
    } else if (useFlag) {   // use in direction
        g.use(direction);
    } else { // walk in direction
        g.move(direction);
    }
}

// main function - this is done
int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit | ios::failbit); // from A4Q3

    // for reading user input
    char cmd;
    char cmd2;
    char race;

    // tracking various statuses
    bool useFlag = false;
    bool attackFlag = false;
    bool gameStart = false;

    Grid g;

    // read the CLA - no more code needed here
    if (argc > 2) { // too many arguments
      cout << "Usage: " << argv[0] << " optional-filename" << endl;
      return 1;
    }

    g.setupGrid();

    // read commands from input
    try {
    while (true) {
        if (!gameStart) { // no game yet - setup player race - no more code needed here
            cin >> race;
            switch (race) { // switch statement - easy to add/remove races
                case 'h': // human
                case 'e': // elf
                case 'd': // dwarf
                case 'o': // orc

                    // initialize the game - either with the provided filename for the exact layout
                    // or set up each floor using the usual method
                    // this is not particularly robust - assumes the user provides an existing file
                    // if a previous game was running, the old game is cleared here and then reinitialized
                    if (argc == 2) {
                        g.init(race, argv[1]); 
                    } else {
                        g.init(race);
                    }

                    cout << g;
                    break;
                default:
                    return 1; // invalid race, quit
            }

            // reset the flags
            useFlag = false;
            attackFlag = false;
            gameStart = true;

            continue;
        }

        // there is an ongoing game
        cin >> cmd;
        switch (cmd) {
            case 'u': // use - no more code needed here 
                useFlag = true;
                attackFlag = false;
                break;

            case 'a': // attack - no more code needed here
                useFlag = false;
                attackFlag = true;
                break; 

            // directions - movement, use, attack
            case 'n':
                cin >> cmd2;
                switch (cmd2) {
                    case 'o': // no
                        playerNextMove(attackFlag, useFlag, Direction::N, g);
                        break;
                    case 'w': // nw
                        playerNextMove(attackFlag, useFlag, Direction::NW, g);
                        break;
                    case 'e': // ne
                        playerNextMove(attackFlag, useFlag, Direction::NE, g);
                        break;
                }
                useFlag = false;
                attackFlag = false;
                break;

            case 'e': // ea
                cin >> cmd2;
                if (cmd2 == 'a') {
                    playerNextMove(attackFlag, useFlag, Direction::E, g);
                }
                useFlag = false;
                attackFlag = false;
                break;

            case 's':
                cin >> cmd2;
                switch (cmd2) {
                    case 'o': // so
                        playerNextMove(attackFlag, useFlag, Direction::S, g);
                        break;
                    case 'w': // sw
                        playerNextMove(attackFlag, useFlag, Direction::SW, g);
                        break;
                    case 'e': // se
                        playerNextMove(attackFlag, useFlag, Direction::SE, g);
                        break;
                }
                useFlag = false;
                attackFlag = false;
                break;

            case 'w': // we
                cin >> cmd2;
                if (cmd2 == 'e') {
                    playerNextMove(attackFlag, useFlag, Direction::W, g);
                }
                useFlag = false;
                attackFlag = false;
                break;
            
            case 'r': // restart - no more code needed here
                gameStart = false; // next time it will prompt races again
                useFlag = false;
                attackFlag = false;
                break;

            case 'q': // quit the game - no more code needed here
                return 0; 
        }

        // print the grid
        if (!useFlag && !attackFlag) {
            cout << g;
        }

        // check if the player has won/lost all health
        if (g.endGame()) {
            cout << "Game Over! Your score was: " << g.playerScore() << endl;
            cout << "Would you like to play again? (Y/N)" << endl;

            cin >> cmd;

            if (cmd == 'Y') {
                gameStart = false; // next time it will prompt races again
                useFlag = false;
                attackFlag = false;
                continue;
            } else if (cmd == 'N') {
                return 0;
            } else {
                return 1; // if the player is entering random commands, also just exit so we don't have undefined behaviour
            }

        }
    }

   } catch (ios::failure &) {} // similar to A4Q3, it catches IO failures and quits
}   
