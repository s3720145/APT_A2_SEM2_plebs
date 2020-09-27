#include "Tile.h"
#include <iostream>

Tile::Tile(char colourAsChar) {
    this->colour = (Colour) colourAsChar;
}

Tile::~Tile() {

}

Colour Tile::getColour() {
    return colour;
}

char Tile::getColourAsChar() {
    return colour;
}