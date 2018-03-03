#include "key.h"

#ifndef _LAYER_H
#define _LAYER_H

class Layer {
    private:
        Key **keys;
        int rowSize;
        int colSize;
        void setKey(Key *);
    public:
        Layer(char **values, int rows, int columns);
        Key * getKey(int r, int c);
        int getRowSize();
        int getColumnSize();
        /* The below setters return this, so they may be chained.*/
        Layer *setLayerUp(Layer *, int r, int c);
        Layer *setLayerDown(Layer *, int r, int c);
        Layer *setLayerTemporaryUp(Layer *, int r, int c);
        Layer *setLayerTemporaryDown(Layer *, int r, int c);
};

#endif
