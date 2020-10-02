#ifndef TEST_H
#define TEST_H
#include "GameEngine.h"

#define tileBagSize    100

using std::exception;

class Test {
public:
    Test();
    ~Test();
    void readSaveFile();
    void readTileBag();
private:
    //GameEngine* gameEngine;
};

#endif // TEST_H