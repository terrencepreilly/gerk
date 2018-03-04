#ifndef _KEY_TYPE_H
#define _KEY_TYPE_H
/*
 * The activation type for a key.
 */
enum KeyType {
    // Output something to the keyboard.
    VALUE,
    // Change the layer temporarily.
    TEMPORARY,
    // Change layers.
    SWITCH,
};
#endif
