#define BOOST_TEST_MODULE DurationSymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "pitch.hpp"
using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(DurationTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  Pitch p1('D', 's', 4);
  Pitch p2("E", "", 4);
  Pitch p3("D", "bb", "5");
  BOOST_TEST(p1.getName()       == "D");
  BOOST_TEST(p1.getAccidental() == "s");
  BOOST_TEST(p1.getOctaveInt()  == 4);
  BOOST_TEST(p2.getName()       == "E");
  BOOST_TEST(p2.getAccidental() == "n");
  BOOST_TEST(p2.getOctaveInt()  == 4);
  BOOST_TEST(p3.toString()      == "Dd5");
}

BOOST_AUTO_TEST_CASE(test_constructor_throw) {
  BOOST_CHECK_THROW(Pitch p1('D', 'B', 4),  std::invalid_argument);
  BOOST_CHECK_THROW(Pitch p2("D", "aa", 4), std::invalid_argument);
  BOOST_CHECK_THROW(Pitch p3("X", "", 6),   std::invalid_argument);
  BOOST_CHECK_THROW(Pitch p4("AZE", "", 3), std::invalid_argument);
  BOOST_CHECK_THROW(Pitch p4("A", "", 10),  std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_operator) {
  Pitch p1('D', 's', 4);
  Pitch p2("D", "s", 4);
  Pitch p3("E", "b", 4);

  bool t1 = p1 == p2;
  bool t2 = p1 == p3;
  BOOST_TEST(t1 == true);
  BOOST_TEST(t2 == false);
}

BOOST_AUTO_TEST_SUITE_END()
