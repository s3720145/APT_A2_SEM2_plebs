#include "Gameboard.h"
#include "GenericLinkedList.cpp"

template class GenericLinkedList<Player*>;

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
    std::cout << "test1" << std::flush;
    players->addToBack(new Player(playerName, score));
}

const Player* Gameboard::getCurrentPlayer() {
    return this->currentPlayer;
}

void Gameboard::setNextCurrentPlayer() {
    currentPlayer = players->removeHead()->value;
    players->addToBack(currentPlayer);
}

const string Gameboard::tileBagToString() {
    return nullptr;
}

const string Gameboard::centreFactoryToString() {
    return nullptr;
}

const string Gameboard::factoriesToString() {
    return nullptr;
}