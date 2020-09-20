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
}
bool Player::insertIntoMosaic(const int row_num, const Tile::Colour tile){
    bool success = false;
        int i =0;
        int j =0;
    if(row_num == 1){
        i = 0;
        j = ARRAY_DIM;
    }
    else if(row_num == 2){
        i = 1;
        j = ARRAY_DIM -1;
    }
    else if(row_num == 3){
        i = 2;
        j = ARRAY_DIM -2;
    }
    else if(row_num == 4){
        i = 3;
        j = ARRAY_DIM -3;
    }
    else if(row_num == 5){
        i = 4;
        j = ARRAY_DIM -4;
    }
    else if(row_num == 6){
        i = 5;
        j = ARRAY_DIM -5;
    }
    for(int k=ARRAY_DIM; k> j; k--){
       scoring[ARRAY_DIM-k] = static_cast<Tile::Colour>(k); 
    }
    for(int k = 0; k+i<ARRAY_DIM; k++){
       scoring[k+i] = static_cast<Tile::Colour>(k); 
    }
    for(int k=row_num; k<ARRAY_DIM; k++){
        if(scoring[k] == tile){
            if(mosaic[i][k] == Tile::Colour::NoTile){
                mosaic[i][k] = tile;
                success = true;
            }
            else{
                success = false;
            }
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