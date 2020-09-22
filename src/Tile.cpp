#include "Tile.h"

Tile::Tile(char colourAsChar) {
    if(colourAsChar == 'B') {
        colour = DARK_BLUE;
    } else if(colourAsChar == 'Y') {
        colour = YELLOW;
    } else if(colourAsChar == 'R') {
        colour = RED;
    } else if(colourAsChar == 'U') {
        colour = BLACK;
    } else if(colourAsChar == 'L') {
        colour = LIGHT_BLUE;
    } else {
        colour = FIRST_PLAYER;
    }

    this->colourAsChar = colourAsChar;
    isInMosaic = false;
}

Tile::~Tile() {

}

Colour Tile::getColour() {
    return colour;
}

char Tile::getColourAsChar(){
    return colourAsChar;
}