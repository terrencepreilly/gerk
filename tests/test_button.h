#include "button.h"

#ifndef _TEST_BUTTON_H
#define _TEST_BUTTON_H

/* A mock button implementation for testing. */
class TestButton : public Button {
    private:
        bool isFalling;
        bool isRising;
        bool updatesRun;
    public:
        TestButton();
        TestButton(int r, int c);
        bool fallingEdge();
        bool risingEdge();
        void update();
        void setFalling();
        void setRising();
        bool getUpdatesRun();
};
#endif
