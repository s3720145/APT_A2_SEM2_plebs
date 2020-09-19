#ifndef TILE
#define TILE

namespace Tile {
    enum Colour {
        Red,
        Yellow,
        DarkBlue,
        LightBlue,
        Black,
        FirstPlayer,
        NoTile
    };
    const char getColourAsChar(Colour colour);

    const int getColourAsInt(Colour colour);
};

#endif // TILE