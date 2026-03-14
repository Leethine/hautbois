#define BOOST_TEST_MODULE SingleNoteSymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "note.hpp"
#include "note_single.hpp"
#include "pitch.hpp"
#include "duration.hpp"

using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(SingleNoteTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  SingleNote n1 ("C",1,4);
  SingleNote n2 ("D#5",1,4);
  SingleNote n3 ("Eb6",1,4);
  SingleNote n4 ("Fx7",1,8);
  SingleNote n5 ("GB1",1,4);
  SingleNote n6 ("A8",1,8);
  SingleNote n7 ("B0",1,8);
  SingleNote n8 ("S",1,8);
  SingleNote n9 ("R",1,8);

  BOOST_TEST(n1.toString() == "Cn4,1/4");
  BOOST_TEST(n2.toString() == "D#5,1/4");
  BOOST_TEST(n3.toString() == "Eb6,1/4");
  BOOST_TEST(n4.toString() == "Fx7,1/8");
  BOOST_TEST(n5.toString() == "GB1,1/4");
  BOOST_TEST(n6.toString() == "An8,1/8");
  BOOST_TEST(n7.toString() == "Bn0,1/8");
  BOOST_TEST(n8.toString() == "S,1/8");
  BOOST_TEST(n9.toString() == "R,1/8");
}

BOOST_AUTO_TEST_CASE(test_constr_throw) {
  BOOST_CHECK_THROW(SingleNote n0 ("", 1,4),         std::invalid_argument);
  BOOST_CHECK_THROW(SingleNote n1 ("X", 1,4),        std::invalid_argument);
  BOOST_CHECK_THROW(SingleNote n2 ("STD", 1,4),      std::invalid_argument);
  BOOST_CHECK_THROW(SingleNote n3 ("Cdd4", 1,4),     std::invalid_argument);
  BOOST_CHECK_THROW(SingleNote n4 ("C5",4,"..."),    std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_member) {
  SingleNote n1 ("C4", 1,4);
  SingleNote n2 ("C4", 1,8);
  bool t1 = *n1.getPitch() == *n2.getPitch();
  bool t2 = *n1.getDuration() > *n2.getDuration();
  BOOST_TEST(t1);
  BOOST_TEST(t2);
}

BOOST_AUTO_TEST_CASE(test_property) {
  SingleNote n1 ("C4", 1,4);
  BOOST_TEST(n1.getPropertyStr().empty());
  n1.updateProperty("trill");
  BOOST_TEST(n1.getPropertyStr() == "trill");
}

BOOST_AUTO_TEST_CASE(test_get_except) {
  class NewSingleNote : public SingleNote {
    public:
    NewSingleNote() : SingleNote() {}
  };
  NewSingleNote * n = new NewSingleNote();
  BOOST_TEST(!n->hasPitch());
  BOOST_TEST(n->getPitchSize() == 0);
  BOOST_TEST(!n->hasDuration());
  BOOST_TEST(n->getDurationSize() == 0);
}

BOOST_AUTO_TEST_SUITE_END()