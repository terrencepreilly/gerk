#include <string>
#include <vector>
#include "key.h"
using namespace std;

#ifndef _LAYER_H
#define _LAYER_H

class Layer {
    private:
        vector<vector<Key *>> keys;
    public:

        /**
         * Create a new layer.
         *
         * Generates keys with the given values from the vector.
         *
         * Args:
         *      values: The values of the keys at the given positions.
         *
         */
        Layer(vector<vector<string>> values);

        Key * getKey(int r, int c);
        int getRowSize();
        int getColumnSize();
        /* The below setters return this, so they may be chained.*/
        Layer *setLayerSwitch(Layer *, int r, int c);
        Layer *setLayerTemporarySwitch(Layer *, int r, int c);
        void setKey(Key *key, int r, int c);
};

#endif
