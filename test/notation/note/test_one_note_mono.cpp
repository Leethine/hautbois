#define BOOST_TEST_MODULE Note OneNote Base
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/one_note_mono.hpp"

using hautbois::NoteName;
using hautbois::Duration;
using hautbois::OneNote;
using hautbois::OneNoteMono;

// Test constructor
OneNote * n = new OneNoteMono("C4", {1,4});
BOOST_AUTO_TEST_CASE(test1_constructor) {
    BOOST_CHECK(n->getType() == hautbois::NoteType::MONO);
    BOOST_CHECK_EQUAL(n->isTied(), false);
    n->makeTie();
    BOOST_CHECK_EQUAL(n->isTied(), true);
    n->unTie();
    BOOST_CHECK_EQUAL(n->isTied(), false);
}

// Test override functions
BOOST_AUTO_TEST_CASE(test2_override) {
    BOOST_CHECK_EQUAL(n->printNote(), "(C4,1/4)");
    BOOST_CHECK_EQUAL(n->getName(), "C4");
    BOOST_CHECK_EQUAL(n->getIndex(), 40);
    BOOST_CHECK_EQUAL(n->getDurationNum(), 1);
    BOOST_CHECK_EQUAL(n->getDurationDenom(), 4);
}