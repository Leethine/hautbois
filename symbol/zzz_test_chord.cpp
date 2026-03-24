#include "note_chord.hpp"
#include "pitch.hpp"
#include "duration.hpp"

#include <cassert>
// #include <string>
#include <iostream>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {

/* Test1: constructor */
// Create chord with a list of pitch str, then duration num and duration denom
Chord * c1 = new Chord({"C4","E4","G4"},1,4);
Chord * c2 = new Chord({"A#3","Gx4"},1,4);
Chord * c3 = new Chord({"C4","E4","G4"},1,4);
assert(c1->toString() == "Cn4,En4,Gn4,1/4");
assert(c2->toString() == "A#3,Gx4,1/4");
assert(c3->toString() == "Cn4,En4,Gn4,1/4");
delete c2;
delete c3;
PRINTL("[TEST1 PASSED]");

/* Test2: copy-constructor */
c1->setTied(0);
c1->setTied(1);
c2 = new Chord(*c1);
assert(c2->isChord());
assert(c2->toString() == "Cn4,En4,Gn4,1/4");
// The ties should persist during copy
assert(c2->isTied(0));
assert(c2->isTied(1));
assert(!c2->isTied(2));
delete c2;
PRINTL("[TEST2 PASSED]");

/* Test3: get() */
// Chord only has one duration
assert(c1->getDurationSize() == 1);
// Pitch size reflects the number of pitches
assert(c1->getPitchSize() == 3);
// getPitch takes position as param, the same as isTied(), index start at 0
assert(c1->getPitch(1)->toString() == "En4");
PRINTL("[TEST3 PASSED]");

/* Test4: private methods */
class ChordTest : public Chord {
public:
  ChordTest(const Chord& c) : Chord(c) {}
  virtual void setPitch(Pitch * __p, int pos) { Chord::setPitch(__p, pos); }
  virtual void setDuration(Duration *__d, int pos) { Chord::setDuration(__d, -1); }
  virtual void setProperty(Property *__p, int pos) { Chord::setProperty(__p, -1); }
  virtual Pitch * getPitchyMod(int pos) { return Chord::getPitchyMod(pos); }
  virtual Duration * getDurationMod(int pos) { return Chord::getDurationMod(pos); }
  virtual Property * getPropertyMod(int pos) { return Chord::getPropertyMod(pos); }
  virtual ChordTest& operator=(const ChordTest& __n) { return *this; }
  virtual Chord& operator=(const Chord& __n) { return *this; }
  virtual bool hasPitch() const { return Chord::hasPitch(); }
  virtual bool hasPitch(size_t __pos) const { return Chord::hasPitch(__pos); }
};
ChordTest c4(*c1);
Pitch * p = c4.getPitchyMod(0);
assert(p->toString() == "Cn4");
Pitch * p_new = new Pitch('G', '#', 6);
// Setting pitch to p_new at pos == 1
// the GC of the old pitch is automated, no need to free it manually
c4.setPitch(p_new, 1);
// now, getPitch(1) should return the new pitch
assert(c4.hasPitch(1));
assert(c4.getPitch(1)->toString() == "G#6");
delete c1;
PRINTL("[TEST4 PASSED]");

PRINTL("[ALL TESTS PASSED]");

return 0;
}
