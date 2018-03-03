#include "layer.h"

#ifndef _BOARD_H
#define _BOARD_H

class Board {
    private:
        Layer *previous;
        Layer *current;
    public:
        Board(Layer *current);

        /* Execute all activated keys in this layer. */
        void runKeys();
};

#endif
