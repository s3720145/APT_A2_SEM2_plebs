#ifndef INPUTPROCESSING
#define INPUTPROCESSING

#include "Gameboard.h"

class InputProcessing {
public:
    InputProcessing();
    ~InputProcessing();
    // checks if player move is valid
    bool processPlayerInput(string playerInput, Gameboard* gameboard);

    void saveGame(string fileName, Gameboard* gameboard);

    bool isAColour(char c);

private:
    vector<string> validTurns;
    int numValidTurns;
};

#endif // INPUTPROCESSING