#include <string>

#include "key_type.h"

using namespace std;

#ifndef _KEY_H
#define _KEY_H
class Layer;

class Key {
    private:
        string value;
        Layer *layer;
        KeyType type;
    public:
        Key(string val);

        static Key* temporaryKey(Layer *l) {
            Key * key = new Key("");
            key->setLayer(l);
            key->setType(TEMPORARY);
            return key;
        }

        static Key* switchKey(Layer *l) {
            Key * key = new Key("");
            key->setLayer(l);
            key->setType(SWITCH);
            return key;
        }

        bool isStatic();
        string getValue();
        void setLayer(Layer *l);
        Layer *getLayer();
        void setType(KeyType t);
        KeyType getType();
};

#endif
