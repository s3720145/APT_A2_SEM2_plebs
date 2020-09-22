#include "Player.h"

Player::Player(string playerName, int totalScore) {
    this->playerName = playerName;
    this->totalScore = totalScore;

    for(int i=0; i<ARRAY_DIM; i++){
        storageRows[i] = new Tile*[i + 1];
    }
}

Player::~Player(){
    //deconstruct the secondary part of the storage array (due to the fact i use new tile)
    
}

bool Player::insertIntoMosaic(const int row_num, const Tile* tile){
    bool success = false;
    
    return success;
}

bool Player::insertIntoStorageRow(const int row_num, Tile* tile){
    bool insertSuccess;
    if(storageRows[row_num-1][0] == tile || storageRows[row_num-1][0] == nullptr){
        //itterate through coloumn
        for(int i=0; i<row_num-1; i++){
            if(storageRows[row_num-1][i] == nullptr && insertSuccess != true){
               storageRows[row_num-1][i] = tile;
                insertSuccess = true; 
            }
        }
    }
    else{
        insertSuccess = false;
    }
    return insertSuccess;
}

bool Player::insertIntoBrokenTiles(Tile* tile){
    bool insertSuccess = false;
    for(int i=0; i<BROKEN_TILES_MAX; i++){
        if(brokenTiles[i] == nullptr && insertSuccess != true){
            brokenTiles[i] = tile;
            insertSuccess = true;
        }
    }
    return insertSuccess;
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

const string Player::mosaicToString(){
    string output = "";

    return output;
}

const string Player::storageRowsToString(){
    string output = "";
    
    return output;
}

const string Player::brokenTilesToString(){
    string output = "";
    
    return output;
}