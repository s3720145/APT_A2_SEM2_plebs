#ifndef PLAYER
#define PLAYER

#include "Tile.h"
#include <string>
#include <vector>

#define ARRAY_DIM           5
#define BROKEN_TILES_MAX    7

using std::string;
using std::vector;

class Player {
public:
    Player(string playerName, int totalScore);
    ~Player();

    bool insertIntoMosaic(const int row_num, const Tile* tile);
    bool insertIntoStorageRow(const int row_num, Tile* tile);
    bool insertIntoBrokenTiles(Tile* tile);

    string getPlayerName();
    const int getTotalScore();
    const int getCurrRoundScore();

    const string mosaicToString();
    const string storageRowsToString();
    const string brokenTilesToString();

private:
    string playerName;
    int totalScore;
    int currRoundScore;
    int numBrokenTiles;
    Tile* mosaic[ARRAY_DIM][ARRAY_DIM];
    Tile** storageRows[ARRAY_DIM];
    Tile* brokenTiles[BROKEN_TILES_MAX];
};

#endif // PLAYER