#include "button.h"

Button::Button(int r, int c) : row(r), column(c) {}

int Button::getRow() {
    return row;
}

int Button::getColumn() {
    return column;
}
