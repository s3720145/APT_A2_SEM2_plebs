#ifndef GAMEBOARD
#define GAMEBOARD

#include "GenericLinkedList.h"
#include "Player.h"
#include <fstream>
#include <sstream>

#define NUM_PER_TILE    20
#define FACTORY_WIDTH   4
#define playerCount     2
#define NORMAL          0
#define GRAY            1
#define SIX_TILE        2

using std::vector;
using std::stringstream;

class Gameboard {

public:
    Gameboard();
    ~Gameboard();

    // generates the tile bag from DefaultTileBag.txt
    void setTileBag();
    // randomizes the bag depending on seed
    void randomizeTileBag(int seed, int mode);
    //adds a tile to the bag assuming its a char
    bool addTileBag(char c);

    // sets factories by pulling from tile bag
    void setFactories();

    // inserts a single tile into centre factory
    void insertIntoCentreFactory(Tile* tile);

    // methods insert tiles from factories to player storage row
    // if storage_row is 0, insert into broken tiles
    bool FactoryTilesToPlayer(int factory_row, int storage_row, Colour colour);

    // adds a new player into the gameboard
    void addNewPlayer(string playerName);

    // gets the curren player, or the player who's turn it currently is
    Player* getCurrentPlayer();

    // returns an array containing all players
    Player** getPlayers();

    // sets the player to the next current player
    void setNextCurrentPlayer();

    // checks end of round condition
    bool isEndOfRound();

    // ends round and cleans up
    void endRound();

    bool getIsFirstTurn();
    void setIsFirstTurn(bool isFirstTurn);

    // returns a string of all player names
    string playerNamesToString();

    // returns a string representation of all the factories
    const string factoriesToString();

private:
    GenericLinkedList<Tile*>* tileBag;
    Player* players[playerCount];

    int centreFactorySize;
    vector<Tile*> centreFactory;
    Tile* factories[ARRAY_DIM][FACTORY_WIDTH];
    vector<char> unShuffledBag;
    vector<char> shuffledBag;
    int playerAmount;
    int currentPlayerIter;

    bool isFirstTurn;
};

#endif // GAMEBOARD