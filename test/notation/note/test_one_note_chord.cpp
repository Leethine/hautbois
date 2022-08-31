#define BOOST_TEST_MODULE Note OneNote Base
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/one_note_chord.hpp"

using hautbois::NoteName;
using hautbois::Duration;
using hautbois::OneNoteBase;
using hautbois::OneNoteChord;

// Test constructor
OneNoteBase * n1 = new OneNoteChord({"C4","E4","G4"}, {{1,4},{1,4},{1,4}});
BOOST_AUTO_TEST_CASE(test1_constructor) {
    BOOST_CHECK(n1->getType() == hautbois::NoteType::CHORD);
}

// Test override functions for note1
BOOST_AUTO_TEST_CASE(test2_override) {
    BOOST_CHECK_EQUAL(n1->printNote(), "(C4+E4+G4,1/4)");
    BOOST_CHECK_EQUAL(n1->getName(), "Chord");
    BOOST_CHECK_EQUAL(n1->getIndex(), 103);
    BOOST_CHECK_EQUAL(n1->getDurationNum(), 1);
    BOOST_CHECK_EQUAL(n1->getDurationDenom(), 4);
}

// Test override functions for note2
OneNoteBase * n2 = new OneNoteChord({"A3","C#4","E4"}, {{1,4},{1,4},{1,8}});
BOOST_AUTO_TEST_CASE(test3_override) {
    BOOST_CHECK_EQUAL(n2->printNote(), "(A3+C#4+E4,1/4+1/4+1/8)");
    BOOST_CHECK_EQUAL(n2->getName(), "Chord"); 
    BOOST_CHECK_EQUAL(n2->getIndex(), 103); // 103 is the index for chord
    BOOST_CHECK_EQUAL(n2->getDurationNum(), 1);
    BOOST_CHECK_EQUAL(n2->getDurationDenom(), 4);
}
