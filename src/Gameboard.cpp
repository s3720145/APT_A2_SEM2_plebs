#include "Gameboard.h"
#include "GenericLinkedList.cpp"
#include "GenericNode.cpp"
#include "InputProcessing.h"

template class GenericLinkedList<Tile*>;
template class GenericNode<Tile*>;

Gameboard::Gameboard() {
    tileBag = new GenericLinkedList<Tile*>();
    playerAmount = ZERO;
    currentPlayerIter = ZERO;
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
        std::cout << "ERROR - CANNOT FIND - src/DefaultTileBag.txt" 
        << std::endl;
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
    charCheck->~InputProcessing();
    return output;
}

void Gameboard::setFactories() {
    centreFactory.push_back(new Tile('F'));
    centreFactorySize = ONE;
    
    for(int row_num = ZERO; row_num < ARRAY_DIM; ++row_num) {
        for(int col_num = ZERO; col_num < FACTORY_WIDTH; ++col_num) {
            factories[row_num][col_num] = tileBag->removeHead();
        }
    }
}

void Gameboard::insertIntoCentreFactory(Tile* tile) {
    centreFactory.push_back(tile);
    centreFactorySize++;
}

bool Gameboard::FactoryTilesToPlayer(
    int factory_row, int storage_row, Colour colour) {
    bool operationSuccess = false;
    vector<Tile*> insertedTiles;
    int numInsertedTiles = ZERO;
    
    if(storage_row == ZERO || 
    players[currentPlayerIter]->cannotInsertIntoStorageRow(
        storage_row - 1, colour) == false) {
        if(factory_row == ZERO) {
            int counter = ZERO;
            while(counter < centreFactorySize) {
                if(centreFactory[counter]->getColour() == colour) {
                    insertedTiles.push_back(centreFactory[counter]);
                    centreFactory.erase(centreFactory.begin() + counter);
                    ++numInsertedTiles;
                    --centreFactorySize;
                } else if(centreFactory[counter]->getColour() == FIRST_PLAYER) {
                    players[currentPlayerIter]->insertIntoBrokenTiles(
                        centreFactory[counter]);
                    players[currentPlayerIter]->setHasFirstPlayerTile(true);
                    centreFactory.erase(centreFactory.begin() + counter);
                    --centreFactorySize;
                } else {
                    ++counter;
                }
            }
        } else if(factories[factory_row - ONE][ZERO] != nullptr) {
            for(int col_num = ZERO; col_num < FACTORY_WIDTH; ++col_num) {
                if(factories[factory_row - ONE][col_num]->getColour() == colour)
                 {
                    insertedTiles.push_back(
                        factories[factory_row - ONE][col_num]);
                    factories[factory_row - ONE][col_num] = nullptr;
                    ++numInsertedTiles;
                } else {
                    insertIntoCentreFactory(
                        factories[factory_row - ONE][col_num]);
                    factories[factory_row - ONE][col_num] = nullptr;
                }
            }
        }

        // if the number of tiles being inserted is larger than 0
        if(numInsertedTiles > ZERO) {
            players[currentPlayerIter]->insertIntoStorageRow(
                storage_row - ONE,numInsertedTiles, insertedTiles);
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
    if(currentPlayerIter > playerCount-ONE){
        currentPlayerIter = ZERO;
    }
}

bool Gameboard::isEndOfRound() {
    bool isEndOfRound = true;

    if(centreFactorySize == ZERO) {
        for(int row_num = ZERO; row_num < ARRAY_DIM; ++row_num) {
            for(int col_num = ZERO; col_num < FACTORY_WIDTH; ++col_num) {
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

    for(int i = ZERO; i < playerCount; ++i) {
        returningTiles = players[i]->cleanUp();

        for(Tile* tile : returningTiles) {
            tileBag->addToBack(tile);
        }

        if(players[i]->getHasFirstPlayerTile() == true) {
            currentPlayerIter = i;
            players[i]->setHasFirstPlayerTile(false);
            std::cout << (players[i] != getCurrentPlayer()) <<std::endl;
            if(players[i] != getCurrentPlayer()){
                setNextCurrentPlayer();
            }
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

    for(int row_num = ZERO; row_num < ARRAY_DIM; ++row_num) {
        ss << row_num + ONE << ": ";
        for(int col_num = ZERO; col_num < FACTORY_WIDTH; ++col_num) {
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

    for(int i = ZERO; i < playerAmount; i++) {
        ss << players[i]->getPlayerName() << '\n';
    }

    return ss.str();
}