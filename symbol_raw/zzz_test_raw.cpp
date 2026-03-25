#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <iostream>
#include <cassert>

#include "duration_raw.hpp"
#include "pitch_raw.hpp"
#include "property_raw.hpp"

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;

int main() {

/* TEST1: Duration */
// constructor test
DurationRaw d(1,4);
assert(d.getNum() == 1);
assert(d.getDenom() == 4);
d.setNum(3);
d.setDenom(8);
assert(d.getNum() == 3);
assert(d.getDenom() == 8);

// assignment test
DurationRaw d1(3,8);
DurationRaw d2 = d1;
assert(d2.getNum() == 3);
assert(d2.getDenom() == 8);

// serialization test
DurationRaw d3(7,16);
std::ofstream ofs1("cereal_object1");
{
  boost::archive::text_oarchive oa(ofs1);
  oa << d3;
}
DurationRaw d4;
{
  std::ifstream ifs("cereal_object1");
  boost::archive::text_iarchive ia(ifs);
  ia >> d4;
}
assert(d4.getNum() == 7);
assert(d4.getDenom() == 16);
PRINTL("[TEST1 PASSED]");

/* TEST2: Pitch */
PitchRaw p('C', 'n', 4);
assert(p.getName() == 'C');
assert(p.getAccidental() == 'n');
assert(p.getOctave() == 4);
p.setName('D');
p.setAccidental('s');
p.setOctave(5);
assert(p.getName() == 'D');
assert(p.getAccidental() == 's');
assert(p.getOctave() == 5);

PitchRaw p1('A', 'b', 5);
PitchRaw p2 = p1;
assert(p2.getName() == 'A');
assert(p2.getAccidental() == 'b');
assert(p2.getOctave() == 5);

PitchRaw p3('G', 'x', 6);
std::ofstream ofs2("cereal_object2");
{
  boost::archive::text_oarchive oa(ofs2);
  oa << p3;
}
PitchRaw p4;
{
  std::ifstream ifs("cereal_object2");
  boost::archive::text_iarchive ia(ifs);
  ia >> p4;
}
assert(p4.getName() == 'G');
assert(p4.getAccidental() == 'x');
assert(p4.getOctave() == 6);
PRINTL("[TEST2 PASSED]");

/* TEST3: Property */
PropertyRaw pp;
BOOST_ASSERT(!pp.hasValue());
std::string s ("test string");
pp.set(s.c_str());
BOOST_ASSERT(pp.hasValue());
assert(pp.getStr() == s);
assert(std::strcmp(s.c_str(),pp.get()) == 0);

PropertyRaw pp1;
std::string s1 ("test string eq eq");
pp1.set(s1);
PropertyRaw pp2 = pp1;
BOOST_ASSERT(pp2.hasValue());
assert(pp2.getStr() == s1);
assert(std::strcmp(s1.c_str(),pp2.get()) == 0);

PropertyRaw pp3;
std::string s2 ("test string string");
pp3.set(s2.c_str());
std::ofstream ofs3("cereal_object3");
{
  boost::archive::text_oarchive oa(ofs3);
  oa << pp3;
}
PropertyRaw pp4;
{
  std::ifstream ifs("cereal_object3");
  boost::archive::text_iarchive ia(ifs);
  ia >> pp4;
}
assert(pp4.hasValue());
assert(pp4.getStr() == s2);
PRINTL("[TEST3 PASSED]");

PRINTL("[ALL TESTS PASSED]");
return 0;
}