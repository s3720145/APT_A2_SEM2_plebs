#include "Gameboard.h"
#include "GenericLinkedList.cpp"
#include "GenericNode.cpp"
#include "InputProcessing.h"

template class GenericLinkedList<Tile*>;
template class GenericNode<Tile*>;

Gameboard::Gameboard() {
    tileBag = new GenericLinkedList<Tile*>();
    playerAmount = 0;
    currentPlayerIter = 0;
    isFirstTurn = true;
}

Gameboard::~Gameboard() {
    tileBag->~GenericLinkedList();
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
    
    if(storage_row == 0 || players[currentPlayerIter]->cannotInsertIntoStorageRow(storage_row - 1, colour) == false) {
        if(factory_row == 0) {
            int counter = 0;
            while(counter < centreFactorySize) {
                if(centreFactory[counter]->getColour() == colour) {
                    insertedTiles.push_back(centreFactory[counter]);
                    centreFactory.erase(centreFactory.begin() + counter);
                    ++numInsertedTiles;
                    --centreFactorySize;
                } else if(centreFactory[counter]->getColour() == FIRST_PLAYER) {
                    players[currentPlayerIter]->insertIntoBrokenTiles(centreFactory[counter]);
                    players[currentPlayerIter]->setHasFirstPlayerTile(true);
                    centreFactory.erase(centreFactory.begin() + counter);
                    --centreFactorySize;
                } else {
                    ++counter;
                }
            }
        } else if(factories[factory_row - 1][0] != nullptr) {
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

        // if the number of tiles being inserted is larger than 0
        if(numInsertedTiles > 0) {
            players[currentPlayerIter]->insertIntoStorageRow(storage_row - 1, numInsertedTiles, insertedTiles);
            operationSuccess = true;
        } 
        // else {
        //     for(Tile* tile : insertedTiles) {
        //         players[currentPlayerIter]->insertIntoBrokenTiles(tile);
        //     }
        //     operationSuccess = true;
        // }
    }

    return operationSuccess;
}

void Gameboard::addNewPlayer(string playerName) {
    players[playerAmount] = new Player(playerName);
    playerAmount++;
}

Player* Gameboard::getCurrentPlayer() {
    return players[currentPlayerIter];
}

Player** Gameboard::getPlayers(){
    return players;
}

void Gameboard::setNextCurrentPlayer() {
    currentPlayerIter++;
    if(currentPlayerIter > playerCount-1){
        currentPlayerIter = 0;
    }
}

bool Gameboard::isEndOfRound() {
    bool isEndOfRound = true;

    if(centreFactorySize == 0) {
        for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
            for(int col_num = 0; col_num < FACTORY_WIDTH; ++col_num) {
                if(factories[row_num][col_num] != nullptr) {
                    isEndOfRound = false;
                }
            }
        }
    } else {
        isEndOfRound = false;
    }

    return isEndOfRound;
}

void Gameboard::endRound() {
    vector<Tile*> returningTiles;

    for(int i = 0; i < playerCount; ++i) {
        returningTiles = players[i]->cleanUp();

        for(Tile* tile : returningTiles) {
            tileBag->addToBack(tile);
        }

        if(players[i]->getHasFirstPlayerTile() == true) {
            currentPlayerIter = i;
            players[i]->setHasFirstPlayerTile(false);
        }
    }
}

bool Gameboard::getIsFirstTurn() {
    return isFirstTurn;
}

void Gameboard::setIsFirstTurn(bool isFirstTurn) {
    this->isFirstTurn = isFirstTurn;
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

string Gameboard::playerNamesToString() {
    stringstream ss;

    for(int i = 0; i < playerAmount; i++) {
        ss << players[i]->getPlayerName() << '\n';
    }

    return ss.str();
}