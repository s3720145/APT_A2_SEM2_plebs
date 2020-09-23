#ifndef TILE_H
#define TILE_H

enum Colour {
    DARK_BLUE = 'B',
    YELLOW = 'Y',
    RED = 'R',
    BLACK = 'U',
    LIGHT_BLUE = 'L',
    FIRST_PLAYER = 'F',
};

class Tile {
public:
    Tile(char colourAsChar);
    // no need for move constructor as Tile only contains an enum
    ~Tile();
    Colour getColour();
    char getColourAsChar();

private:
    Colour colour;
};

#endif // TILE_H