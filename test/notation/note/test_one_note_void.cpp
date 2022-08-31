#define BOOST_TEST_MODULE Note OneNote Base
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/one_note_void.hpp"

using hautbois::NoteName;
using hautbois::Duration;
using hautbois::OneNoteBase;
using hautbois::OneNoteVoid;

// Test constructor
OneNoteBase * n = new OneNoteVoid({1,4});
BOOST_AUTO_TEST_CASE(test1_constructor) {
    BOOST_CHECK(n->getType() == hautbois::NoteType::VOID);
}

// Test override functions
BOOST_AUTO_TEST_CASE(test2_override) {
    BOOST_CHECK_EQUAL(n->printNote(), "(V,1/4)");
    BOOST_CHECK_EQUAL(n->getName(), "V");
    BOOST_CHECK_EQUAL(n->getIndex(), 107); // 107 is the index for void note
    BOOST_CHECK_EQUAL(n->getDurationNum(), 1);
    BOOST_CHECK_EQUAL(n->getDurationDenom(), 4);
}
