#include "test_button.h"

TestButton::TestButton(int r, int c) : isFalling(false), isRising(false), Button(r, c) {}

bool TestButton::fallingEdge() {
    return isFalling;
}

bool TestButton::risingEdge() {
    return isRising;
}

void TestButton::setFalling() {
    isFalling = true;
}

void TestButton::setRising() {
    isRising = true;
}
