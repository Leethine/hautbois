#define BOOST_TEST_MODULE ChordSymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "note.hpp"
#include "note_chord.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"

using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(ChordTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  Chord n1({"C4", "G#5", "Db3"}, 1,4);
  BOOST_TEST(n1.toString() == "Cn4,G#5,Db3,1/4");
  std::vector<std::string> args;
  args.emplace_back("Cx6");
  args.emplace_back("DB5");
  args.emplace_back("C#4");
  args.emplace_back("D6");
  Chord n2 (args, 4, ".");
  BOOST_TEST(n2.toString() == "Cx6,DB5,C#4,Dn6,3/8");
}

BOOST_AUTO_TEST_CASE(test_constr_throw) {
  BOOST_CHECK_THROW(Chord n0 ({""}, 1,4),         std::invalid_argument);
  BOOST_CHECK_THROW(Chord n1 ({"X"}, 1,4),        std::invalid_argument);
  BOOST_CHECK_THROW(Chord n2 ({"Cn4","XXX"}, 1,4),std::invalid_argument);
}

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
  n3.setUntied(1);
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

BOOST_AUTO_TEST_CASE(test_get_except) {
  Note * n1 = new Chord ({"C4", "G#5", "Db3"}, 1,4);
  BOOST_TEST(n1->getPitchSize() == 3);
  BOOST_TEST(n1->getPitch(1)->toString() == "G#5");
  BOOST_CHECK_THROW(n1->getPitch(5), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()