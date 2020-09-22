#include "Player.h"

Player::Player(string playerName) {
    this->playerName = playerName;
    totalScore = 0;
    numBrokenTiles = 0;

    setTilePositions();

    // creating a staggered array
    for(int row_num = 0; row_num < ARRAY_DIM; row_num++){
        storageRows[row_num] = new Tile*[row_num + 1];
    }
}

Player::~Player(){
    //deconstruct the secondary part of the storage array (due to the fact i use new tile)
    
}

void Player::setTilePositions() {
    char tileTypesLowerCase[] = {'b','y','r','u','l'};

    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        int counter = 0;

        for(int col_num = ARRAY_DIM - row_num; col_num < ARRAY_DIM; col_num++) {
            tilePositions[row_num][counter] = tileTypesLowerCase[col_num];
            counter++;
        }

        for(int col_num = 0; col_num < ARRAY_DIM - row_num; col_num++) {
            tilePositions[row_num][counter] = tileTypesLowerCase[col_num];
            counter++;
        }
    }
}

bool Player::isInMosaicRow(const int row_num, Tile* tile) {
    bool inMosaic = false;

    for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
        if(mosaic[row_num][col_num] != nullptr && mosaic[row_num][col_num]->getColourAsChar() == tile->getColourAsChar()) {
            inMosaic = true;
        }
    }

    return move(inMosaic);
}

void Player::insertIntoMosaic(const int row_num, Tile* tile){
    for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
        if(tilePositions[row_num][col_num] == tolower(tile->getColourAsChar())) {
            mosaic[row_num][col_num] = move(tile);
        }
    }

    // have to calculate score of the insert
}

bool Player::insertIntoStorageRow(const int row_num, Tile* tile){
    bool insertSuccess = false;

    if(isInMosaicRow(row_num, tile) == false) {
        if(storageRows[row_num][0] == nullptr) {
            storageRows[row_num][0] = move(tile);
            insertSuccess = true;
        } else if(storageRows[row_num][0]->getColourAsChar() == tile->getColourAsChar()) {
            for(int col_num = 1; col_num < row_num; ++col_num) {
                if(storageRows[row_num][col_num] == nullptr && insertSuccess == false) {
                    storageRows[row_num][col_num] = move(tile);
                    insertSuccess = true;
                }
            }
        }
    }
    
    return move(insertSuccess);
}

bool Player::insertIntoBrokenTiles(Tile* tile){
    bool insertSuccess = false;

    if(numBrokenTiles != BROKEN_TILES_MAX) {
        brokenTiles[numBrokenTiles] = move(tile);
        ++numBrokenTiles;
    }

    return move(insertSuccess);
}

Tile** Player::cleanUp() {
    Tile** returningTiles = new Tile*[numBrokenTiles];

    // check if storage row is full
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        if(storageRows[row_num][row_num] != nullptr) {
            // inserts into mosaic when the row is full
            insertIntoMosaic(row_num, move(storageRows[row_num][row_num]));

            // sends rest of tiles in storage row to returningTiles
            for(int col_num = 0; col_num < row_num - 1; ++col_num) {
                returningTiles[col_num] = move(storageRows[row_num][col_num]);
            }
        }
    }

    for(int i = 0; i < numBrokenTiles; i++){
        returningTiles[i] = move(brokenTiles[i]);
    }

    return move(returningTiles);
}

string Player::getPlayerName(){
    return playerName;
}

const int Player::getTotalScore(){
    return totalScore;
}

const int Player::getCurrRoundScore(){
    return currRoundScore;
}

const string Player::playerBoardToString(){
    stringstream ss;
    
    ss << "Mosaic for " << playerName << ":\n";

    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        ss << row_num + 1 << ": ";
        // Prints the storage rows
        for(int col_num = 1; col_num < ARRAY_DIM - row_num ; ++col_num) {
            ss << "  ";
        }

        for(int col_num = row_num; col_num >= 0; --col_num) {
            if(storageRows[row_num][col_num] == nullptr) {
                ss << ". ";
            } else {
                ss << storageRows[row_num][col_num]->getColourAsChar() << ' ';
            }
        }

        // Prints the mosaic
        ss << "||";
        
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            if(mosaic[row_num][col_num] != nullptr) {
                ss << ' ' << mosaic[row_num][col_num]->getColourAsChar();
            } else {
                ss << ' ' << tilePositions[row_num][col_num];
            }
        }
        
        ss << '\n';
    }

    ss << "broken: ";
    for(int i = 0; i < numBrokenTiles; i++) {
        ss << brokenTiles[i]->getColourAsChar() << " \n";
    }

    return ss.str();
}