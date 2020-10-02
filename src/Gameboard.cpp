#include "Gameboard.h"
#include "GenericLinkedList.cpp"
#include "GenericNode.cpp"
#include "InputProcessing.h"

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
    tileBag->~GenericLinkedList();
    players->~GenericLinkedList();
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
bool Gameboard::addTileBag(char c){
    bool output = false;
    InputProcessing* charCheck= new InputProcessing();
    if(charCheck->isAColour(c))
    {
        tileBag->addToBack(new Tile(c));
        output = true;
    }
    else{
        output = false;
    }
    return output;
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
    
    if(currentPlayer->cannotInsertIntoStorageRow(storage_row - 1, colour) == true) {
        if(factory_row == 0) {
            int counter = 0;
            while(counter < centreFactorySize) {
                if(centreFactory[counter]->getColour() == colour) {
                    insertedTiles.push_back(centreFactory[counter]);
                    centreFactory.erase(centreFactory.begin() + counter);
                    ++numInsertedTiles;
                    --centreFactorySize;
                } else if(centreFactory[counter]->getColour() == FIRST_PLAYER) {
                    insertedTiles.push_back(centreFactory[counter]);
                    centreFactory.erase(centreFactory.begin() + counter);
                    ++numInsertedTiles;
                    --centreFactorySize;
                } else {
                    ++counter;
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

        if(numInsertedTiles > 0 && storage_row != 0) {
            int counter1 = 0;
            while(numInsertedTiles > 0) {
                operationSuccess = currentPlayer->insertIntoStorageRow(storage_row, insertedTiles[counter1]);
                if(operationSuccess == true){
                    insertedTiles.erase(insertedTiles.begin() + counter1);
                    numInsertedTiles--;
                }
                else{
                    tileBag -> addToBack(insertedTiles[counter1]);
                    numInsertedTiles--;
                }
                counter1++;
            }
        } else {
            int counter1 = 0;
            while(numInsertedTiles > 0) {
                operationSuccess = currentPlayer->insertIntoBrokenTiles(insertedTiles[counter1]);
                if(operationSuccess == true){
                    insertedTiles.erase(insertedTiles.begin() + counter1);
                    numInsertedTiles--;
                }
                else{
                    tileBag -> addToBack(insertedTiles[counter1]);
                    numInsertedTiles--;
                }
                counter1++;
            }
        }
    }

    return operationSuccess;
}

void Gameboard::addNewPlayer(string playerName) {
    players->addToBack(new Player(playerName));
    playerNames.push_back(playerName);
}

Player* Gameboard::getCurrentPlayer() {
    return this->currentPlayer;
}
GenericLinkedList<Player*>* Gameboard::getPlayers(){
    return players;
}

void Gameboard::setNextCurrentPlayer() {
    currentPlayer = players->removeHead();
    players->addToBack(currentPlayer);
}

bool Gameboard::isEndOfRound() {
    //todo check if all factories are empty.
    return centreFactorySize == 0 ? true : false;
}

void Gameboard::endRound() {
    vector<Tile*> returningTiles;

    for(int i = 0; i < 2; ++i) {
        setNextCurrentPlayer();
        returningTiles = currentPlayer->cleanUp();
        for(Tile* tile : returningTiles) {
            tileBag->addToBack(tile);
        }
    }
    setNextCurrentPlayer();
}

string Gameboard::playerNamesToString() {
    stringstream ss;

    for(int i = 0; i < 2; ++i) {
        ss << playerNames[i] << '\n';
    }

    return ss.str();
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