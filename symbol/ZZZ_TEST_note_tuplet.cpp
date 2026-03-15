#define BOOST_TEST_MODULE TupletSymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "note.hpp"
#include "note_tuplet.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"

using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(TupletTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  Tuplet n1(1, 4, {"C4","8","G#5","8","Db3","8"}, 3);
  BOOST_TEST(n1.toString() == "Cn4,1/8,G#5,1/8,Db3,1/8, [1/4] [3]");
  std::vector<std::string> args;
  args.emplace_back("Cx6");
  args.emplace_back("16");
  args.emplace_back("DB5");
  args.emplace_back("16");
  args.emplace_back("C#4");
  args.emplace_back("8");
  args.emplace_back("D6");
  args.emplace_back("8");
  Tuplet n2 (1, 4, args, 3);
  BOOST_TEST(n2.toString() == "Cx6,1/16,DB5,1/16,C#4,1/8,Dn6,1/8, [1/4] [3]");
}

BOOST_AUTO_TEST_CASE(test_constr_throw) {
  BOOST_CHECK_THROW(Tuplet n0 (1, 4, {""}, 4),         std::invalid_argument);
  BOOST_CHECK_THROW(Tuplet n0 (1,2,{"Cn4","4","C"},4), std::invalid_argument);
  BOOST_CHECK_THROW(Tuplet n0 (1, 4, {""}, 4),        std::invalid_argument);
}

/*
BOOST_AUTO_TEST_CASE(test_tie) {
  Chord n1 ({"C4", "Bb4", "A4"}, 1,4);
  n1.setTied(1);
  BOOST_TEST(n1.isTied(0) == false);
  BOOST_TEST(n1.isTied(1) == true);
  BOOST_TEST(n1.isTied(2) == false);
  Chord n2 ({"C4", "Bb4", "A4"}, 1,4);
  n2.setTied();
  BOOST_TEST(n2.isTied(0) == true);
  BOOST_TEST(n2.isTied(1) == true);
  BOOST_TEST(n2.isTied(2) == true);
  Chord n3 ({"C4", "Bb4", "A4"}, 1,4);
  n3.setUntied();
  BOOST_TEST(n3.isTied(0) == false);
  BOOST_TEST(n3.isTied(1) == false);
  BOOST_TEST(n3.isTied(2) == false);
  n3.setTied(3); // out of range
  BOOST_TEST(n3.isTied(0) == false);
  BOOST_TEST(n3.isTied(1) == false);
  BOOST_TEST(n3.isTied(2) == false);
}

BOOST_AUTO_TEST_CASE(test_get_pitch) {
  Chord n1 ({"C#4", "Bb4", "A4"}, 1,4);
  BOOST_TEST(n1.getSize() == 3);
  BOOST_TEST(n1.getPitchSize() == 3);
  BOOST_TEST(n1.getPitch(0)->toString() == "C#4");
  BOOST_TEST(n1.getPitch(1)->toString() == "Bb4");
  BOOST_TEST(n1.getPitch(2)->toString() == "An4");
}

BOOST_AUTO_TEST_CASE(test_get) {
  Note * n1 = new Chord ({"C4", "G#5", "Db3"}, 1,4);
  BOOST_TEST(n1->getPitchSize() == 3);
  BOOST_TEST(n1->getPitch(1)->toString() == "G#5");
  BOOST_TEST(n1->isValid());
  delete n1;
}

BOOST_AUTO_TEST_CASE(test_property) {
  Chord n1 ({"C4", "G#5", "Db3"}, 1,4);
  n1.updateProperty("ABC");
  BOOST_TEST(n1.getPropertyStr() == "ABC");
  n1.updateProperty("");
  BOOST_TEST(!n1.hasProperty());
}

BOOST_AUTO_TEST_CASE(test_copy_constr) {
  Chord n1 ({"C4", "G#5", "Db3"}, 3,4);
  Chord n2 (n1);
  BOOST_TEST(n2.getPitch(0)->toString() == "Cn4");
  BOOST_TEST(n2.getPitch(1)->toString() == "G#5");
  BOOST_TEST(n2.getPitch(2)->toString() == "Db3");
  BOOST_TEST(n2.getDuration()->toString() == "3/4");
  BOOST_TEST(!n2.isTied(0));
  BOOST_TEST(!n2.isTied(1));
  BOOST_TEST(!n2.isTied(2));
  n1.setTied(1);
  Chord n3 (n1);
  BOOST_TEST(!n3.isTied(0));
  BOOST_TEST(n3.isTied(1));
  BOOST_TEST(!n3.isTied(2));
  n1.setTied(2);
  n1.updateProperty("hhha");
  BOOST_TEST(n1.hasProperty());
  Chord n4 = n1;
  BOOST_TEST(!n4.isTied(0));
  BOOST_TEST(n4.isTied(1));
  BOOST_TEST(n4.isTied(2));
  BOOST_TEST(n4.getPropertyStr() == "hhha");
}
*/

BOOST_AUTO_TEST_SUITE_END()