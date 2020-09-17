#ifndef PLAYER
#define PLAYER

#include "Tile.h"
#include <string>
#include <vector>

#define ARRAY_DIM           5
#define BROKEN_TILES_MAX    7
#define ROW_1_START         1
#define ROW_2_START         2
#define ROW_3_START         4
#define ROW_4_START         7
#define ROW_5_START         11

using std::string;
using std::vector;

class Player {
public:
    Player(string playerName, int totalScore);
    ~Player();

    void initialiseMosaic();
    bool insertIntoMosaic(const int row_num, const Tile::Colour tile);
    void initialiseStorageRows();
    bool insertIntoStorageRow(const int row_num, const Tile::Colour tile);
    bool insertIntoBrokenTiles(const Tile::Colour tile);

    const string getPlayerName();
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
    Tile::Colour mosaic[ARRAY_DIM][ARRAY_DIM];
    Tile::Colour** storageRows[ARRAY_DIM];
    Tile::Colour* brokenTiles[BROKEN_TILES_MAX];
};

#endif // PLAYER