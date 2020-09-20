#include "Tile.h"

const char Tile::getColourAsChar(Colour colour){
    char colourChar;
    if(colour == Tile::Colour::Black){
        colourChar = 'U';
    }
    else if(colour == Tile::Colour::DarkBlue){
        colourChar = 'B';
    }
    else if(colour == Tile::Colour::LightBlue){
        colourChar = 'L';
    }
    else if(colour == Tile::Colour::Yellow){
        colourChar = 'Y';
    }
    else if(colour == Tile::Colour::Red){
        colourChar = 'R';
    }
    else if(colour == Tile::Colour::FirstPlayer){
        colourChar = 'F';
    }
    else if(colour == Tile::Colour::NoTile){
        colourChar = '.';
    }
    return colourChar;
}
const int Tile::getColourAsInt(Colour colour){
    int colourInt;
    if(colour == Tile::Colour::Black){
        colourInt = 5;
    }
    else if(colour == Tile::Colour::DarkBlue){
        colourInt = 3;
    }
    else if(colour == Tile::Colour::LightBlue){
        colourInt = 4;
    }
    else if(colour == Tile::Colour::Yellow){
        colourInt = 2;
    }
    else if(colour == Tile::Colour::Red){
        colourInt = 1;
    }
    else if(colour == Tile::Colour::FirstPlayer){
        colourInt = 0;
    }
    else if(colour == Tile::Colour::NoTile){
        colourInt = 9;
    }
    return colourInt;
}