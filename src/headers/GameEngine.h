#ifndef GAMEENGINE
#define GAMEENGINE

#include "Gameboard.h"
#include "InputProcessing.h"
#include "OutputProcessing.h"
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
    void saveGame();
    void newRound();

    const Gameboard* getGameboard();

private:
    Gameboard* gameboard;
    InputProcessing* inputProcessing;
    OutputProcessing* outputProcessing;
};

#endif // GAMEENGINE