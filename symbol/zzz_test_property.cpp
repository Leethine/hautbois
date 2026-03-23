#include "property.hpp"

#include <cassert>
// #include <string>
#include <iostream>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {


/* Test1: constructor */
Property p1;
std::string s = "trill";
Property p2 (s);
assert(p2.toString() == s);
assert(p2 == s);
assert(!p1.hasValue());
assert(p2.hasValue());

PRINTL("[TEST1 PASSED]");

PRINTL("[ALL TESTS PASSED]");

return 0;
}