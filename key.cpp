#include <stdio.h>

#include "key.h"

Key::Key(int r, int c, const char *val) {
    value = val;
    row = r;
    column = c;
    type = VALUE;
}

bool Key::isStatic() {
    return value == NULL;
}

const char * Key::getValue() {
    return value;
}

void Key::setLayer(Layer *l) {
    layer = l;
}

Layer * Key::getLayer() {
    return layer;
}

int Key::getRow() {
    return row;
}

int Key::getColumn() {
    return column;
}

KeyType Key::getType() {
    return type;
}

void Key::setType(KeyType t) {
    type = t;
}
