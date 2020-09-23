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
    gameboard->setFactories();
    gameboard->setNextCurrentPlayer();

    newRound();
}

void GameEngine::loadGame() {
}

void GameEngine::saveGame() {

}

void GameEngine::newRound() {
    cout << "=== Start Round ===" << endl;
    cout << "TURN FOR PLAYER: " << gameboard->getCurrentPlayer()->getPlayerName() << endl;
    cout << "Factories:" << endl;
    cout << gameboard->factoriesToString() << endl;
    cout << gameboard->getCurrentPlayer()->playerBoardToString() << endl;

    gameboard->FactoryTilesToPlayer(1, 1, BLACK);
    gameboard->FactoryTilesToPlayer(1, 1, BLACK);

    cout << gameboard->factoriesToString() << endl;
    cout << gameboard->getCurrentPlayer()->playerBoardToString() << endl;

    gameboard->FactoryTilesToPlayer(2, 3, DARK_BLUE);
    gameboard->FactoryTilesToPlayer(3, 3, LIGHT_BLUE);
    gameboard->FactoryTilesToPlayer(0, 5, RED);

    cout << gameboard->factoriesToString() << endl;
    cout << gameboard->getCurrentPlayer()->playerBoardToString() << endl;

    gameboard->getCurrentPlayer()->cleanUp();

    cout << gameboard->factoriesToString() << endl;
    cout << gameboard->getCurrentPlayer()->playerBoardToString() << endl;

}

const Gameboard* GameEngine::getGameboard() {
    return this->gameboard;
}