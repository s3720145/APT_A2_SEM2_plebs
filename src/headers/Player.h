#ifndef PLAYER
#define PLAYER

#include "Tile.h"
#include <string>
#include <vector>
#include <sstream>

#define ARRAY_DIM           5
#define BROKEN_TILES_MAX    7
#define ZERO                0
#define ONE                 1
#define MAX_FACTORY         5
#define MIN_STORAGE_ROW     1
#define MAX_STORAGE_ROW     5
#define TWO                 2
#define THREE               3
#define FOUR                4
#define FIVE                5
#define SIX                 6
#define SEVEN               7
#define EIGHT               8
#define ELEVEN              11
#define FOURTEEN            14
#define FULL_ROW            2
#define FULL_COL            7
#define FULL_COLOUR         10

using std::string;
using std::stringstream;
using std::vector;

class Player {
public:
    Player(string playerName);
    ~Player();

    void setTilePositions();
    bool isInMosaicRow(const int row_num, Colour colour);
    bool cannotInsertIntoStorageRow(int row_num, Colour colour);
    void insertIntoMosaic(const int row_num, Tile* tile);
    bool insertIntoStorageRow(const int row_num, int num_tiles,
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

private:
    string playerName;
    int totalScore;
    int currRoundScore;
    int numBrokenTiles;
    char tilePositions[ARRAY_DIM][ARRAY_DIM];
    Tile* mosaic[ARRAY_DIM][ARRAY_DIM];
    Tile** storageRows[ARRAY_DIM];
    Tile* brokenTiles[BROKEN_TILES_MAX];
    bool hasFirstPlayerTile;
};

#endif // PLAYER