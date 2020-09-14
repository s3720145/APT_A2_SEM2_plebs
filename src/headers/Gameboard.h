#ifndef GAMEBOARD
#define GAMEBOARD

#include "SinglyLinkedList.h"
#include "Player.h"

using std::vector;

class Gameboard {

public:
    Gameboard();
    ~Gameboard();

    void initialiseTileBag();
    void initialiseTileBag(string tileBag);
    void initialiseCentreFactory();
    void setCentreFactory(string centreFactory);
    void initialiseFactories();
    void setFactories(string factories);

    void setPlayer1(string playerName, int totalScore);
    void setPlayer2(string playerName, int totalScore);
    const Player* getPlayer1();
    const Player* getPlayer2();
    void setCurrentPlayer();

    const string tileBagToString();
    const string centreFactoryToString();
    const string factoriesToString();

private:
    SinglyLinkedList* tileBag;

    vector<Tile::Colour> centreFactory;
    Tile::Colour factories[ARRAY_DIM][ARRAY_DIM];

    Player* player1;
    Player* player2;
    Player* currentPlayer;
};

#endif // GAMEBOARD