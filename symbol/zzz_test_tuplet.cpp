#include "note_tuplet.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"

#include <cassert>
// #include <string>
#include <iomanip>
#include <iostream>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {

/* Test1: constructor */
// Create tuplet with a list of pitch-value pair (both str), then the note value
Tuplet * t1 = new Tuplet(1,4,{"C4","8","E4","8","G4","8"},3);
// must provide param pos to getPitch(), otherwise nullptr will be returned
assert(t1->getPitch(0)->toString() == "Cn4");
assert(t1->getPitch(1)->toString() == "En4");
assert(t1->getPitch(2)->toString() == "Gn4");
// getDuration() without param ==> the global value of the whole tuplet
assert(t1->getDuration()->toString() == "1/4");
// getDuration() with pos param ==> the n-th note's duration within the tuplet
assert(t1->getDuration(0)->toString() == "1/8");
assert(t1->getDuration(1)->toString() == "1/8");
assert(t1->getDuration(2)->toString() == "1/8");
PRINTL("[TEST1 PASSED]");

/* Test2: copy-constructor */
t1->setTied(2);
// update note property at pos 2
t1->updateProperty("pp",2);
assert(t1->getPropertyStr(2) == "pp");
// call copy constructor
Tuplet * t2 = new Tuplet(*t1);
// Copy-constructor should copy everything including property and ties
assert(t2->getPropertySize() == 3);
assert(t2->isTied(2));
assert(t2->getPropertyStr(2) == "pp");
PRINTL("[TEST2 PASSED]");
delete t1;
delete t2;

/* Test3: size checks */
t1 = new Tuplet(1,4,{"C4","16","C4","16","E4","8","G4","8"},3);
// getSize() returns the size of the divider (in this case is 3: one 1/4 note splited by three 1/8 notes)
assert(t1->getSize() == 3);
// but we have 4 notes here:
// C,1/16 - C,1/16 - E,1/8 - G,1/8
assert(t1->getPitchSize() == 4);
assert(t1->getDurationSize() == 4);
assert(t1->getPropertySize() == 4);
// check with hasXXX() method, e.g.
assert(t1->hasDuration(3));
assert(!t1->hasDuration(5));
// out of range means nullptr, e.g.
assert(t1->getPitch(10) == nullptr);
// Or simply check the integrety with isValid()
assert(t1->isValid());
PRINTL("[TEST3 PASSED]");

/* Test4: protected methods */
class TupletTest : public Tuplet {
public:
  TupletTest(const Tuplet& c) : Tuplet(c) {}
  virtual void setPitch(Pitch * __p, int pos) { Tuplet::setPitch(__p, pos); }
  virtual void setDuration(Duration *__d, int pos) { Tuplet::setDuration(__d, pos); }
  virtual void setProperty(Property *__p, int pos) { Tuplet::setProperty(__p, pos); }
  virtual Pitch * getPitchyMod(int pos) { return Tuplet::getPitchyMod(pos); }
  virtual Duration * getDurationMod(int pos) { return Tuplet::getDurationMod(pos); }
  virtual Property * getPropertyMod(int pos) { return Tuplet::getPropertyMod(pos); }
  virtual TupletTest& operator=(const TupletTest& __n) { return *this; }
  virtual Tuplet& operator=(const Tuplet& __n) { return *this; }
};
TupletTest tt = TupletTest(*t1);
delete t1;
Pitch * p = new Pitch('A','B',5);
Duration * d = new Duration(1,32);
Property * pp = new Property("fff");
// Before calling set method
assert(tt.getPitch(2)->toString() == "En4");
assert(tt.getDuration(2)->toString() == "1/8");
assert(tt.getPropertyStr(2).empty());
// calling set method (no need to worry about GC)
tt.setPitch(p, 2);
tt.setDuration(d, 2);
tt.setProperty(pp, 2);
// After set
assert(tt.getPitch(2)->toString() == "AB5");
assert(tt.getDuration(2)->toString() == "1/32");
assert(tt.getPropertyStr(2) == "fff");
// Erase property text
tt.setProperty(nullptr, 2);
assert(tt.getPropertyStr(2).empty());
PRINTL("[TEST4 PASSED]");

PRINTL("[ALL TESTS PASSED]");
return 0;
}
