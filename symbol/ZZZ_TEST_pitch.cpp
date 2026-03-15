#define BOOST_TEST_MODULE PitchSymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "pitch.hpp"
using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(PitchTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  Pitch p1('D', '#', 4);
  Pitch p2('E', 'n', 6);
  Pitch p3('G', 'B', 3);
  Pitch p4('R');
  BOOST_TEST(p1.getName()       == "D");
  BOOST_TEST(p1.getAccidental() == "#");
  BOOST_TEST(p1.getOctaveInt()  == 4);
  BOOST_TEST(p2.getName()       == "E");
  BOOST_TEST(p2.getAccidental() == "n");
  BOOST_TEST(p2.getOctaveInt()  == 6);
  BOOST_TEST(p3.toString()      == "GB3");
}

BOOST_AUTO_TEST_CASE(test_constructor_throw) {
  BOOST_CHECK_THROW(Pitch p1('D', 'X', 4),  std::invalid_argument);
  BOOST_CHECK_THROW(Pitch p2('D', 's', 4), std::invalid_argument);
  BOOST_CHECK_THROW(Pitch p3('X', 'n', 6),   std::invalid_argument);
  BOOST_CHECK_THROW(Pitch p4('V'), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_operator) {
  Pitch p1('D', '#', 5);
  Pitch p2('E', 'b', 5);
  Pitch p3('E', 'b', 5);

  bool t1 = p1 != p2;
  bool t2 = p2 == p3;
  bool t3 = p1.toIndex() == p2.toIndex();
  BOOST_TEST(t1);
  BOOST_TEST(t2);
  BOOST_TEST(t3);
}

BOOST_AUTO_TEST_SUITE_END()
