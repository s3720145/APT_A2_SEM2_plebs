#include "Player.h"
#include <iostream>

Player::Player(string playerName) {
    this->playerName = playerName;
    totalScore = ZERO;
    numBrokenTiles = ZERO;
    hasFirstPlayerTile = false;

    setTilePositions();

    // creating a staggered array
    for(int row_num = ZERO; row_num < ARRAY_DIM; row_num++){
        storageRows[row_num] = new Tile*[row_num + ONE];
    }
}

Player::~Player(){
    //deconstruct the secondary part of the storage array (due to the fact i use new tile)
    
}
// sets where the tiles can be placed on the mosaic kind of like a bingo scoring sheet
void Player::setTilePositions() {
    char tileTypesLowerCase[] = {'b','y','r','u','l'};

    for(int row_num = ZERO; row_num < ARRAY_DIM; ++row_num) {
        int counter = ZERO;

        for(int col_num = ARRAY_DIM - row_num; col_num < ARRAY_DIM; col_num++) {
            tilePositions[row_num][counter] = tileTypesLowerCase[col_num];
            counter++;
        }

        for(int col_num = ZERO; col_num < ARRAY_DIM - row_num; col_num++) {
            tilePositions[row_num][counter] = tileTypesLowerCase[col_num];
            counter++;
        }
    }
}

// Checks if the tile is already placed in the desired mosaic row
bool Player::isInMosaicRow(const int row_num, Colour colour) {
    bool inMosaic = false;

    for(int col_num = ZERO; col_num < ARRAY_DIM; ++col_num) {
        if(mosaic[row_num][col_num] != nullptr && 
        mosaic[row_num][col_num]->getColourAsChar() == colour) {
            inMosaic = true;
        }
    }

    return inMosaic;
}

// returns false if we cannot insert even 1 tile into storage row
bool Player::cannotInsertIntoStorageRow(int row_num, Colour colour) {
    bool cannotInsert = false;

    if(storageRows[row_num][ZERO] != nullptr && 
    storageRows[row_num][ZERO]->getColour() != colour) {
        cannotInsert = true;
    } else if(storageRows[row_num][row_num] != nullptr) {
        cannotInsert = true;
    } else if(isInMosaicRow(row_num, colour) == true) {
        cannotInsert = true;
    }

    return cannotInsert;
}

void Player::insertIntoMosaic(const int row_num, Tile* tile){
    int conseq_row = ZERO;
    int conseq_col = ZERO;
    int col_inserted = ZERO;
    int bothRowCol = ONE;
    //Goes through all the possible positions for the tile (according to the tiling grid)
    for(int col_num = ZERO; col_num < ARRAY_DIM; ++col_num) {
        if(tilePositions[row_num][col_num] == tolower(tile->getColourAsChar())) 
        {
            mosaic[row_num][col_num] = tile;
            col_inserted = col_num;
        }
    }
    // scoring for every time you add a tile( consequtive tiles);
    // Row conseqeutive check
    if(col_inserted != ARRAY_DIM-ONE){
        for(int col_num = col_inserted+ONE; col_num<ARRAY_DIM; col_num++){
            if(mosaic[row_num][col_num] != nullptr){
                conseq_row++;
            }
            else{
                //skip the process
                col_num = ARRAY_DIM;
            }
        }
    }
    if(col_inserted != ZERO){
        for(int col_num = col_inserted-ONE; col_num> -ONE; col_num--){
            if(mosaic[row_num][col_num] != nullptr){
                conseq_row++;
            }
            else{
                //skip the process
                col_num = -ONE;
            }
        }
    }
    // Coloumn conseqeutive check
    if(row_num != ARRAY_DIM-ONE){

        for(int curr_row_num = row_num + ONE; curr_row_num<ARRAY_DIM;
         curr_row_num++){
            if(mosaic[curr_row_num][col_inserted] != nullptr){
                conseq_col++;
            }
            else{
                //skip the process
                curr_row_num = ARRAY_DIM;
            }
        }
    }
    if(row_num != ZERO){
        for(int curr_row_num = row_num - ONE; curr_row_num> -ONE;
         curr_row_num--){
            if(mosaic[curr_row_num][col_inserted] != nullptr){
                conseq_col++;
            }
            else{
                //skip the process
                curr_row_num = -ONE;
            }
        }
    }
    //if both row and coloumn have consequetives then due to the rules, both row and coloumn get added(the tile that got inserted gets double points)
    if(conseq_col != ZERO && conseq_row != ZERO){
        bothRowCol = TWO;
    }
    // adds the consequetive points for row and coloumn(both dont have a point for the tile itself) and then adds the Tile inserted points
        currRoundScore += conseq_col + conseq_row + bothRowCol;
}

