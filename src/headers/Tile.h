#ifndef TILE
#define TILE

namespace Tile {
    enum Colour {
        Red = 'R',
        Yellow = 'Y',
        DarkBlue = 'B',
        LightBlue = 'L',
        Black = 'U',
        FirstPlayer = 'F',
        NoTile = '.'
    };

    const char getColourAsChar(Colour colour);

    const int getColourAsInt(Colour colour);
};

#endif // TILE