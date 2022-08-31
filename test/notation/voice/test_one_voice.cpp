#define BOOST_TEST_MODULE Voice OneVoice
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/voice/one_voice.hpp"

using hautbois::Duration;
using hautbois::OneNote;
using hautbois::OneBar;
using hautbois::OneVoice;

BOOST_AUTO_TEST_CASE(test1_constructor) {
    OneVoice voice1("3/4");
}

BOOST_AUTO_TEST_CASE(test2_addgetnote) {
    OneVoice voice1("3/4");
    voice1.addNote("C#5", "1/4");
    voice1.addNote("F5", "1/4");
    voice1.addNote("A5", "1/4");
    voice1.addNote("D5", "1/4");
    voice1.addNote("F5", "1/4");
    voice1.addNote("A5", "1/4");

    OneNote& n1 = voice1.getNoteInBar(1,1);
    OneNote& n2 = voice1.getNoteInBar(0,2);
    BOOST_CHECK_EQUAL(n1.printNote(), "(F5,1/4)");
    BOOST_CHECK_EQUAL(n2.printNote(), "(A5,1/4)");
}

BOOST_AUTO_TEST_CASE(test3_tempvoice) {
    OneVoice voice1("3/4");
    voice1.newTempVoice(3);
    voice1.addNoteTempVoice("A5","1/4");
    voice1.addNoteTempVoice("B5","1/4");
    // if the last note is commented, there will be error
    voice1.addNoteTempVoice("A5","1/4");

    voice1.newTempVoice(7);
    voice1.addNoteTempVoice("B5","1/4");
    voice1.addNoteTempVoice("C6","1/4");
    voice1.addNoteTempVoice("B5","1/4");

    OneBar& bar1 = voice1.getBarTempVoice(0,0);
    BOOST_CHECK_EQUAL(bar1.printBarLine(), "(A5,1/4) (B5,1/4) (A5,1/4)");
}