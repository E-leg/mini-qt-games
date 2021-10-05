#ifndef HEXBOARD_H
#define HEXBOARD_H

#include "hex.h"

class HexBoard
{
public:
    HexBoard();

    // getters/setters
    QList<Hex*> getHexes();

    // public methods
    void placeHexes(int x, int y, int cols, int rows);

private:
    QList<Hex*> hexes;
};

#endif // HEXBOARD_H
