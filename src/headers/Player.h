#ifndef PLAYER
#define PLAYER

#include "Tile.h"
#include <string>
#include <vector>
#include <sstream>

#define ARRAY_DIM           5
#define BROKEN_TILES_MAX    7

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
    bool insertIntoStorageRow(const int row_num, Tile* tile);
    bool insertIntoBrokenTiles(Tile* tile);
    vector<Tile*> cleanUp();
    int calculateScore();

    string getPlayerName();
    const int getTotalScore();
    const int getCurrRoundScore();

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
};

#endif // PLAYER