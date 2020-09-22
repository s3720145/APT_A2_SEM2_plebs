#include "Gameboard.h"
#include "GenericLinkedList.cpp"
#include "GenericNode.cpp"

template class GenericLinkedList<Player*>;
template class GenericLinkedList<Tile*>;
template class GenericNode<Player*>;
template class GenericNode<Tile*>;

Gameboard::Gameboard() {
    tileBag = new GenericLinkedList<Tile*>();
    players = new GenericLinkedList<Player*>();
    currentPlayer = nullptr;
}

Gameboard::~Gameboard() {
    
}

void Gameboard::setTileBag() {
    std::ifstream file("src/DefaultTileBag.txt");
    char c;

    if(file.is_open()) {
        while(file >> c) {
            tileBag->addToBack(new Tile(c));
        }
    } else {
        std::cout << "ERROR - CANNOT FIND - src/DefaultTileBag.txt" << std::endl;
    }

    if(!file.eof() && file.fail()) {
        std::cout << "ERROR READING - src/DefaultTileBag.txt" << std::endl;
    }

    file.close();
}

void Gameboard::setFactories() {
    centreFactory.push_back(new Tile('F'));
    centreFactorySize = 1;
    
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = 0; col_num < FACTORY_WIDTH; ++col_num) {
            factories[row_num][col_num] = tileBag->removeHead()->getValue();
        }
    }
}

void Gameboard::addNewPlayer(string playerName, int score) {
    players->addToBack(new Player(playerName, score));
}

Player* Gameboard::getCurrentPlayer() {
    return this->currentPlayer;
}

void Gameboard::setNextCurrentPlayer() {
    currentPlayer = players->removeHead()->getValue();
    std::cout << currentPlayer->getPlayerName() << std::endl;
    players->addToBack(currentPlayer);
}

const string Gameboard::tileBagToString() {
    return nullptr;
}

const string Gameboard::centreFactoryToString() {
    std::stringstream ss;

    for(Tile* tile : centreFactory) {
        ss << tile->getColourAsChar();
    }

    return ss.str();
}

const string Gameboard::factoriesToString() {
    std::stringstream ss;

    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        ss << row_num + 1 << ": ";
        for(int col_num = 0; col_num < FACTORY_WIDTH; ++col_num) {
            if(factories[row_num][col_num] != nullptr) {
                ss << factories[row_num][col_num]->getColourAsChar();
            }
        }
        ss << '\n';
    }

    return ss.str();
}