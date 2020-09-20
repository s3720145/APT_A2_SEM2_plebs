#include "GameEngine.h"

GameEngine::GameEngine() {
    gameboard = new Gameboard();
    inputProcessing = new InputProcessing();
    outputProcessing = new OutputProcessing();
}

GameEngine::~GameEngine() {

}

void GameEngine::newGame() {
    int numPlayers = 2;
    string playerName;

    cout << "Starting a New Game" << endl << endl;

    for(int i = 1; i <= numPlayers; ++i) {
        cout << "Enter a name for player " << i << endl;
        cout << "> ";
        cin >> playerName;
        gameboard->addNewPlayer(playerName, 0);
        cout << endl << endl;
    }

    

}

void GameEngine::loadGame() {
}

void GameEngine::saveGame() {

}

void GameEngine::newRound() {

}

const Gameboard* GameEngine::getGameboard() {
    return this->gameboard;
}