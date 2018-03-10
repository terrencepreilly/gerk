#include "layer.h"
#include "key.h"

Layer::Layer(vector<vector<string>> values) {
    keys = vector<vector<Key*>>();
    for (vector<vector<string>>::iterator rowIt = values.begin();
            rowIt != values.end(); rowIt++) {
        vector<Key *> keyRow;
        for (vector<string>::iterator colIt = rowIt->begin();
                colIt != rowIt->end(); colIt++) {
            Key *key = new Key(*colIt);
            keyRow.push_back(key);
        }
        keys.push_back(keyRow);
    }
}


Key * Layer::getKey(int r, int c) {
    return keys[r][c];
}

int Layer::getRowSize() {
    return keys.size();
}

int Layer::getColumnSize() {
    return keys.begin()->size();
}

Layer * Layer::setLayerSwitch(Layer *layer, int r, int c) {
    Key *key = Key::switchKey(layer);
    key->setLayer(layer);
    keys[r][c] = key;
    return this;
}

void Layer::setKey(Key *key, int r, int c) {
    keys[r][c] = key;
}

Layer * Layer::setLayerTemporarySwitch(Layer *layer, int r, int c) {
    Key *key = Key::temporaryKey(layer);
    key->setLayer(layer);
    keys[r][c] = key;

    // Set the other layer automatically to ensure symmetry.
    Key *targetKey = Key::temporaryKey(this);
    targetKey->setLayer(this);
    layer->setKey(targetKey, r, c);

    return this;
}
