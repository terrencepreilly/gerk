#include "board.h"

Board::Board(Layer *layer) {
    current = layer;
}

/* Execute all activated keys in this layer. */
void Board::runKeys() {
}
