#include "Test.h"
#include <iostream>

Test::Test(){
    gameEngine = new GameEngine();
}
Test::~Test(){
    gameEngine->~GameEngine();
}

void Test::readSaveFile(string fileName){
    std::ifstream file("src/Savefiles/" + fileName);
    char c;
    int addedToBag = 0;
    int addedPlayers = 0;
    string turns;
    bool newRound = true;
    string buffer;
    bool fileIsIncorrect = true;

    players = gameEngine->getGameboard()->getPlayers();
    if(file.is_open()) {
        //todo if tile bag isnt 100
        while(tileBagSize>addedToBag && file >> c ) {
            readTileBag(c);
            addedToBag++;
        }
        // after reading the tiles the file is still on the first line, therefor i need to move to the second line and use a buffer
        getline(file, buffer);
        while(addedPlayers < playerAmount){
            string playerName;
            getline(file, playerName);
            gameEngine->getGameboard()->addNewPlayer(playerName);
            addedPlayers++;
        }
        while (getline(file, turns)){
            //std::stringbuf string = (std::stringbuf) turns;
            cout << turns << std::endl;
            //cin.rdbuf(&string);
            if(newRound){
                gameEngine->getGameboard()->setFactories();

                cout << "=== Start Round ===" << endl;
                newRound = false;
            }
            cout << "TURN FOR PLAYER: " << gameEngine->getGameboard()->getCurrentPlayer()->getPlayerName() << endl;
            cout << "Factories:" << endl;
            cout << gameEngine->getGameboard()->factoriesToString() << endl;
            cout << gameEngine->getGameboard()->getCurrentPlayer()->playerBoardToString() << endl << endl;
            fileIsIncorrect = gameEngine->getInputProcessing()->processPlayerInput(turns, gameEngine->getGameboard());
            if(fileIsIncorrect == false){
                cout << "Save File has an incorrect turn" << std::endl;
                file.close();
            }
            else{
                gameEngine->getGameboard()->setNextCurrentPlayer();
                if(gameEngine->getGameboard()->isEndOfRound()){
                    newRound = true;
                    gameEngine->getGameboard()->endRound();
                    gameEngine->getGameboard()->setNextCurrentPlayer();
                    cout << "=== END OF ROUND ===" << endl;
                }
            }
        }
        if(fileIsIncorrect == true){
            cout << gameEngine->getGameboard()->factoriesToString() << endl;
            for(int i = 0; i < playerAmount; i++){
                Player* player = players[i];
                cout << player->playerBoardToString() << endl << endl;
            }
        }
    } else {
        std::cout << "ERROR - CANNOT FIND - " << fileName << std::endl;
    }

    if(!file.eof() && file.fail()) {
        std::cout << "ERROR READING - " << fileName << std::endl;
    }

    file.close();
}

void Test::readTileBag(char c){
    bool checkIn = false;
    checkIn = gameEngine->getGameboard()->addTileBag(c);
    if(checkIn == false){
        std::cout << "Bag Invalid" << std::endl;
        throw exception();
    }
}