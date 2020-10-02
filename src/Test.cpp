#include "Test.h"
#include <iostream>

Test::Test(){
    gameEngine = new GameEngine();
    readSaveFile();
}
Test::~Test(){
    
}

void Test::readSaveFile(){
    readTileBag();
    readTurn();
}

void Test::readTileBag(){
    char readIn;
    for(int i = 0; i < tileBagSize; i++){
        bool checkIn = false;
        std::cin >> readIn;
        checkIn = gameEngine->getGameboard()->addTileBag();
        if(checkIn = false){
            std::cout << "Bag Invalid" << std::endl;
            throw exception();
        }
    }
}
Test::readTurn(){
    
}