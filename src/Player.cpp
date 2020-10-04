#include "Player.h"
#include <iostream>

Player::Player(string playerName) {
    this->playerName = playerName;
    totalScore = 0;
    numBrokenTiles = 0;
    hasFirstPlayerTile = false;

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

// Checks if the tile is already placed in the desired mosaic row
bool Player::isInMosaicRow(const int row_num, Colour colour) {
    bool inMosaic = false;

    for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
        if(mosaic[row_num][col_num] != nullptr && mosaic[row_num][col_num]->getColourAsChar() == colour) {
            inMosaic = true;
        }
    }

    return inMosaic;
}

// returns false if we cannot insert even 1 tile into storage row
bool Player::cannotInsertIntoStorageRow(int row_num, Colour colour) {
    bool cannotInsert = false;

    if(storageRows[row_num][0] != nullptr && storageRows[row_num][0]->getColour() != colour) {
        cannotInsert = true;
    } else if(storageRows[row_num][row_num] != nullptr) {
        cannotInsert = true;
    } else if(isInMosaicRow(row_num, colour) == true) {
        cannotInsert = true;
    }

    return cannotInsert;
}

void Player::insertIntoMosaic(const int row_num, Tile* tile){
    int conseq_row = 0;
    int conseq_col = 0;
    int col_inserted = 0;
    int insertedTile = 0;
    int bothRowCol = 1;
    for(int col_num = 0; col_num < ARRAY_DIM; ++col_num) {
        if(tilePositions[row_num][col_num] == tolower(tile->getColourAsChar())) {
            mosaic[row_num][col_num] = tile;
            col_inserted = col_num;
            ++insertedTile;
        }
    }
    // scoring for every time you add a tile( consequtive tiles);
    if(col_inserted != ARRAY_DIM-1){
        for(int col_num = col_inserted+1; col_num<ARRAY_DIM; col_num++){
            if(mosaic[row_num][col_num] != nullptr){
                conseq_row++;
            }
            else{
                //skip the process
                col_num = ARRAY_DIM;
            }
        }
    }
    if(col_inserted != 0){
        for(int col_num = col_inserted-1; col_num> -1; col_num--){
            if(mosaic[row_num][col_num] != nullptr){
                conseq_row++;
            }
            else{
                //skip the process
                col_num = -1;
            }
        }
    }
    if(row_num != ARRAY_DIM-1){
        for(int curr_row_num = row_num + 1; curr_row_num<ARRAY_DIM; curr_row_num++){
            if(mosaic[curr_row_num][col_inserted] != nullptr){
                conseq_col++;
            }
            else{
                //skip the process
                curr_row_num = ARRAY_DIM;
            }
        }
    }
    if(row_num != 0){
        for(int curr_row_num = row_num - 1; curr_row_num> -1; curr_row_num--){
            if(mosaic[curr_row_num][col_inserted] != nullptr){
                conseq_col++;
            }
            else{
                //skip the process
                curr_row_num = -1;
            }
        }
    }
    if(conseq_col != 0 && conseq_row != 0){
        bothRowCol = 2;
    }
        std::cout << conseq_col << std::endl << conseq_row << std::endl << bothRowCol << std::endl;
        currRoundScore += conseq_col + conseq_row + bothRowCol;
}

bool Player::insertIntoStorageRow(const int row_num, int num_tiles, vector<Tile*> tiles) {
    bool insertSuccess = false;

    // for each tile being inserted
    for(int i = 0; i < num_tiles; ++i) {
        bool isTileInserted = false;
        // find a free spot in storage row (should at least be 1 free spot)
        for(int col_num = 0; col_num <= row_num && isTileInserted == false; ++col_num) {
            if(storageRows[row_num][col_num] == nullptr) {
                storageRows[row_num][col_num] = tiles[i];
                isTileInserted = true;
            }
        }

        if(isTileInserted == false) {
            insertIntoBrokenTiles(tiles[i]);
        }
    }

    return insertSuccess;
}

bool Player::insertIntoBrokenTiles(Tile* tile){
    bool insertSuccess = false;

    if(numBrokenTiles != BROKEN_TILES_MAX) {
        brokenTiles[numBrokenTiles] = tile;
        ++numBrokenTiles;
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

    calculateBrokenTiles();

    for(int i = 0; i < numBrokenTiles; i++){
        returningTiles.push_back(brokenTiles[i]);
        brokenTiles[i] = nullptr;
    }
    numBrokenTiles = 0;

    return returningTiles;
}

void Player::calculateBrokenTiles(){
    if(numBrokenTiles == 1){
        currRoundScore -= 1;
    }
    else if(numBrokenTiles == 2){
        currRoundScore -= 2;
    }
    else if(numBrokenTiles == 3){
        currRoundScore -= 4;
    }
    else if(numBrokenTiles == 4){
        currRoundScore -= 6;
    }
    else if(numBrokenTiles == 5){
        currRoundScore -= 8;
    }
    else if(numBrokenTiles == 6){
        currRoundScore -= 11;
    }
    else if(numBrokenTiles == 7){
        currRoundScore -= 14;
    }
    if(currRoundScore < 0){
        currRoundScore = 0;
    }
}
void Player::calculateTotalScore() {
    int endGameScore = 0;
    char tileTypesLowerCase[] = {'b','y','r','u','l'};
    //row full check
    for(int row_num = 0; row_num < ARRAY_DIM; row_num++){
        bool rowCheck = true;
        for(int col_num = 0; col_num < ARRAY_DIM; col_num++){
            if(mosaic[row_num][col_num] ==nullptr){
                rowCheck = false;
            }
        }
        if(rowCheck == true){
            endGameScore += 2;
        }
    }
    // coloumn full check
    for(int col_num = 0; col_num < ARRAY_DIM; col_num++){
        bool colCheck = true;
        for(int row_num = 0; row_num < ARRAY_DIM; row_num++){
            if(mosaic[row_num][col_num] ==nullptr){
                colCheck = false;
            }
        }
        if(colCheck == true){
            endGameScore += 7;
        }
    }
    // 5(or 6 for enhancment) of each colour check
    for(char tile : tileTypesLowerCase){
        int currColourAmount = 0;
        for(int row_num = 0; row_num<ARRAY_DIM; row_num++){
            for(int col_num = 0; col_num<ARRAY_DIM; col_num++){
                if(mosaic[row_num][col_num]->getColourAsChar() == tile){
                    currColourAmount++;
                }
            }
        }
        if(currColourAmount == 5){
            endGameScore += 10;
        }
    }

    totalScore = currRoundScore + endGameScore;
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

bool Player::getHasFirstPlayerTile() {
    return hasFirstPlayerTile;
}

void Player::setHasFirstPlayerTile(bool hasFirstPlayerTile) {
    this->hasFirstPlayerTile = hasFirstPlayerTile;
}

const string Player::playerBoardToString() {
    stringstream ss;
    
    ss << " Mosaic for " << playerName << ":\n";

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