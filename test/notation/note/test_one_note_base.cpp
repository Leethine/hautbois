#define BOOST_TEST_MODULE Note OneNote Base
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/one_note_base.hpp"

using hautbois::OneNote;

OneNote n;
BOOST_AUTO_TEST_CASE(test1_constructor) {
    BOOST_CHECK(n.getType() == hautbois::NoteType::VIRTUAL);
    BOOST_CHECK_EQUAL(n.isTied(), false);
    n.makeTie();
    BOOST_CHECK_EQUAL(n.isTied(), true);
    n.unTie();
    BOOST_CHECK_EQUAL(n.isTied(), false);
}

BOOST_AUTO_TEST_CASE(test2_printnote) {
    BOOST_CHECK_EQUAL(n.printNote(), "()");
}
