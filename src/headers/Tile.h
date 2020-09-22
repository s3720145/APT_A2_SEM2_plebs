#ifndef TILE_H
#define TILE_H

enum Colour {
    DARK_BLUE,
    YELLOW,
    RED,
    BLACK,
    LIGHT_BLUE,
    FIRST_PLAYER,
};

class Tile {
public:
    Tile(char colourAsChar);
    ~Tile();
    Colour getColour();
    char getColourAsChar();

private:
    Colour colour;
    char colourAsChar;
    bool isInMosaic;
};

#endif // TILE_H