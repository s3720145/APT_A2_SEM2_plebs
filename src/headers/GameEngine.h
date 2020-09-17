#ifndef GAMEENGINE
#define GAMEENGINE

#include "Gameboard.h"

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

private:
    Gameboard* gameboard;
};

#endif // GAMEENGINE