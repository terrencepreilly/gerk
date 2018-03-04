#include <stdlib.h>
#include "layer.h"
#include "key.h"

Layer::Layer(char **values, int rows, int columns) {
    keys = (Key**) malloc(sizeof(Key) * rows * columns);
    rowSize = rows;
    colSize = columns;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            Key *key = new Key(row, col, values[row * rowSize + col]);
            setKey(key);
        }
    }
}


Key * Layer::getKey(int r, int c) {
    return keys[r * rowSize + c];
}

void Layer::setKey(Key * key) {
     keys[key->getRow() * rowSize + key->getColumn()] = key;
}

int Layer::getRowSize() {
    return rowSize;
}

int Layer::getColumnSize() {
    return colSize;
}

Layer * Layer::setLayerSwitch(Layer *layer, int r, int c) {
    Key *key = Key::switchKey(layer, r, c);
    key->setLayer(layer);
    setKey(key);
    return this;
}

Layer * Layer::setLayerTemporarySwitch(Layer *layer, int r, int c) {
    Key *key = Key::temporaryKey(layer, r, c);
    key->setLayer(layer);
    setKey(key);

    // Set the other layer automatically to ensure symmetry.
    Key *targetKey = Key::temporaryKey(this, r, c);
    targetKey->setLayer(this);
    layer->setKey(targetKey);

    return this;
}
