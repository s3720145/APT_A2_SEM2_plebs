#ifndef GAMEBOARD
#define GAMEBOARD

#include "GenericLinkedList.h"
#include "Player.h"
#include <fstream>
#include <sstream>

#define NUM_PER_TILE    20
#define FACTORY_WIDTH   4
#define playerCount     2

using std::vector;
using std::stringstream;

class Gameboard {

public:
    Gameboard();
    ~Gameboard();

    void setTileBag();
    bool addTileBag(char c);
    void setFactories();
    void insertIntoCentreFactory(Tile* tile);

    // methods insert tiles from factories to player storage row
    // if storage_row is 0, insert into broken tiles
    bool FactoryTilesToPlayer(int factory_row, int storage_row, Colour colour);

    void addNewPlayer(string playerName);
    Player* getCurrentPlayer();
    Player** getPlayers();
    void setNextCurrentPlayer();

    bool isEndOfRound();
    void endRound();

    bool getIsFirstTurn();
    void setIsFirstTurn(bool isFirstTurn);

    string playerNamesToString();
    const string factoriesToString();

private:
    GenericLinkedList<Tile*>* tileBag;
    Player* players[playerCount];

    int centreFactorySize;
    vector<Tile*> centreFactory;
    Tile* factories[ARRAY_DIM][FACTORY_WIDTH];

    int playerAmount;
    int currentPlayerIter;

    bool isFirstTurn;
};

#endif // GAMEBOARD