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
    string tileBag;
    int addedPlayers = 0;
    string turns;
    bool newRound = true;
    bool fileIsIncorrect = true;

    players = gameEngine->getGameboard()->getPlayers();
    if(file.is_open()) {
        //todo if tile bag isnt 100
        getline(file, tileBag);
        readTileBag(tileBag);
        // after reading the tiles the file is still on the first line, therefor i need to move to the second line and use a buffer
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

void Test::readTileBag(string tileBag){
    bool checkIn = false;
    if(tileBag.length()-1 != (long unsigned int)tileBagSize){
        std::cout << "Bag Invalid" << std::endl;
        throw exception();
    }
    else{
        for(long unsigned int i = 0; i<tileBag.length()-1; i++){
            checkIn = gameEngine->getGameboard()->addTileBag(tileBag[i]);
            if(checkIn == false){
                std::cout << "Bag Invalid" << std::endl;
                throw exception();
            }
        }
    }
}