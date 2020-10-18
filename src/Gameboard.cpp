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
        std::cout << "ERROR - CANNOT FIND - src/DefaultTileBag.txt" << std::endl;
    }

    if(!file.eof() && file.fail()) {
        std::cout << "ERROR READING - src/DefaultTileBag.txt" << std::endl;
    }

    file.close();
}
void Gameboard::randomizeTileBag(int seed, int mode){
    srand(seed);
    string tileTypes;
    int tileCount;
    int tileAmount = 20;
    int tileTotal;
    int counter = ZERO;
    if(mode == SIX_TILE){
        tileTypes = "UYBRLO";
        tileCount = 6;
        tileTotal = 120;
        ARRAY_DIM = 6;
    }
    else{
        tileTypes = "UYBRL";
        tileCount = 5;
        tileTotal = 100;
        ARRAY_DIM = 5;
    }
    factories = new Tile**[FIVE];
    for(int i = 0; i < ARRAY_DIM; i++){
        factories[i] = new Tile*[FACTORY_WIDTH];
    }
    for(int i=0; i<tileCount;i++){
        for(int j = 0; j < tileAmount; j++){
            char temp = tileTypes[i];
            unShuffledBag.push_back(temp);
        }
    }
    while(counter < tileTotal){
        int r = random()%(tileTotal - counter);
        shuffledBag.push_back(unShuffledBag[r]);
        unShuffledBag.erase(unShuffledBag.begin() + r);
        counter++;
    }
    std::ofstream defaultTileBag("src/DefaultTileBag.txt");
    string tileBagFinal;
    for(int i=0; i < tileTotal; i++){
        tileBagFinal += shuffledBag[i];
    }
    if(defaultTileBag.fail()) {
        std::cout << "TileBag file doesn't exist! please create one before continuing to play!(DefaultTileBag.txt)" << std::endl;
    } else {

        defaultTileBag << tileBagFinal;
    }

    defaultTileBag.close();

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
    
    for(int row_num = ZERO; row_num < FIVE; ++row_num) {
        for(int col_num = ZERO; col_num < FACTORY_WIDTH; ++col_num) {
            factories[row_num][col_num] = tileBag->removeHead();
        }
    }
}

void Gameboard::insertIntoCentreFactory(Tile* tile) {
    centreFactory.push_back(tile);
    centreFactorySize++;
}

bool Gameboard::FactoryTilesToPlayer(int factory_row, int storage_row, 
Colour colour) {
    bool operationSuccess = false;
    vector<Tile*> insertedTiles;
    int numInsertedTiles = ZERO;

    // if storage_row = 0 or it is possible to insert into a storage row
    if(storage_row == ZERO || players[currentPlayerIter]->
    cannotInsertIntoStorageRow(storage_row - 1, colour) == false) {
        if(factory_row == ZERO) {
            int counter = ZERO;
            // collect tiles of the desired colour from the centre factory
            while(counter < centreFactorySize) {
                if(centreFactory[counter]->getColour() == colour) {
                    insertedTiles.push_back(centreFactory[counter]);
                    centreFactory.erase(centreFactory.begin() + counter);
                    ++numInsertedTiles;
                    --centreFactorySize;
                } else if(centreFactory[counter]->getColour() == FIRST_PLAYER) {
                    players[currentPlayerIter]->
                    insertIntoBrokenTiles(centreFactory[counter]);
                    players[currentPlayerIter]->setHasFirstPlayerTile(true);
                    centreFactory.erase(centreFactory.begin() + counter);
                    --centreFactorySize;
                } else {
                    ++counter;
                }
            }
        } else if(factories[factory_row - 1][ZERO] != nullptr) {
            // else collect tiles from the specified factory
            for(int col_num = ZERO; col_num < FACTORY_WIDTH; ++col_num) {
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

        // if the number of tiles being inserted is larger than 0 attempt to insert into storage row
        if(numInsertedTiles > ZERO && storage_row != ZERO) {
            insertedTiles = 
            players[currentPlayerIter]->insertIntoStorageRow(storage_row - 1, numInsertedTiles, insertedTiles);
            operationSuccess = true;
        } else if(numInsertedTiles > ZERO && storage_row == ZERO) {
            // else if storage_row = 0 insert all tiles straight into broken tiles
            for(Tile* tile : insertedTiles) {
                if(players[currentPlayerIter]->insertIntoBrokenTiles(tile) == false) {
                    boxLid.push_back(tile);
                }
            }
            insertedTiles.clear();
            operationSuccess = true;
        }
    }

    return operationSuccess;
}

void Gameboard::addNewPlayer(string playerName, int arrayDim) {
    players[playerAmount] = new Player(playerName, arrayDim);
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
        currentPlayerIter = ZERO;
    }
}

bool Gameboard::isEndOfRound() {
    bool isEndOfRound = true;

    // check all factories if they are empty. If and only if all factories are empty is it considered the end of round
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
        boxLid.insert(boxLid.end(), returningTiles.begin(), returningTiles.end());
        if(players[i]->getHasFirstPlayerTile() == true) {
            currentPlayerIter = i;
            players[i]->setHasFirstPlayerTile(false);
        }

    }
    if(tileBag->getHead() == nullptr){
        int tileTotalAmount;
        if(ARRAY_DIM == 6){
            tileTotalAmount = 120;
        }
        else{
            tileTotalAmount = 100;
        }
        for(int i=0; i < tileTotalAmount; i++){
            int r = random()%(tileTotalAmount - i);
            tileBag->addToBack(boxLid[r]);
            boxLid.erase(boxLid.begin() + r);
        }
    }
    isFirstTurn = true;
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

    for(int row_num = ZERO; row_num < FIVE; ++row_num) {
        ss << row_num + 1 << ": ";
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