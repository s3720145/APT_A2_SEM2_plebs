#ifndef TEST_H
#define TEST_H
#include "GameEngine.h"

#define tileBagSize    100
#define playerAmount   2

using std::exception;

class Test{
public:
    Test();
    ~Test();
    void readSaveFile(string fileName);
    void readTileBag(string tileBag);
private:
    GameEngine* gameEngine;
    Player** players;
};

#endif // TEST_H