#include <string>

#include "key.h"

Key::Key(string val) {
    value = val;
    type = VALUE;
}

bool Key::isStatic() {
    return value.empty();
}

std::string Key::getValue() {
    return value;
}

void Key::setLayer(Layer *l) {
    layer = l;
}

Layer * Key::getLayer() {
    return layer;
}

KeyType Key::getType() {
    return type;
}

void Key::setType(KeyType t) {
    type = t;
}
