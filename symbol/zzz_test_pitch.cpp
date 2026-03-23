#include "pitch.hpp"

#include <cassert>
// #include <string>
#include <stdexcept>
#include <iostream>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {

Pitch * p1;
Pitch * p2;
Pitch * p3;

/* Test1: constructor */
// By default, middle octave
p1 = new Pitch('D');
assert(p1->toString() == "Dn4");
p2 = new Pitch('E', 'b', 3);
assert(p2->toString() == "Eb3");
p3 = new Pitch('F', 'x', 5);
assert(p3->toString() == "Fx5");
delete p1;
delete p2;
delete p3;
PRINTL("[TEST1 PASSED]");

/* Test2: constructor raise exception */
try {
  p1 = new Pitch('X');
}
catch (const std::invalid_argument& e) {
  std::string s(e.what());
  assert(!s.empty());
}
PRINTL("[TEST2 PASSED]");

/* Test3: copy constructor */
p1 = new Pitch('D');
p2 = new Pitch(*p1);
assert(p2->toString() == "Dn4");
delete p1;
delete p2;
PRINTL("[TEST3 PASSED]");

/* Test4: operators */
p1 = new Pitch('D');
p2 = new Pitch('D','n',4);
p3 = new Pitch('E','b',6);
assert(*p1 == *p2);
// p3 > p2 ==> p3 is a higher pitch than p2
assert(*p3 > *p2);
// p2 < p3 ==> p2 is a lower pitch than p3
assert(*p2 < *p3);
PRINTL("[TEST4 PASSED]");
delete p1;
delete p2;
delete p3;


PRINTL("[ALL TESTS PASSED]");
return 0;
}