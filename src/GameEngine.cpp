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

    for(int i = 1; i <= MAX_PLAYERS; ++i) {
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
}

// TODO
void GameEngine::loadGame() {
    
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

    for(int i = 0; i < playerCount; ++i) {
        cout << players[i]->playerBoardToString() << endl;
        cout << "Current round score: " << players[i]->getCurrRoundScore() << endl << endl;
    }
    
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
        } catch(...) {}

        if(successfulTurn == false) {
            cout << "Turn unsuccessful, Please try again!" << endl;
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

