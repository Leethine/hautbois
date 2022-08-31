#define BOOST_TEST_MODULE Bar OneBar
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/bar/one_bar.hpp"

using hautbois::Duration;
using hautbois::OneNote;
using hautbois::OneBar;

BOOST_AUTO_TEST_CASE(test1_constructor) {
    OneBar bar1;
    OneBar bar2("3/4");
    BOOST_CHECK_EQUAL(bar1.getMeter(), Duration(4,4));
    BOOST_CHECK_EQUAL(bar2.getMeter(), Duration(3,4));
}

BOOST_AUTO_TEST_CASE(test2_addnote) {
    OneBar bar1;
    bar1.addNote("C#5", "1/4");
    bar1.addNote("C#5", "1/4");
    bar1.addNote("C#5", "1/4");
    bar1.addNote("C#5", "1/4");
}

BOOST_AUTO_TEST_CASE(test3_getnote) {
    OneBar bar1;
    bar1.addNote("C#5", "1/4");
    bar1.addNote("D#5", "1/4");
    bar1.addNote("E5", "1/4");
    bar1.addNote("F5", "1/4");
    BOOST_CHECK_EQUAL(bar1.printNthNote(3), "(F5,1/4)");
    BOOST_CHECK_EQUAL(bar1.printNthNote(2), "(E5,1/4)");

    // deletion of E5, then F5 should be the lastone
    bar1.deleteNthNote(2);
    BOOST_CHECK_EQUAL(bar1.printNthNote(2), "(F5,1/4)");

    bar1.addNote("G5", "1/4");
    BOOST_CHECK_EQUAL(bar1.getFirstNote().printNote(), "(C#5,1/4)");
    BOOST_CHECK_EQUAL(bar1.getLastNote().printNote(), "(G5,1/4)");
}

BOOST_AUTO_TEST_CASE(test4_getnote) {
    OneBar bar1;
    bar1.addNote("C#5", "1/4");
    bar1.addNote("D#5", "1/4");
    bar1.addNote("E5", "1/4");
    bar1.addNote("F5", "1/4");
    BOOST_CHECK_EQUAL(bar1.printBarLine(),"(C#5,1/4) (D#5,1/4) (E5,1/4) (F5,1/4)");
}

BOOST_AUTO_TEST_CASE(test5_insertnote) {
    OneBar bar1;
    bar1.addNote("C5", "1/4");
    bar1.addNote("D5", "1/4");
    bar1.addNote("E5", "1/4");
    bar1.insertNote(1, "F5", "1/4");
    BOOST_CHECK_EQUAL(bar1.printBarLine(),"(C5,1/4) (F5,1/4) (D5,1/4) (E5,1/4)");
}