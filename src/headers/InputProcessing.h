#ifndef INPUTPROCESSING
#define INPUTPROCESSING

#include "Player.h"

class InputProcessing {
public:
    InputProcessing();
    ~InputProcessing();
    // checks player input for errors
    bool errorCheck(string playerInput);
    // checks if player move is valid
    bool processPlayerInput(string playerInput, Player player);
private: 
};

#endif // INPUTPROCESSING