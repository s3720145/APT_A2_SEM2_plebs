#ifndef GAMEENGINE
#define GAMEENGINE

#include "Gameboard.h"
#include "InputProcessing.h"
#include <iostream>

#define tileBagSize 100
#define MAX_PLAYERS 2
#define NUM_ROUNDS  5

using std::cout;
using std::cin;
using std::endl;

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    // starts a new game composing of 5 rounds
    void newGame();

    // loads a game state from a save file
    void loadGame();

    // starts a new round
    void newRound();

    // process the current players turn
    void newPlayerTurn();

    Gameboard* getGameboard();
    InputProcessing* getInputProcessing();

    // prints end of game scores and prints the winner
    void announceWinner();
    void readTileBag(string tileBag);

private:
    Gameboard* gameboard;
    InputProcessing* inputProcessing;
    string tileBagOrder;
};

#endif // GAMEENGINE