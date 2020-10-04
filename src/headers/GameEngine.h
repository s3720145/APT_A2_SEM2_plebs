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
    void newGame();
    void loadGame();
    void newRound();
    void newPlayerTurn();

    Gameboard* getGameboard();
    InputProcessing* getInputProcessing();
    void announceWinner();
    void readTileBag(string tileBag);

private:
    Gameboard* gameboard;
    InputProcessing* inputProcessing;
};

#endif // GAMEENGINE