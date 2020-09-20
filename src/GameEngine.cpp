#include "GameEngine.h"

GameEngine::GameEngine() {
    gameboard = new Gameboard();
    inputProcessing = new InputProcessing();
    outputProcessing = new OutputProcessing();
}

GameEngine::~GameEngine() {

}

void GameEngine::newGame() {
    //int numPlayers = 2;
    string playerName;
    Player* player1;
    Player* player2;

    cout << "Starting a New Game" << endl << endl;

    // for(int i = 1; i <= numPlayers; ++i) {
    //     cout << "Enter a name for player " << i << endl;
    //     cout << "> ";
    //     cin >> playerName;
    //     std::cout << "test0" << std::flush;
    //     //gameboard->addNewPlayer(playerName, 0);
    //     cout << endl << endl;
    // }

    cout << "Enter a name for player 1" << endl;
    cout << "> ";
    cin >> playerName;
    player1 = new Player(playerName, 0);

    cout << "Enter a name for player 2" << endl;
    cout << "> ";
    cin >> playerName;
    player2 = new Player(playerName, 0);

    //gameboard->setNextCurrentPlayer();

    cout << "Let's Play!"<< endl << endl;
    cout << "=== Start Round ===" << std::flush;



    // cout << player1->mosaicToString();
    cout << player1->storageRowsToString();
    // cout << "test" << std::flush;
    // cout << player1->brokenTilesToString();

    // cout << player2->storageRowsToString();
    // cout << player2->mosaicToString();
    // cout << player2->brokenTilesToString();
    
    newRound();

    cout << "TURN FOR PLAYER " << player1->getPlayerName();
    string playerInput;
    cin >> playerInput;

    cout << "TURN FOR PLAYER " << player2->getPlayerName();



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