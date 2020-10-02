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
    void readTileBag(char c);
    void readTurn();
private:
    GameEngine* gameEngine;
};

#endif // TEST_H