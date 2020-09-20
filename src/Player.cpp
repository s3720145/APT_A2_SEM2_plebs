#include "Player.h"

Player::Player(string playerName, int totalScore){
this->playerName = playerName;
this->totalScore = totalScore;
}

Player::~Player(){
    //deconstruct the secondary part of the storage array (due to the fact i use new tile)
    for(int i=0; i<ARRAY_DIM; i++){
        for(int j=0; j<i+1; j++){
            storageRows[i][j] = nullptr;
        }
    }
}

void Player::initialiseMosaic(){
    for(int i = 0; i<ARRAY_DIM; i++){
        for(int j = 0; j<ARRAY_DIM; j++){
            mosaic[i][j] = Tile::Colour::NoTile;
        }
    }
    initialiseScoring();
}

void Player::initialiseScoring(){
        for(int i=0; i<ARRAY_DIM; i++){
       scoring[i] = static_cast<Tile::Colour>(i); 
    }

    for(int i = 0; i < ARRAY_DIM; ++i) {
        int counter = 0;
        for(int j = ARRAY_DIM - i; j < ARRAY_DIM; j++) {
            scoringMosaic[i][counter] = scoring[j];
            counter++;
        }


        for(int j = 0; j < ARRAY_DIM - i; j++) {
            scoringMosaic[i][counter] = scoring[j];
            counter++;
        }
    }
}

bool Player::insertIntoMosaic(const int row_num, const Tile::Colour tile){
    bool success = false;
    for(int i=0; i<ARRAY_DIM; i++){
        if(scoringMosaic[row_num-1][i] == tile){
            mosaic[row_num-1][i] = tile;
            success = true;
        }
        else{
            success = false;
        }
    }
    return success;
}

void Player::initialiseStorageRows(){
    for(int i=0; i<ARRAY_DIM; i++){
        storageRows[i] = new Tile::Colour*[i+1];
        for(int j=0; j<i+1; j++){
            *storageRows[i][j] = Tile::Colour::NoTile;
        }
    }
}

bool Player::insertIntoStorageRow(const int row_num, const Tile::Colour tile){
    bool insertSuccess;
    if(*storageRows[row_num-1][0] == tile || *storageRows[row_num-1][0] == Tile::Colour::NoTile){
        //itterate through coloumn
        for(int i=0; i<row_num-1; i++){
            if(*storageRows[row_num-1][i] == Tile::Colour::NoTile && insertSuccess != true){
               *storageRows[row_num-1][i] = tile;
                insertSuccess = true; 
            }
        }
    }
    else{
        insertSuccess = false;
    }
    return insertSuccess;
}

bool Player::insertIntoBrokenTiles(const Tile::Colour tile){
    bool insertSuccess = false;
    for(int i=0; i<BROKEN_TILES_MAX; i++){
        if(brokenTiles[i] == nullptr && insertSuccess != true){
            *brokenTiles[i] = tile;
            insertSuccess = true;
        }
    }
    return insertSuccess;
}

const string Player::getPlayerName(){
    return playerName;
}

const int Player::getTotalScore(){
    return totalScore;
}

const int Player::getCurrRoundScore(){
    return currRoundScore;
}

const string Player::mosaicToString(){
    string output;
    for(int i=0; i < ARRAY_DIM; i++){
        for(int j=0; j<ARRAY_DIM; j++){
            output.push_back(getColourAsChar(mosaic[i][j]));
        }
    }
    return output;
}

const string Player::storageRowsToString(){
    string output;
    for(int i=0; i < ARRAY_DIM; i++){
        for(int j=0; j<i+1; j++){
            output.push_back(getColourAsChar(*storageRows[i][j]));
        }
    }
    return output;
}

const string Player::brokenTilesToString(){
    string output;
    for(int i=0; i < BROKEN_TILES_MAX; i++){
        output.push_back(getColourAsChar(*brokenTiles[i]));
    }
    return output;
}