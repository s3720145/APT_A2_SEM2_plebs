#include "Test.h"
#include <iostream>

Test::Test(){
    gameEngine = new GameEngine();
}
Test::~Test(){
    
}

void Test::readSaveFile(string fileName){
    std::ifstream file("src/Savefiles/" + fileName);
    char c;
    int addedToBag = 0;
    int addedPlayers = 0;
    string turns;
    if(file.is_open()) {
        while(file >> c && tileBagSize>addedToBag) {
            readTileBag(c);
            addedToBag++;
        }
        while(addedPlayers < playerAmount){
            string playerName;
            getline(file, playerName);
            gameEngine->getGameboard()->addNewPlayer(playerName);
        }
        while(file >> turns){
            stringbuf s = turns;
            cin.rdbuf(&s);
            gameEngine->newRound();
        }
        cout << gameEngine->getGameboard()->factoriesToString() << endl;
        for(Player* player : gameEngine->getGameboard()->getPlayers()){
            cout << gameboard->getCurrentPlayer()->playerBoardToString() << endl << endl;
        }
    } else {
        std::cout << "ERROR - CANNOT FIND - src/DefaultTileBag.txt" << std::endl;
    }

    if(!file.eof() && file.fail()) {
        std::cout << "ERROR READING - src/DefaultTileBag.txt" << std::endl;
    }

    file.close();
    readTileBag();
    readTurn();
}

void Test::readTileBag(char c){
    bool checkIn = false;
    checkIn = gameEngine->getGameboard()->addTileBag(c);
    if(checkIn = false){
        std::cout << "Bag Invalid" << std::endl;
        throw exception();
    }
}
void Test::readTurn(){
    
}