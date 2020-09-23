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
            factories[row_num][col_num] = tileBag->removeHead();
        }
    }
}

void Gameboard::insertIntoCentreFactory(Tile* tile) {
    centreFactory.push_back(tile);
    centreFactorySize++;
}

bool Gameboard::FactoryTilesToPlayer(int factory_row, int storage_row, Colour colour) {
    bool operationSuccess = false;
    vector<Tile*> insertedTiles;
    int numInsertedTiles = 0;
    
    if(currentPlayer->cannotInsertIntoStorageRow(storage_row - 1, colour) == false) {
        if(factory_row == 0) {
            for(int i = 0; i < centreFactorySize; ++i) {
                if(centreFactory[i]->getColour() == colour) {
                    insertedTiles.push_back(centreFactory[i]);
                    centreFactory.erase(centreFactory.begin() + i);
                    ++numInsertedTiles;
                } else if(centreFactory[i]->getColour() == FIRST_PLAYER) {
                    currentPlayer->insertIntoBrokenTiles(centreFactory[i]);
                    centreFactory.erase(centreFactory.begin() + i);
                }
            }
        } else {
            for(int col_num = 0; col_num < FACTORY_WIDTH; ++col_num) {
                if(factories[factory_row - 1][col_num]->getColour() == colour) {
                    insertedTiles.push_back(factories[factory_row - 1][col_num]);
                    factories[factory_row - 1][col_num] = nullptr;
                    ++numInsertedTiles;
                } else {
                    insertIntoCentreFactory(factories[factory_row - 1][col_num]);
                    factories[factory_row - 1][col_num] = nullptr;
                }
            }
        }

        if(numInsertedTiles > 0) {
            currentPlayer->insertIntoStorageRow(storage_row - 1, numInsertedTiles, insertedTiles);
            operationSuccess = true;
        }
    }

    return operationSuccess;
}

void Gameboard::addNewPlayer(string playerName) {
    players->addToBack(new Player(playerName));
}

Player* Gameboard::getCurrentPlayer() {
    return this->currentPlayer;
}

void Gameboard::setNextCurrentPlayer() {
    currentPlayer = players->removeHead();
    players->addToBack(currentPlayer);
}

const string Gameboard::factoriesToString() {
    stringstream ss;

    ss << "0: ";
    for(Tile* tile : centreFactory) {
        ss << tile->getColourAsChar();
    }
    ss << '\n';

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