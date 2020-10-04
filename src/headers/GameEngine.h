#ifndef GAMEENGINE
#define GAMEENGINE

#include "Gameboard.h"
#include "InputProcessing.h"
#include <iostream>

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

private:
    Gameboard* gameboard;
    InputProcessing* inputProcessing;
    string tileBagOrder;
};

#endif // GAMEENGINE