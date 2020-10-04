#include "Test.h"
#include <iostream>

Test::Test(){
    gameEngine = new GameEngine();
}
Test::~Test(){
    gameEngine->~GameEngine();
}

void Test::readSaveFile(string fileName){
    std::ifstream file("src/Testfiles/" + fileName);
    string tileBag;
    int addedPlayers = 0;
    string turns;
    bool newRound = true;
    bool fileIsIncorrect = true;
    players = gameEngine->getGameboard()->getPlayers();
    if(file.is_open()) {
        //todo if tile bag isnt 100
        getline(file, tileBag);
        cout << (int)tileBag.length();
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
            cout << turns << endl;
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
                cout << "Save File has an incorrect turn" << endl;
                file.close();
            }
            else{
                gameEngine->getGameboard()->setNextCurrentPlayer();
                if(gameEngine->getGameboard()->isEndOfRound()){
                    newRound = true;
                    gameEngine->getGameboard()->endRound();
                    cout << "=== END OF ROUND ===" << endl;
                }
            }
        }
        if(fileIsIncorrect == true){
            cout << "State of Game:" << endl;
            cout << gameEngine->getGameboard()->factoriesToString() << endl;
            for(int i = 0; i < playerAmount; i++){
                Player* player = players[i];
                cout << player->playerBoardToString() << endl << endl;
            }
        }
    } else {
        cout << "ERROR - CANNOT FIND - " << fileName << endl;
    }

    if(!file.eof() && file.fail()) {
        cout << "ERROR READING - " << fileName << endl;
    }

    file.close();
}

void Test::readTileBag(string tileBag){
    bool checkIn = false;
    if((int)tileBag.length()-1 != tileBagSize){
        cout << "Bag Invalid" << endl;
        throw exception();
    }
    else{
        for(int i = 0; i<(int) tileBag.length()-1; i++){
            cout << tileBag[i];
            checkIn = gameEngine->getGameboard()->addTileBag(tileBag[i]);
            if(checkIn == false){
                cout << "Bag Invalid" << endl;
                throw exception();
            }
        }
    }
}