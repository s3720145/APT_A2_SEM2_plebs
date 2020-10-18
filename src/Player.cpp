#include "Player.h"
#include <iostream>

Player::Player(string playerName, int mode) {
    this->playerName = playerName;
    modePlayed = mode;
    totalScore = ZERO;
    numBrokenTiles = ZERO;
    hasFirstPlayerTile = false;
    if(modePlayed == 6){
        BROKEN_TILES_MAX = 8;
        ARRAY_DIM = 6;
    }
    else{
        BROKEN_TILES_MAX = 7;
        ARRAY_DIM = 5;
    }
    mosaic = new Tile**[ARRAY_DIM];
    for(int row_num = ZERO; row_num < ARRAY_DIM; row_num++){
        mosaic[row_num]= new Tile*[ARRAY_DIM];
        for(int col_num = ZERO; col_num < ARRAY_DIM; col_num++){
            mosaic[row_num][col_num] = nullptr;
        }
    }
    tilePositions = new char*[ARRAY_DIM];
    for(int row_num = ZERO; row_num < ARRAY_DIM; row_num++){
        tilePositions[row_num]= new char[ARRAY_DIM];
    }
    setTilePositions();
    // creating a staggered array
    storageRows = new Tile**[ARRAY_DIM];
    for(int row_num = ZERO; row_num < ARRAY_DIM; row_num++){
        storageRows[row_num] = new Tile*[row_num + ONE];
        for(int i=0; i < row_num+1; i++){
            storageRows[row_num][i] = nullptr;
        }
    }
    brokenTiles = new Tile*[ARRAY_DIM];
}

Player::~Player(){
    //deconstruct the secondary part of the storage array (due to the fact i use new tile)
    
}
// sets where the tiles can be placed on the mosaic kind of like a bingo scoring sheet
void Player::setTilePositions() {
    char tileTypesLowerCase[] = {'b','y','r','u','l', 'o'};
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
    if(modePlayed == ONE){
        string playerInput;
        std::cin >> playerInput;
        manualInsert(row_num, tile, playerInput);
    } else{
    //Goes through all the possible positions for the tile (according to the tiling grid)
        for(int col_num = ZERO; col_num < ARRAY_DIM; ++col_num) {
            if(tilePositions[row_num][col_num] == tolower(tile->getColourAsChar())) 
            {
                mosaic[row_num][col_num] = tile;
                roundScoring(row_num, col_num);
            }
        }
    }
    
}
void Player::roundScoring(int row_num, int col_inserted){
    endOfGame = false;
    int conseq_row = ZERO;
    int conseq_col = ZERO;
    int bothRowCol = ONE;
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
    if(conseq_row + ONE == FIVE){
        endOfGame = true;
    }
}
void Player::manualInsert(const int row_num, Tile* tile, string playerInput){
        std::cout << "Player: " << playerName << std::endl;
        std::cout << "Row number: " << row_num << std::endl;
        std::cout << "Tile Colour: " << tile->getColourAsChar() << std::endl;

        
        vector<std::string> tokens;
        string token;
        int numTokens = ZERO;
        int colToInsert = ZERO;
        bool isValidTurn = false;
        std::istringstream tokenStream(playerInput);

        // splits string into tokens and place into vector
        while (getline(tokenStream, token, ' ')) {
            tokens.push_back(token);
            numTokens++;
        }
        if(numTokens == 2) {
            if(tokens[ZERO] == "save") {
            std::cout << "Cannot save while placing tiles, try again after. " << std::endl;
            isValidTurn = false;
            } else if(tokens[ZERO] == "place"){
                colToInsert = std::stoi(tokens[ONE]);
                isValidTurn = true;
            }else {
            isValidTurn = false;
            }
        }
        else{
            isValidTurn = false;
        }
        if(isValidTurn == false){
            std::cout << "Invalid Placement of Tile, please Try Again." << std::endl;
            manualInsert(row_num, tile, playerInput);
        }else{
            if(colToInsert >= 1 && colToInsert <= 5){
                if(mosaic[row_num][colToInsert] != nullptr) 
                {
                    mosaic[row_num][colToInsert] = tile;
                    roundScoring(row_num, colToInsert);
                }
                else{
                    std::cout << "There is already a tile there, please try a different position!" << std::endl;
                    manualInsert(row_num, tile, playerInput);
                }
            }
            else{
                std::cout << "Invalid Placement of Tile, please Try Again." << std::endl;
                manualInsert(row_num, tile, playerInput);
            }
        }
}
vector<Tile*> Player::insertIntoStorageRow(
    const int row_num, int num_tiles, vector<Tile*> tiles) {
    // for each tile being inserted
    bool insertSuccess = true;
    while(insertSuccess == true){
        // for(int i = ZERO; i < num_tiles; ++i) {
        bool isTileInserted = false;
        // find a free spot in storage row (should at least be ONE free spot)
        for(int col_num = ZERO; col_num <= row_num &&
         isTileInserted == false; ++col_num) {
            if(storageRows[row_num][col_num] == nullptr) {
                storageRows[row_num][col_num] = tiles[ZERO];
                tiles.erase(tiles.begin() + ZERO);
                isTileInserted = true;
            }
        }
        if(isTileInserted == false) {
            insertSuccess = insertIntoBrokenTiles(tiles[ZERO]);
            if(insertSuccess == true){
                tiles.erase(tiles.begin() + ZERO);
                num_tiles--;
            }
        }
        if(tiles.empty()){
            insertSuccess = true;
            insertSuccess = false;
        }
    }
    return tiles;
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
    else if(numBrokenTiles == EIGHT){
        currRoundScore -= EIGHTEEN;
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
                if(mosaic[row_num][col_num] != nullptr && 
                mosaic[row_num][col_num]->getColourAsChar() == tile){
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
    ss << " Mosaic for " << playerName << ":\n";

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
bool Player::getEnd(){
    return endOfGame;
}