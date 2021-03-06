#include "test_button.h"

TestButton::TestButton(int r, int c) :
    isFalling(false),
    isRising(false),
    updatesRun(false),
    Button(r, c) {}

bool TestButton::fallingEdge() {
    return isFalling;
}

bool TestButton::risingEdge() {
    return isRising;
}

void TestButton::setFalling() {
    isFalling = true;
    isRising = false;
}

void TestButton::setRising() {
    isRising = true;
    isFalling = false;
}

void TestButton::update() {
    updatesRun = true;
}


bool TestButton::getUpdatesRun() {
    return updatesRun;
}
