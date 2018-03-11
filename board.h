#include <vector>

#include "layer.h"
#include "button.h"
#include "reporter.h"

#ifndef _BOARD_H
#define _BOARD_H

class Board {
    private:
        Layer *previous;
        Layer *current;
        Button **buttons;
        int rowSize;
        int colSize;
        Reporter *reporter;

    public:
        Board(Layer *current, Reporter *rep);

        Layer * getPreviousLayer();
        Layer * getCurrentLayer();

        Button * getButton(int r, int c);
        Board * setButton(int r, int c, Button *button);

        bool inTemporaryLayer();

        /* Execute all activated keys in this layer. */
        void runKeys();
};

#endif
