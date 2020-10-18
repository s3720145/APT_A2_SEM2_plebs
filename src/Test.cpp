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
    int addedPlayers = ZERO;
    string turns;
    bool newRound = true;
    bool fileIsIncorrect = true;
    bool modeTypeCorrect = false;
    string modeSaved;
    players = gameEngine->getGameboard()->getPlayers();
    if(file.is_open()) {
        getline(file, modeSaved);
        int modeType = stoi(modeSaved);
        if(modeType == 0){
            modeTypeCorrect = true;
        }
        else if(modeType == 1){
            modeTypeCorrect = true;
        }
        else if(modeType == 2){
            modeTypeCorrect = true;
        }
        else{
            cout << "Mode is wrong, unable to start game!";
        }
        if(modeTypeCorrect == true){
        getline(file, tileBag);
        readTileBag(tileBag);
        // after reading the tiles the file is still on the first line, therefor i need to move to the second line and use a buffer
        while(addedPlayers < playerAmount){
            string playerName;
            getline(file, playerName);
            gameEngine->getGameboard()->addNewPlayer(playerName, modeType);
            addedPlayers++;
        }
        while (getline(file, turns)){
            //std::stringbuf string = (std::stringbuf) turns;
            //cin.rdbuf(&string);
            if(newRound){
                gameEngine->getGameboard()->setFactories();

                cout << "=== Start Round ===" << endl;
                newRound = false;
            }
            cout << "TURN FOR PLAYER: " << gameEngine->getGameboard()->
            getCurrentPlayer()->getPlayerName() << endl;
            cout << "Factories:" << endl;
            cout << gameEngine->getGameboard()->factoriesToString() << endl;
            cout << gameEngine->getGameboard()->
            getCurrentPlayer()->playerBoardToString() << endl << endl;
            fileIsIncorrect = 
            gameEngine->getInputProcessing()->processPlayerInput(
                turns, gameEngine->getGameboard());
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
            for(int i = ZERO; i < playerAmount; i++){
                Player* player = players[i];
                cout << player->playerBoardToString() << endl << endl;
            }
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
    if((int)tileBag.length()-ONE != tileBagSize){
        cout << "Bag Invalid" << endl;
        throw exception();
    }
    else{
        for(int i = ZERO; i<(int) tileBag.length()-ONE; i++){
            checkIn = gameEngine->getGameboard()->addTileBag(tileBag[i]);
            if(checkIn == false){
                cout << "Bag Invalid" << endl;
                throw exception();
            }
        }
    }
}