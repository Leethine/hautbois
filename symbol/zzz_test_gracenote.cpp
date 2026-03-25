#include "note_grace.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"

#include <cassert>
// #include <string>
#include <iostream>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {

/* Test1: constructor */
// Create GraceNote note with a main duration/pitch, then the list of pitch-value pair (both str),
GraceNote * g1 = new GraceNote(1,4,"D4", {"C4","16","C#4","16"});
// must provide param pos to getPitch(), otherwise nullptr will be returned
assert(g1->getPitch(0)->toString() == "Cn4");
assert(g1->getPitch(1)->toString() == "C#4");
// getPitch without any param ==> the main pitch
assert(g1->getPitch()->toString() == "Dn4");
// getDuration() without param ==> the main duration
assert(g1->getDuration()->toString() == "1/4");
// getDuration() with pos param ==> the n-th note's duration within the GraceNote
assert(g1->getDuration(0)->toString() == "1/16");
assert(g1->getDuration(1)->toString() == "1/16");
PRINTL("[TEST1 PASSED]");

/* Test2: copy-constructor */
g1->setTied(1);
// update note property at pos 2
g1->updateProperty("pp",1);
assert(g1->getPropertyStr(1) == "pp");
// call copy constructor
GraceNote * g2 = new GraceNote(*g1);
// Copy-constructor should copy everything including property and ties
assert(g2->getPropertySize() == 2);
assert(g2->isTied(1));
assert(g2->getPropertyStr(1) == "pp");
PRINTL("[TEST2 PASSED]");
delete g1;
delete g2;

/* Test3: size checks */
g1 = new GraceNote(1,4,"F4",{"C4","16","D4","16","E4","8"});
assert(g1->getPitchSize() == 3);
assert(g1->getDurationSize() == 3);
assert(g1->getPropertySize() == 3);
// check with hasXXX() method, e.g.
assert(g1->hasDuration(2));
assert(!g1->hasDuration(5));
// out of range means nullptr, e.g.
assert(g1->getPitch(10) == nullptr);
// Or simply check the integrety with isValid()
assert(g1->isValid());
PRINTL("[TEST3 PASSED]");

/* Test4: protected methods */
class GraceNoteTest : public GraceNote {
public:
  GraceNoteTest(const GraceNote& c) : GraceNote(c) {}
  virtual void setPitch(Pitch * __p, int pos) { GraceNote::setPitch(__p, pos); }
  virtual void setDuration(Duration *__d, int pos) { GraceNote::setDuration(__d, pos); }
  virtual void setProperty(Property *__p, int pos) { GraceNote::setProperty(__p, pos); }
  virtual Pitch * getPitchyMod(int pos) { return GraceNote::getPitchyMod(pos); }
  virtual Duration * getDurationMod(int pos) { return GraceNote::getDurationMod(pos); }
  virtual Property * getPropertyMod(int pos) { return GraceNote::getPropertyMod(pos); }
  virtual GraceNoteTest& operator=(const GraceNoteTest& __n) { return *this; }
  virtual GraceNote& operator=(const GraceNote& __n) { return *this; }
};
GraceNoteTest g = GraceNoteTest(*g1);
delete g1;
Pitch * p = new Pitch('A','B',5);
Duration * d = new Duration(1,32);
Property * pp = new Property("fff");
// Before calling set method
assert(g.getPitch(2)->toString() == "En4");
assert(g.getDuration(2)->toString() == "1/8");
assert(g.getPropertyStr(2).empty());
// calling set method (no need to worry about GC)
g.setPitch(p, 2);
g.setDuration(d, 2);
g.setProperty(pp, 2);
// After set
assert(g.getPitch(2)->toString() == "AB5");
assert(g.getDuration(2)->toString() == "1/32");
assert(g.getPropertyStr(2) == "fff");
// Erase property text
g.setProperty(nullptr, 2);
assert(g.getPropertyStr(2).empty());
PRINTL("[TEST4 PASSED]");

PRINTL("[ALL TESTS PASSED]");
return 0;
}
