#include "Player.h"
#include "Tile.cpp"

Player::Player(string playerName, int totalScore){
this->playerName = playerName;
this->totalScore = totalScore;
}
void Player::initialiseMosaic(){
    for(int i = 0; i<ARRAY_DIM; i++){
        for(int j = 0; j<ARRAY_DIM; j++){
            mosaic[i][j] = Tile::Colour::NoTile;
        }
    }
}
//todo insert logic and ask about how the 2D array is supposed to be organised if the mosaic needs results in lowercase and uppercase
bool insertIntoMosaic(const int row_num, const Tile::Colour tile){
    return false;
}
void Player::initialiseStorageRows(){
    for(int i=0; i<ARRAY_DIM; i++){
        storageRows[i] = new Tile::Colour*[i+1];
        for(int j=0; j<i+1; j++){
            *storageRows[i][j] = Tile::NoTile;
        }
    }
}
bool Player::insertIntoStorageRow(const int row_num, const Tile::Colour tile){
    bool insertSuccess;
    if(*storageRows[row_num-1][0] == tile || *storageRows[row_num-1][0] == Tile::Colour::NoTile){
        //itterate through coloumn
        for(int i=0; i<row_num; i++){
            if(*storageRows[row_num-1][i] == Tile::Colour::NoTile && insertSuccess != true){
               *storageRows[row_num-1][i] = tile;
                insertSuccess = true; 
            }
        }
        if(insertSuccess == false){
            insertSuccess = insertIntoBrokenTiles(tile);
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
    //ask what happens if broken tiles is overloaded.
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