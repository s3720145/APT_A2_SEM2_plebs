#ifndef INPUTPROCESSING
#define INPUTPROCESSING

#include "Gameboard.h"

class InputProcessing {
public:
    InputProcessing();
    ~InputProcessing();

    // checks if player move is valid
    bool processPlayerInput(string playerInput, Gameboard* gameboard);

    // saves the current game state to a save file
    void saveGame(string fileName, Gameboard* gameboard);

    // checks if the char corresponds to an enum colour
    bool isAColour(char c);

private:
    vector<string> validTurns;
    int numValidTurns;
};

#endif // INPUTPROCESSING