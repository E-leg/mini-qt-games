#include "hexboard.h"
#include "game.h"

extern Game *game;

HexBoard::HexBoard()
{
}

QList<Hex *> HexBoard::getHexes() {
    return hexes;
}

void HexBoard::placeHexes(int x, int y, int cols, int rows) {
    int X_SHIFT = 82;
    int Y_SHIFT = 82;

    // Set columns
    for (int i=0; i<cols; i++){

        // Set rows
        for (int j=0; j<rows; j++) {
            int ALTERNATE_SHIFT = (Y_SHIFT/2)*(i%2);
            Hex *hex = new Hex();
            hex->setPos(x + X_SHIFT*i, y + Y_SHIFT*j + ALTERNATE_SHIFT);
            hexes.append(hex);
            game->scene->addItem(hex);

            // set hex parameters
            hex->setOwner(game->playerNone);
        }
    }
}
