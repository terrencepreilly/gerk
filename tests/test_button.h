#include "button.h"

#ifndef _TEST_BUTTON_H
#define _TEST_BUTTON_H

/* A mock button implementation for testing. */
class TestButton : public Button {
    private:
        bool isFalling;
        bool isRising;
    public:
        TestButton();
        TestButton(int r, int c);
        bool fallingEdge();
        bool risingEdge();
        void setFalling();
        void setRising();
};
#endif
