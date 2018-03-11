
#ifndef _REPORTER_H
#define _REPORTER_H
#include <string>

/* Abstract class which handles reporting key values on button presses. */
class Reporter {
    public:
        virtual void report(std::string value) = 0;
};

#endif
