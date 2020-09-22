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

    for(int i = 1; i <= 4; ++i) {
        string playerName;
        cout << "Enter a name for player " << i << endl;
        cout << "> ";
        cin >> playerName;
        gameboard->addNewPlayer(playerName, 0);
        cout << endl;
    }

    cout << "Let's Play!"<< endl << endl;

    gameboard->setNextCurrentPlayer();

    newRound();
}

void GameEngine::loadGame() {
}

void GameEngine::saveGame() {

}

void GameEngine::newRound() {
    gameboard->setTileBag();
    gameboard->setFactories();

    cout << "=== Start Round ===" << endl;
    cout << "TURN FOR PLAYER: " << gameboard->getCurrentPlayer()->getPlayerName() << endl;
    cout << "Factories:" << endl;
    cout << gameboard->centreFactoryToString() << endl;
    cout << gameboard->factoriesToString() << endl;

}

const Gameboard* GameEngine::getGameboard() {
    return this->gameboard;
}