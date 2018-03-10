#include "stdlib.h"
#include "board.h"

Board::Board(Layer *layer) {
    current = layer;
    rowSize = layer->getRowSize();
    colSize = layer->getColumnSize();
    buttons = (Button **) malloc(sizeof(Button) * rowSize * colSize);
}

Layer * Board::getPreviousLayer() {
    return previous;
}

Layer * Board::getCurrentLayer() {
    return current;
}

Button * Board::getButton(int r, int c) {
    int index = rowSize * r + c;
    return buttons[index];
}

Board * Board::setButton(int r, int c, Button *button) {
    int index = rowSize * r + c;
    buttons[index] = button;
    return this;
}

bool Board::inTemporaryLayer() {
    return previous != NULL;
}

/* Execute all activated keys in this layer. */
void Board::runKeys() {
    for (int rowIndex = 0; rowIndex < rowSize; rowIndex++) {
        for (int colIndex = 0; colIndex < colSize; colIndex++) {
            Button *button = getButton(rowIndex, colIndex);
            Key *key = current->getKey(rowIndex, colIndex);
            if (button->fallingEdge()) {
                switch (key->getType()) {
                    case VALUE:
                        break;
                    case TEMPORARY:
                        previous = current;
                        current = key->getLayer();
                        break;
                    case SWITCH:
                        current = key->getLayer();
                        break;
                    default:
                        break;
                }
            } else if (button->risingEdge() && key->getType() == TEMPORARY) {
                if (inTemporaryLayer()) {
                    current = previous;
                    previous = NULL;
                }
            }
        }
    }
}
