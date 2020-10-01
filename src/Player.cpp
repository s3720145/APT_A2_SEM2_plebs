#include "Player.h"
#include <iostream>

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

bool Player::isInMosaicRow(const int row_num, Colour colour) {
    bool inMosaic = false;

    for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
        if(mosaic[row_num][col_num] != nullptr && mosaic[row_num][col_num]->getColourAsChar() == colour) {
            inMosaic = true;
        }
    }

    return inMosaic;
}

// returns false if we cannot insert even 1 tile
bool Player::cannotInsertIntoStorageRow(int row_num, Colour colour) {
    bool canInsert = false;

    if(storageRows[row_num][0] == nullptr || storageRows[row_num][0]->getColour() == colour) {
        canInsert = true;
    } else if(isInMosaicRow(row_num, colour) == false) {
        canInsert = true;
    }

    return canInsert;
}

void Player::insertIntoMosaic(const int row_num, Tile* tile){
    for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
        if(tilePositions[row_num][col_num] == tolower(tile->getColourAsChar())) {
            mosaic[row_num][col_num] = tile;
        }
    }

    // TODO SCORING CODE HERE
}

bool Player::insertIntoStorageRow(const int row_num, Tile* tile) {
    bool insertSuccess = false;
    for(int i = 0; i<row_num; i++){
        if(storageRows[row_num][i] == nullptr && i <= row_num) {
            storageRows[row_num][i] = tile;
            insertSuccess=true;
        } 
        else {
            insertSuccess = insertIntoBrokenTiles(tile);
        }
    }
    return insertSuccess;
}

bool Player::insertIntoBrokenTiles(Tile* tile){
    bool insertSuccess = false;

    if(numBrokenTiles != BROKEN_TILES_MAX) {
        brokenTiles[numBrokenTiles] = tile;
        ++numBrokenTiles;
        insertSuccess = true;
    }

    return insertSuccess;
}

vector<Tile*> Player::cleanUp() {
    //Tile** returningTiles = new Tile*[numBrokenTiles];
    vector<Tile*> returningTiles;

    // check if storage row is full
    for(int row_num = 0; row_num < ARRAY_DIM; ++row_num) {
        // inserts into mosaic when the row is full
        if(storageRows[row_num][row_num] != nullptr) {
            insertIntoMosaic(row_num, storageRows[row_num][row_num]);

            // sends rest of tiles in storage row to returningTiles
            for(int col_num = 0; col_num <= row_num; ++col_num) {
                returningTiles.push_back(storageRows[row_num][col_num]);
                storageRows[row_num][col_num] = nullptr;
            }
        }
    }

    for(int i = 0; i < numBrokenTiles; i++){
        returningTiles.push_back(brokenTiles[i]);
        brokenTiles[i] = nullptr;
    }
    numBrokenTiles = 0;

    return returningTiles;
}

// TODO
int Player::calculateScore() {
    int score = 0;

    return score;
}

string Player::getPlayerName() {
    return playerName;
}

const int Player::getTotalScore() {
    return totalScore;
}

const int Player::getCurrRoundScore() {
    return currRoundScore;
}

const string Player::playerBoardToString() {
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
                ss << storageRows[row_num][col_num]->getColourAsChar() << " ";
            }
        }

        // Prints the mosaic
        ss << "||";
        
        for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
            if(mosaic[row_num][col_num] != nullptr) {
                ss << " " << mosaic[row_num][col_num]->getColourAsChar();
            } else {
                ss << " .";
            }
        }
        
        ss << "\n";
    }

    ss << "broken: ";
    for(int i = 0; i < numBrokenTiles; i++) {
        ss << brokenTiles[i]->getColourAsChar() << " ";
    }

    return ss.str();
}