#ifndef _BUTTON_H
#define _BUTTON_H

class Button {
    private:
    protected:
        int row;
        int column;
    public:
        Button();
        Button(int r, int c);

        int getRow();
        int getColumn();

        // True if the button is rising.
        virtual bool risingEdge() = 0;

        // True if the button is falling.
        virtual bool fallingEdge() = 0;
};

#endif
