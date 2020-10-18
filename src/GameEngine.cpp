#include "GameEngine.h"

GameEngine::GameEngine() {
    gameboard = new Gameboard();
    inputProcessing = new InputProcessing();
}

GameEngine::~GameEngine() {
    gameboard->~Gameboard();
    inputProcessing->~InputProcessing();
}

void GameEngine::newGame(int modeIn) {
    endOfGame = false;
    cout << "Starting a New Game" << endl << endl;
    mode = modeIn;
    inputProcessing->setMode(mode);
    gameboard->randomizeTileBag(seed, mode);
    int arrayDim = 5;
    if(mode == 2){
        arrayDim = 6;
    }
    for(int i = ZERO; i < MAX_PLAYERS; ++i) {
        string playerName;
        cout << "Enter a name for player " << i << endl;
        cout << "> ";
        cin >> playerName;
        gameboard->addNewPlayer(playerName, arrayDim);
        cout << endl;
    }
    cout << "Let's Play!"<< endl << endl;

    gameboard->setTileBag();
    while(endOfGame == false){
        newRound();
    }
    
    announceWinner();
}

void GameEngine::loadGame() {
    string input;
    string tileBag;
    bool isNewRound = true;
    bool roundComplete = true;
    bool fileIsIncorrect = true;
    bool modeTypeCorrect = false;
    string modeSaved;
    string turns;
    cout << "Enter file name: " << endl;
    cin >> input;
    std::ifstream file("src/Savefiles/" + input);
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
        cout << "Starting a New Game" << endl << endl;

        for(int i = ZERO; i < MAX_PLAYERS; ++i) {
            string playerName;
            cout << "Enter a name for player " << i << endl;
            cout << "> ";
            getline(file, playerName);
            gameboard->addNewPlayer(playerName, modeType);
            cout << endl;
        }
        cout << "Let's Play!"<< endl << endl;
        while (getline(file, turns)){
            if(isNewRound){
                gameboard->setFactories();

                cout << "=== Start Round ===" << endl;
                isNewRound = false;
            }
            cout << "TURN FOR PLAYER: " << 
            gameboard->getCurrentPlayer()->getPlayerName() << endl;
            cout << "Factories:" << endl;
            cout << gameboard->factoriesToString() << endl;
            cout << gameboard->getCurrentPlayer()->playerBoardToString() <<
             endl << endl;
            fileIsIncorrect = inputProcessing->processPlayerInput(
                turns, gameboard);
            roundComplete = false;
            // should never happen if save file has been tested and is correct, but just incase.
            if(fileIsIncorrect == false){
                cout << "Save File has an incorrect turn" << endl;
                file.close();
            }
            else{
                gameboard->setNextCurrentPlayer();
                if(gameboard->isEndOfRound()){
                    isNewRound = true;
                    roundComplete = true;
                    cout << "=== END OF ROUND ===" << endl;
                    gameboard->endRound();
                    Player** players = gameboard->getPlayers();

                    for(int i = ZERO; i < MAX_PLAYERS; ++i) {
                        cout << players[i]->playerBoardToString() << endl;
                        cout << "Current round score: " << players[i]->getCurrRoundScore() <<
                        endl << endl;
                        if(players[i]->getEnd() == true){
                            endOfGame = true;
                        }
                    }
                }
            }
        }
        if(roundComplete == false){
            newPlayerTurn();
        }
        while(endOfGame == false){
            newRound();
        }
        announceWinner();
        }
    }else {
        cout << "ERROR - CANNOT FIND - " << input << endl;
    }
    if(!file.eof() && file.fail()) {
        cout << "ERROR READING - " << input << endl;
    }
}

void GameEngine::newRound() {
    // TODO:
    // Each round, whoever first chooses from the centre pile takes the first player marker, adds it to their floor
    // and will then be first player next round, at which point they will add it to the centre for someone to take the
    // following round.
    
    gameboard->setFactories();
    cout << "=== Start Round ===" << endl;

    while(gameboard->isEndOfRound() == false) {
        newPlayerTurn();
    }

    cout << "=== END OF ROUND ===" << endl;

    gameboard->endRound();

    Player** players = gameboard->getPlayers();

    for(int i = ZERO; i < MAX_PLAYERS; ++i) {
        cout << players[i]->playerBoardToString() << endl;
        cout << "Current round score: " << players[i]->getCurrRoundScore() <<
         endl << endl;
        if(players[i]->getEnd() == true){
            endOfGame = true;
        }
    }
}
    

void GameEngine::newPlayerTurn() {
    string playerInput;
    bool successfulTurn = false;

    cout << "TURN FOR PLAYER: " << 
    gameboard->getCurrentPlayer()->getPlayerName() << endl;
    cout << "Factories:" << endl;
    cout << gameboard->factoriesToString() << endl;
    cout << gameboard->getCurrentPlayer()->playerBoardToString() <<
     endl << endl;
    do {
        cout << "> ";
        std::getline(cin >> std::ws, playerInput);

        if(!cin || playerInput == "quit") {
            throw std::exception();
        }

        try {
            successfulTurn = inputProcessing->processPlayerInput(
                playerInput, gameboard);
          
        } catch(...) {
            cout << "Turn unsuccessful, Please try again!" << endl;
        }
      
        if(successfulTurn == false) {
            cout << "Turn unsuccessful, Please try again!" << endl;
        }
        
    } while(successfulTurn == false);

    gameboard->setNextCurrentPlayer();
}
void GameEngine::announceWinner() {
    bool tie = false;
    int winnerScore = ZERO;
    Player* playerWinner = nullptr;
    Player** players = gameboard->getPlayers();
    cout << "=== GAME OVER ===" << endl << endl;
    cout << "Final Scores:" << endl;
    for(int i = ZERO; i < MAX_PLAYERS; i++){
        Player* player = players[i];
        player->calculateTotalScore();
        if(player->getTotalScore() > winnerScore){
            playerWinner = player;
            winnerScore = player->getTotalScore();
        }
        else if(player->getTotalScore() == winnerScore){
            tie = true;
        }
        cout << "Player " << player->getPlayerName() << ": " << 
        player->getTotalScore() << endl;
    }
    if(tie){
        cout << "Players have tied" << endl;
    }else{
        cout << "Player " << playerWinner->getPlayerName() << " wins!" << endl;
    }

}
void GameEngine::readTileBag(string tileBag){
    bool checkIn = false;
    if(tileBag.length()-ONE != tileBagSize){
        std::cout << "Bag Invalid" << std::endl;
        throw std::exception();
    }
    else{
        for(long unsigned int i = ZERO; i<tileBag.length()-ONE; i++){
            checkIn = gameboard->addTileBag(tileBag[i]);
            if(checkIn == false){
                std::cout << "Bag Invalid" << std::endl;
                throw std::exception();
            }
        }
    }
}
Gameboard* GameEngine::getGameboard() {
    return gameboard;
}
InputProcessing* GameEngine::getInputProcessing() {
    return inputProcessing;
}
void GameEngine::setSeed(int seedIn){
    seed = seedIn;
}
