#ifndef PLAYER
#define PLAYER

#include "Tile.h"
#include <string>
#include <vector>
#include <sstream>

#define ZERO                0
#define ONE                 1
#define TWO                 2
#define THREE               3
#define FOUR                4
#define FIVE                5
#define SIX                 6
#define SEVEN               7
#define EIGHT               8
#define ELEVEN              11
#define FOURTEEN            14
#define EIGHTEEN            18
#define FULL_ROW            2
#define FULL_COL            7
#define FULL_COLOUR         10

using std::string;
using std::stringstream;
using std::vector;

class Player {
public:
    Player(string playerName, int mode);
    ~Player();

    void setTilePositions();
    bool isInMosaicRow(const int row_num, Colour colour);
    bool cannotInsertIntoStorageRow(int row_num, Colour colour);
    void insertIntoMosaic(const int row_num, Tile* tile);
    void roundScoring(int row_num, int col_inserted);
    void manualInsert(const int row_num, Tile* tile, string playerInput);
    vector<Tile*> insertIntoStorageRow(const int row_num, int num_tiles,
     vector<Tile*> tiles);
    bool insertIntoBrokenTiles(Tile* tile);
    vector<Tile*> cleanUp();
    void calculateBrokenTiles();
    void calculateTotalScore();

    string getPlayerName();
    const int getTotalScore();
    const int getCurrRoundScore();

    bool getHasFirstPlayerTile();
    void setHasFirstPlayerTile(bool hasFirstPlayerTile);

    const string playerBoardToString();
    bool getEnd();

private:
    string playerName;
    int totalScore;
    int currRoundScore;
    int numBrokenTiles;
    char** tilePositions;
    Tile*** mosaic;
    Tile*** storageRows;
    Tile** brokenTiles;
    bool hasFirstPlayerTile;
    int modePlayed;
    int ARRAY_DIM;
    int BROKEN_TILES_MAX;
    bool endOfGame;
};

#endif // PLAYER