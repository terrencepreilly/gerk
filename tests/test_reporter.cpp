#include <string>
#include <iostream>
using namespace std;

#include "test_reporter.h"

void TestReporter::report(string value) {
    lastValueReported = value;
}
