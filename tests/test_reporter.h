#include "reporter.h"
#include <string>

#ifndef _TEST_REPORTER_H
#define _TEST_REPORTER_H

class TestReporter : public Reporter {
    public:
        std::string lastValueReported;
        void report(std::string value);
};

#endif
