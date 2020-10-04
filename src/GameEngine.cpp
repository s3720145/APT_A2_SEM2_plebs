#include "GameEngine.h"

GameEngine::GameEngine() {
    gameboard = new Gameboard();
    inputProcessing = new InputProcessing();
}

GameEngine::~GameEngine() {
    gameboard->~Gameboard();
    inputProcessing->~InputProcessing();
}

void GameEngine::newGame() {
    cout << "Starting a New Game" << endl << endl;

    for(int i = 0; i < MAX_PLAYERS; ++i) {
        string playerName;
        cout << "Enter a name for player " << i << endl;
        cout << "> ";
        cin >> playerName;
        gameboard->addNewPlayer(playerName);
        cout << endl;
    }

    cout << "Let's Play!"<< endl << endl;

    gameboard->setTileBag();

    for(int i = 0; i < NUM_ROUNDS; ++i) {
        newRound();
    }
    
    //todo winner
}

void GameEngine::loadGame() {
    string input;
    char c;
    bool newRound = true;
    int roundPassed = 0;
    bool roundComplete = true;
    cout << "Enter file name: " << endl;
    cin >> input;
    std::ifstream file("src/Savefiles/" + input);
    if(file.is_open()) {
        while(tileBagSize>addedToBag && file >> c ) {
            readTileBag(c);
            addedToBag++;
        }
        getline(file, buffer);
        string buffer;
        cout << "Starting a New Game" << endl << endl;

        for(int i = 0; i < MAX_PLAYERS; ++i) {
            string playerName;
            cout << "Enter a name for player " << i << endl;
            cout << "> ";
            getline(file, playerName);
            gameboard->addNewPlayer(playerName);
            cout << endl;
        }
        cout << "Let's Play!"<< endl << endl;
        while (getline(file, turns)){
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
            roundComplete = false;
            // should never happen if save file has been tested and is correct, but just incase.
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
                    roundPassed++;
                    roundComplete = true;
                    cout << "=== END OF ROUND ===" << endl;
                }
            }
        }
        if(roundComplete == false){
            newPlayerTurn();
        }
        for(int i = roundPassed; i < NUM_ROUNDS; ++i) {
            newRound();
        }
        //todo winner
    }else {
        std::cout << "ERROR - CANNOT FIND - " << input << std::endl;
    }
    if(!file.eof() && file.fail()) {
        std::cout << "ERROR READING - " << input << std::endl;
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

    gameboard->endRound();

    cout << "=== END OF ROUND ===" << endl;
}

void GameEngine::newPlayerTurn() {
    string playerInput;
    bool successfulTurn = false;

    cout << "TURN FOR PLAYER: " << gameboard->getCurrentPlayer()->getPlayerName() << endl;
    cout << "Factories:" << endl;
    cout << gameboard->factoriesToString() << endl;
    cout << gameboard->getCurrentPlayer()->playerBoardToString() << endl << endl;

    do {
        cout << "> ";
        std::getline(cin >> std::ws, playerInput);

        if(!cin || playerInput == "quit") {
            throw std::exception();
        }

        try {
            successfulTurn = inputProcessing->processPlayerInput(playerInput, gameboard);
        } catch(...) {
            // cout << "Turn unsuccessful" << endl;
        }

        cin.clear();
    } while(successfulTurn == false);

    gameboard->setNextCurrentPlayer();
}

Gameboard* GameEngine::getGameboard() {
    return gameboard;
}
InputProcessing* GameEngine::getInputProcessing() {
    return inputProcessing;
}

