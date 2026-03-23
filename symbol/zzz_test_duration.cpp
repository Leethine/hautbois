#include "duration.hpp"

#include <cassert>
// #include <string>
#include <iostream>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {


/* Test 1 : constructor */
// Construct a Duration with num + denom, e.g. 1/2
Duration * d1 = new Duration(1,2);
assert(d1->toString() == "1/2");
// Construct a Duration with value + dots, e.g. "4." ==> 3/8
Duration * d2 = new Duration(4, ".");
assert(d2->toString() == "3/8");
// 8.. ==> 7/32
Duration * d3 = new Duration(8, "..");
assert(d3->toString() == "7/32");
// Construct a Duration with only denom value
Duration * d4 = new Duration(16);
assert(d4->toString() == "1/16");
delete d1;
delete d2;
delete d3;
PRINTL("[TEST1 PASSED]");

/* Test 2 : copy-constructor */
d1 = new Duration(*d4);
assert(d1->toString() == "1/16");
delete d1;
delete d4;
PRINTL("[TEST2 PASSED]");

/* Test 3 : comparison operators */
d1 = new Duration(1,2);
d2 = new Duration(1,4);
d3 = new Duration(1,8);
d4 = new Duration(1,4);
// d4 == d2 : two durations are the same value
assert(*d4 == *d2);
// d1 > d2 : d1 is longer than d2
assert(*d1 > *d2);
// d4 != d1 : not the same value
assert(*d4 != *d1);
// d3 < d2 : d3 is shorter than d2
assert(*d3 < *d2);
delete d1;
delete d2;
delete d3;
delete d4;

PRINTL("[TEST3 PASSED]");

/* Test 4 : +-x/ operators */
d1 = new Duration(1,2);
d2 = new Duration(1,4);
// d1 + d2 ==> 1/2 + 1/4 ==> 3/4
d3 = new Duration(*d1 + *d2);
assert(d3->toString() == "3/4");
// d1 - d2 ==> 1/2 - 1/4 ==> 1/4
d4 = new Duration(*d1 - *d2);
assert(d4->toString() == "1/4");
delete d3;
delete d4;
// division means shortening the duration value: d1 / 2 ==> 1/2 / 2 ==> 1/4
d3 = new Duration(*d1 / 2);
assert(d3->toString() == "1/4");
// multiplication means expanding the duration value: d2 / 2 ==> 1/4 x 2 ==> 1/2
d4 = new Duration(*d2 * 2);
assert(d4->toString() == "1/2");
delete d1;
delete d2;
delete d3;
delete d4;
d1 = new Duration(1,4);
d2 = new Duration(1,4);
// If d1 == d2, the - operator is invalid, nothing will be done
d3 = new Duration(*d1 - *d2);
assert(d3->toString() == "1/4");
delete d1;
delete d2;
delete d3;
PRINTL("[TEST4 PASSED]");

/* Test 5 : modification operators */
d1 = new Duration(1,2);
d2 = new Duration(1,4);
Duration D1(1,8);
D1 += *d2;
assert(D1.toString() == "3/8");
Duration D2(1,16);
D2 *= 2;
assert(D2.toString() == "1/8");
D2 /= 2;
assert(D2.toString() == "1/16");
D2 /= 0; // Nothing happens
assert(D2.toString() == "1/16");
delete d1;
delete d2;
PRINTL("[TEST5 PASSED]");

PRINTL("[ALL TESTS PASSED]");


return 0;
}