#include "GameEngine.h"

GameEngine::GameEngine() {
    gameboard = new Gameboard();
    inputProcessing = new InputProcessing();
    outputProcessing = new OutputProcessing();
}

GameEngine::~GameEngine() {

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
    cout << "Enter file name: " << endl;


}

void GameEngine::newRound() {
    // TODO:
    // Each round, whoever first chooses from the centre pile takes the first player marker, adds it to their floor
    // and will then be first player next round, at which point they will add it to the centre for someone to take the
    // following round.
    
    gameboard->setFactories();
    gameboard->setNextCurrentPlayer();

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

const Gameboard* GameEngine::getGameboard() {
    return this->gameboard;
}

