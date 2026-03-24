#include "note_single.hpp"
#include "pitch.hpp"
#include "duration.hpp"

#include <cassert>
// #include <string>
#include <iostream>
#include <stdexcept>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {

/* Test1: constructor */
// Create single note with pitch str, duration num, duration denom
SingleNote * n1 = new SingleNote("R",1,4);
SingleNote * n2 = new SingleNote("E5",1,4);
SingleNote * n3 = new SingleNote("Fx6",1,4);
SingleNote * n4 = new SingleNote("Eb3",1,4);
assert(n1->getPitch()->toString() == "R");
assert(n1->getDuration()->toString() == "1/4");
assert(n2->getPitch()->toString() == "En5");
assert(n3->getPitch()->toString() == "Fx6");
assert(n4->getPitch()->toString() == "Eb3");
assert(n1->isRest());
assert(n4->isSingle());
delete n1;
delete n2;
delete n3;
try {
  // Any constructor call with invalid pitch or duration will throw std::invalid_argument
  SingleNote * n5 = new SingleNote("Fss6",1,4);
  delete n5;
}
catch(const std::invalid_argument& e) {
  assert(e.what());
}
PRINTL("[TEST1 PASSED]");

/* Test2: copy-constructor */
// Setting note n4 as tied
n4->setTied();
assert(n4->isTied());
// The copy constructor should copy everything including the tie
n1 = new SingleNote(*n4);
assert(n1->isTied());
delete n1;
delete n4;
PRINTL("[TEST2 PASSED]");

/* Test3: update property */
n1 = new SingleNote("Eb3",1,4);
// The base class has no filter to properties
n1->updateProperty("hello");
assert(n1->getPropertyStr() == "hello");
assert(n1->toString() == "Eb3,1/4");
delete n1;
PRINTL("[TEST3 PASSED]");

PRINTL("[ALL TESTS PASSED]");

return 0;
}
