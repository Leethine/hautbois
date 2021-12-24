#define BOOST_TEST_MODULE Note OneNote Base
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/one_note_rest.hpp"

using hautbois::NoteName;
using hautbois::Duration;
using hautbois::OneNoteBase;
using hautbois::OneNoteRest;

// Test constructor
OneNoteBase * n = new OneNoteRest({1,4});
BOOST_AUTO_TEST_CASE(test1_constructor) {
    BOOST_CHECK(n->getType() == hautbois::NoteType::REST);
}

// Test override functions
BOOST_AUTO_TEST_CASE(test2_override) {
    BOOST_CHECK_EQUAL(n->printNote(), "(R,1/4)");
    BOOST_CHECK_EQUAL(n->getName(), "R");
    BOOST_CHECK_EQUAL(n->getIndex(), 101); // 101 is the index for rest note
    BOOST_CHECK_EQUAL(n->getDurationNum(), 1);
    BOOST_CHECK_EQUAL(n->getDurationDenom(), 4);
}