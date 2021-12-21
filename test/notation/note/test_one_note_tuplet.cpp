#define BOOST_TEST_MODULE Note OneNote Base
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/one_note_tuplet.hpp"

using hautbois::NoteName;
using hautbois::Duration;
using hautbois::OneNote;
using hautbois::OneNoteTuplet;

// Test constructor
OneNote * n = new OneNoteTuplet({"C4","E4","G4"}, {1,2});
BOOST_AUTO_TEST_CASE(test1_constructor) {
    BOOST_CHECK(n->getType() == hautbois::NoteType::TUPLET);
}

// Test override functions for note1
BOOST_AUTO_TEST_CASE(test2_override) {
    BOOST_CHECK_EQUAL(n->printNote(), "(C4-E4-G4,1/2)");
    BOOST_CHECK_EQUAL(n->getName(), "Tuplet");
    BOOST_CHECK_EQUAL(n->getIndex(), 106); // 106 is the index for multuplex
    BOOST_CHECK_EQUAL(n->getDurationNum(), 1);
    BOOST_CHECK_EQUAL(n->getDurationDenom(), 2);
}

