#define BOOST_TEST_MODULE Note creator utils
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/note_facade.hpp"

using namespace hautbois;

OneNote n1 ("rest","1/4");
OneNote n2 ("C#4","1/4");
OneNote n3 ("C#4+E#4","1/4");
OneNote n4 ("D5-E5-D5","1/2");
OneNote n5 ("C#4+E#4+G5","1/4+1/4+1/8");
OneNote n6 ("Void","1/4");

// check types
BOOST_AUTO_TEST_CASE(test1_getType) {
    BOOST_CHECK(n1.getType() == NoteType::REST);
    BOOST_CHECK(n2.getType() == NoteType::MONO);
    BOOST_CHECK(n3.getType() == NoteType::CHORD);
    BOOST_CHECK(n4.getType() == NoteType::TUPLET);
    BOOST_CHECK(n5.getType() == NoteType::CHORD);
    BOOST_CHECK(n6.getType() == NoteType::VOID);
}

// getDuration method
BOOST_AUTO_TEST_CASE(test2_getDuration) {
    BOOST_CHECK_EQUAL(n1.getDuration(), "1/4");
    BOOST_CHECK_EQUAL(n2.getDuration(), "1/4");
    BOOST_CHECK_EQUAL(n3.getDuration(), "1/4");
    BOOST_CHECK_EQUAL(n4.getDuration(), "1/2");
    BOOST_CHECK_EQUAL(n5.getDuration(), "1/4+1/4+1/8");
    BOOST_CHECK_EQUAL(n6.getDuration(), "1/4");
}

// getIndex method
BOOST_AUTO_TEST_CASE(test3_getIndex) {
    BOOST_CHECK_EQUAL(n1.getIndex(), "101");
    BOOST_CHECK_EQUAL(n2.getIndex(), "41");
    BOOST_CHECK_EQUAL(n3.getIndex(), "41+45");
    BOOST_CHECK_EQUAL(n4.getIndex(), "54+56+54");
    BOOST_CHECK_EQUAL(n5.getIndex(), "41+45+59");
    BOOST_CHECK_EQUAL(n6.getIndex(), "107");
}

