#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Core

#include "base_duration.hpp"
#include "base_note.hpp"
#include <vector>
#include <string>
#include <iostream>


#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

// Test duration
BOOST_AUTO_TEST_SUITE( duration )
BOOST_AUTO_TEST_CASE(constructor_test) {
  hautbois::core::BaseDuration d1;
  BOOST_CHECK_EQUAL(d1.getNum(), 1);
  BOOST_CHECK_EQUAL(d1.getDenom(), 1);

  hautbois::core::BaseDuration d2 (1, 4);
  BOOST_CHECK_EQUAL(d2.getNum(), 1);
  BOOST_CHECK_EQUAL(d2.getDenom(), 4);

  hautbois::core::BaseDuration d3 (std::vector<hautbois::UInt8>({3,8}));
  BOOST_CHECK_EQUAL(d3.getNum(), 3);
  BOOST_CHECK_EQUAL(d3.getDenom(), 8);

  hautbois::core::BaseDuration d4 (4, ".");
  BOOST_CHECK_EQUAL(d4.getNum(), 3);
  BOOST_CHECK_EQUAL(d4.getDenom(), 8);

  hautbois::core::BaseDuration d5 (2, "..");
  BOOST_CHECK_EQUAL(d5.getNum(), 5);
  BOOST_CHECK_EQUAL(d5.getDenom(), 8);

  hautbois::core::BaseDuration d6 (16, "");
  BOOST_CHECK_EQUAL(d6.getNum(), 1);
  BOOST_CHECK_EQUAL(d6.getDenom(), 16);

  BOOST_CHECK(d6.toString() == "1/16");
}

BOOST_AUTO_TEST_CASE(operator_test) {
  hautbois::core::BaseDuration d1 (1,8);
  hautbois::core::BaseDuration d2 (1,16);
  hautbois::core::BaseDuration d3 (3,16);
  hautbois::core::BaseDuration d4 (3,32);

  hautbois::core::BaseDuration * p_test;
  
  // operator +
  p_test = new hautbois::core::BaseDuration(d1 + d2);
  BOOST_CHECK(*p_test == d3);
  delete p_test;
  
  // operator -
  p_test = new hautbois::core::BaseDuration(d3 - d2);
  BOOST_CHECK(*p_test == d1);
  delete p_test;

  // operator +=
  d4 += hautbois::core::BaseDuration(16, ".");
  BOOST_CHECK(d4 == hautbois::core::BaseDuration(8, "."));

  // operator >
  BOOST_CHECK(d4 > d2);

  // operator <
  BOOST_CHECK(d2 < d1);

  // operator !=
  BOOST_CHECK(d2 != d1);
}
BOOST_AUTO_TEST_SUITE_END()

// Test note
BOOST_AUTO_TEST_SUITE( note )
BOOST_AUTO_TEST_CASE(constructor_test) {
  hautbois::core::BaseNote n1 ("C", "#", "4", 1, 2);
  //std::string str = n1.getFullNoteNameAsString();
  BOOST_CHECK(n1.getNoteName() == hautbois::core::NoteNameEnum::C);
}
BOOST_AUTO_TEST_SUITE_END()


