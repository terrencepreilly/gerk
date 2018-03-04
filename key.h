#include<stdio.h>

#include "key_type.h"

#ifndef _KEY_H
#define _KEY_H
class Layer;

class Key {
    private:
        int row;
        int column;
        const char * value;
        Layer *layer;
        KeyType type;
    public:
        Key(int r, int c, const char *val);

        static Key* temporaryKey(Layer *l, int r, int c) {
            Key * key = new Key(r, c, NULL);
            key->setLayer(l);
            key->setType(TEMPORARY);
            return key;
        }

        static Key* switchKey(Layer *l, int r, int c) {
            Key * key = new Key(r, c, NULL);
            key->setLayer(l);
            key->setType(SWITCH);
            return key;
        }

        bool isStatic();
        const char *getValue();
        void setLayer(Layer *l);
        Layer *getLayer();
        int getRow();
        int getColumn();
        void setType(KeyType t);
        KeyType getType();
};

#endif
