#define BOOST_TEST_MODULE NoteSymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "note.hpp"
#include "pitch.hpp"
using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(NoteTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  Note n1 (1,4, "C4");
  Note n2 (1,4, "Gx5");
  Note n3 (1,4, "Bbb4");
  Note n4 (1,8, "Gss6");
  Note n5 (1,4, "C4-F4-A4");
  Note n6 (1,8, "C4+E4+G4");
  Note n7 (1,8, "S");
  Note n8 (1,8, "R");

  BOOST_TEST(n1.toString() == "(Cn4 1/4)");
  BOOST_TEST(n2.toString() == "(Gx5 1/4)");
  BOOST_TEST(n3.toString() == "(Bd4 1/4)");
  BOOST_TEST(n4.toString() == "(Gx6 1/8)");
  BOOST_TEST(n5.toString() == "(Cn4-Fn4-An4 1/4)");
  BOOST_TEST(n6.toString() == "(Cn4+En4+Gn4 1/8)");
  BOOST_TEST(n7.toString() == "(S 1/8)");
  BOOST_TEST(n8.toString() == "(R 1/8)");
}

BOOST_AUTO_TEST_CASE(test_constr_throw) {
  BOOST_CHECK_THROW(Note n0 (1,4, ""),         std::invalid_argument);
  BOOST_CHECK_THROW(Note n1 (1,4, "C"),        std::invalid_argument);
  BOOST_CHECK_THROW(Note n2 (1,0, "STD"),      std::invalid_argument);
  BOOST_CHECK_THROW(Note n3 (1,4, "Cdd4"),     std::invalid_argument);
  BOOST_CHECK_THROW(Note n4 (1,4, "C4--"),     std::invalid_argument);
  BOOST_CHECK_THROW(Note n5 (1,4, "C4,D4,E4"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_member) {
  Note n1 (1,4, "C4");
  Note n2 (1,8, "C4");
  bool t1 = n1.getPitch() == n2.getPitch();
  bool t2 = n1.getDuration() > n2.getDuration();
  BOOST_TEST(t1);
  BOOST_TEST(t2);
  
  Note n3 (1,8, "C4+E4+G4");
  auto & v = n3.getPitchGroup();
  std::string s;
  for (auto it = v.cbegin(); it != v.cend(); it++) {
    s.append( (*it)->toString() );
  }
  BOOST_TEST(s == "Cn4En4Gn4");
}

BOOST_AUTO_TEST_SUITE_END()