bool Player::insertIntoStorageRow(
    const int row_num, int num_tiles, vector<Tile*> tiles) {
    bool insertSuccess = false;

    // for each tile being inserted
    for(int i = ZERO; i < num_tiles; ++i) {
        bool isTileInserted = false;
        // find a free spot in storage row (should at least be ONE free spot)
        for(int col_num = ZERO; col_num <= row_num &&
         isTileInserted == false; ++col_num) {
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
    for(int row_num = ZERO; row_num < ARRAY_DIM; ++row_num) {
        // inserts into mosaic when the row is full
        if(storageRows[row_num][row_num] != nullptr) {
            insertIntoMosaic(row_num, storageRows[row_num][row_num]);

            // sends rest of tiles in storage row to returningTiles
            for(int col_num = ZERO; col_num <= row_num; ++col_num) {
                returningTiles.push_back(storageRows[row_num][col_num]);
                storageRows[row_num][col_num] = nullptr;
            }
        }
    }

    calculateBrokenTiles();

    for(int i = ZERO; i < numBrokenTiles; i++){
        returningTiles.push_back(brokenTiles[i]);
        brokenTiles[i] = nullptr;
    }
    numBrokenTiles = ZERO;

    return returningTiles;
}

void Player::calculateBrokenTiles(){
    if(numBrokenTiles == ONE){
        currRoundScore -= ONE;
    }
    else if(numBrokenTiles == TWO){
        currRoundScore -= TWO;
    }
    else if(numBrokenTiles == THREE){
        currRoundScore -= FOUR;
    }
    else if(numBrokenTiles == FOUR){
        currRoundScore -= SIX;
    }
    else if(numBrokenTiles == FIVE){
        currRoundScore -= EIGHT;
    }
    else if(numBrokenTiles == SIX){
        currRoundScore -= ELEVEN;
    }
    else if(numBrokenTiles == SEVEN){
        currRoundScore -= FOURTEEN;
    }
    if(currRoundScore < ZERO){
        currRoundScore = ZERO;
    }
}
void Player::calculateTotalScore() {
    int endGameScore = ZERO;
    char tileTypesLowerCase[] = {'b','y','r','u','l'};
    //row full check
    for(int row_num = ZERO; row_num < ARRAY_DIM; row_num++){
        bool rowCheck = true;
        for(int col_num = ZERO; col_num < ARRAY_DIM; col_num++){
            if(mosaic[row_num][col_num] ==nullptr){
                rowCheck = false;
            }
        }
        if(rowCheck == true){
            endGameScore += FULL_ROW;
        }
    }
    // coloumn full check
    for(int col_num = ZERO; col_num < ARRAY_DIM; col_num++){
        bool colCheck = true;
        for(int row_num = ZERO; row_num < ARRAY_DIM; row_num++){
            if(mosaic[row_num][col_num] ==nullptr){
                colCheck = false;
            }
        }
        if(colCheck == true){
            endGameScore += FULL_COL;
        }
    }
    // 5(or 6 for enhancment) of each colour check
    for(char tile : tileTypesLowerCase){
        int currColourAmount = ZERO;
        for(int row_num = ZERO; row_num<ARRAY_DIM; row_num++){
            for(int col_num = ZERO; col_num<ARRAY_DIM; col_num++){
                if(mosaic[row_num][col_num]->getColourAsChar() == tile){
                    currColourAmount++;
                }
            }
        }
        if(currColourAmount == 5){
            endGameScore += FULL_COLOUR;
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
    
    ss << "Mosaic for " << playerName << ":\n";

    for(int row_num = ZERO; row_num < ARRAY_DIM; ++row_num) {
        ss << row_num + ONE << ": ";
        // Prints the storage rows
        for(int col_num = ONE; col_num < ARRAY_DIM - row_num ; ++col_num) {
            ss << "  ";
        }

        for(int col_num = row_num; col_num >= ZERO; --col_num) {
            if(storageRows[row_num][col_num] == nullptr) {
                ss << ". ";
            } else {
                ss << storageRows[row_num][col_num]->getColourAsChar() << " ";
            }
        }

        // Prints the mosaic
        ss << "||";
        
        for(int col_num = ZERO; col_num < ARRAY_DIM; ++col_num) {
            if(mosaic[row_num][col_num] != nullptr) {
                ss << " " << mosaic[row_num][col_num]->getColourAsChar();
            } else {
                ss << " .";
            }
        }
        
        ss << "\n";
    }

    ss << "broken: ";
    for(int i = ZERO; i < numBrokenTiles; i++) {
        ss << brokenTiles[i]->getColourAsChar() << " ";
    }

    return ss.str();
}