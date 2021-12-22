#define BOOST_TEST_MODULE Note creator utils
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/note_facade.hpp"

using namespace hautbois;

Note n1 ("rest","1/4");
Note n2 ("C#4","1/4");
Note n3 ("C#4+E#4","1/4");
Note n4 ("D5-E5-D5","1/2");
Note n5 ("C#4+E#4+G5","1/4+1/4+1/8");

// check types
BOOST_AUTO_TEST_CASE(test1_getType) {
    BOOST_CHECK(n1.getType() == NoteType::REST);
    BOOST_CHECK(n2.getType() == NoteType::MONO);
    BOOST_CHECK(n3.getType() == NoteType::CHORD);
    BOOST_CHECK(n4.getType() == NoteType::TUPLET);
    BOOST_CHECK(n5.getType() == NoteType::CHORD);
}

BOOST_AUTO_TEST_CASE(test2_types) {
    BOOST_CHECK(n1.getType() == NoteType::REST);
    BOOST_CHECK(n2.getType() == NoteType::MONO);
    BOOST_CHECK(n3.getType() == NoteType::CHORD);
    BOOST_CHECK(n4.getType() == NoteType::TUPLET);
    BOOST_CHECK(n5.getType() == NoteType::CHORD);
}

