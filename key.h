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

        static Key* temporaryDownKey(Layer *l, int r, int c) {
            Key * key = new Key(r, c, NULL);
            key->setLayer(l);
            key->setType(TEMP_DOWN);
            return key;
        }

        static Key* temporaryUpKey(Layer *l, int r, int c) {
            Key * key = new Key(r, c, NULL);
            key->setLayer(l);
            key->setType(TEMP_UP);
            return key;
        }

        static Key* downKey(Layer *l, int r, int c) {
            Key * key = new Key(r, c, NULL);
            key->setLayer(l);
            key->setType(DOWN);
            return key;
        }
        static Key* upKey(Layer *l, int r, int c) {
            Key * key = new Key(r, c, NULL);
            key->setLayer(l);
            key->setType(UP);
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
