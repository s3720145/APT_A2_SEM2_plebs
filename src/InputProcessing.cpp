#include "InputProcessing.h"

InputProcessing::InputProcessing() {

}

InputProcessing::~InputProcessing() {

}

bool InputProcessing::errorCheck(string playerInput) {
    return true;
}

bool InputProcessing::processPlayerInput(string playerInput, Player player) {
    bool isValidMove;

    if(errorCheck(playerInput) == false) {
        isValidMove = false;
    } else {
        isValidMove = true;
    }

    return isValidMove;
}