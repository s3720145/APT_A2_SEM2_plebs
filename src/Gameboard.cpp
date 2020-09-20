#include "Gameboard.h"

Gameboard::Gameboard() {
    tileBag = new SinglyLinkedList();
    centreFactory.push_back(Tile::FirstPlayer);
    centreFactorySize = 1;
}

Gameboard::~Gameboard() {
    
}

void Gameboard::initialiseTileBag() {

}

void Gameboard::initialiseFactories() {

}

void Gameboard::addNewPlayer(string playerName, int score) {
    players[numPlayers] = new Player(playerName, score);
    numPlayers++;
}

const Player* Gameboard::getCurrentPlayer() {
    return this->currentPlayer;
}

void Gameboard::setNextCurrentPlayer() {
    if(currentPlayer == players[numPlayers]) {
        currentPlayer = player
    }
}

const string Gameboard::tileBagToString() {

}

const string Gameboard::centreFactoryToString() {

}

const string Gameboard::factoriesToString() {

}