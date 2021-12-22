#define BOOST_TEST_MODULE Note creator utils
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/note_creator_utils.hpp"

using namespace hautbois;

// Test rmWhiteSpace
BOOST_AUTO_TEST_CASE(test1_rmWhiteSpace) {
    std::string s1 = "1 / 4";
    BOOST_CHECK_EQUAL(note_creator_utils::rmWhiteSpace_copy(s1), "1/4");
    BOOST_CHECK(s1 != "1/4");
    note_creator_utils::rmWhiteSpace(s1);
    BOOST_CHECK_EQUAL(s1, "1/4");
}

// Test SplitToken
BOOST_AUTO_TEST_CASE(test2_splitToken) {
    std::string s1 = "A#5+C#6+E6";
    TokenVector v1 = note_creator_utils::splitToken(s1, "+");
    BOOST_CHECK_EQUAL(v1.size(),3);
    BOOST_CHECK_EQUAL(v1[0],"A#5");
    BOOST_CHECK_EQUAL(v1[1],"C#6");
    BOOST_CHECK_EQUAL(v1[2],"E6");

    std::string s2 = "A#5-C#6-E6-C#6-A#5";
    TokenVector v2 = note_creator_utils::splitToken(s2, "-");
    BOOST_CHECK_EQUAL(v2.size(),5);
    BOOST_CHECK_EQUAL(v2[0],"A#5");
    BOOST_CHECK_EQUAL(v2[1],"C#6");
    BOOST_CHECK_EQUAL(v2[2],"E6");
    BOOST_CHECK_EQUAL(v2[3],"C#6");
    BOOST_CHECK_EQUAL(v2[4],"A#5");
}

// Test str2Duration
BOOST_AUTO_TEST_CASE(test3_str2Duration) {
    std::string s1 = "3/4";
    Duration d1 = note_creator_utils::str2Duration(s1);
    Duration d2 = {3,4};
    BOOST_CHECK_EQUAL(d1,d2);

    std::string s2 = "5/16";
    Duration d3 = note_creator_utils::str2Duration(s2);
    Duration d4 = {5,16};
    BOOST_CHECK_EQUAL(d3,d4);
}

// Test str2GroupDuration
BOOST_AUTO_TEST_CASE(test4_str2GroupDuration) {
    std::string s1 = "3/4+3/4+3/4";
    GroupDuration d1 = note_creator_utils::str2GroupDuration(s1);
    BOOST_CHECK_EQUAL(d1.size(),3);
    BOOST_CHECK_EQUAL(d1[0],Duration(3,4));
    BOOST_CHECK_EQUAL(d1[1],Duration(3,4));
    BOOST_CHECK_EQUAL(d1[2],Duration(3,4));

    std::string s2 = "3/4+3/4+1/4";
    GroupDuration d2 = note_creator_utils::str2GroupDuration(s2);
    BOOST_CHECK_EQUAL(d2.size(),3);
    BOOST_CHECK_EQUAL(d2[0],Duration(3,4));
    BOOST_CHECK_EQUAL(d2[1],Duration(3,4));
    BOOST_CHECK_EQUAL(d2[2],Duration(1,4));

    // test duplicable group duration
    GroupDuration d3 = note_creator_utils::str2GroupDuration("1/4",4);
    BOOST_CHECK_EQUAL(d3.size(),4);
    BOOST_CHECK_EQUAL(d3[0],Duration(1,4));
    BOOST_CHECK_EQUAL(d3[1],Duration(1,4));
    BOOST_CHECK_EQUAL(d3[2],Duration(1,4));
    BOOST_CHECK_EQUAL(d3[3],Duration(1,4));
}

// Test str2GroupNoteNameChord
BOOST_AUTO_TEST_CASE(test5_str2GroupNoteNameChord) {
    std::string s1 = "G5+Bb5+D6+E#6";
    GroupNoteName v1 = note_creator_utils::str2GroupNoteNameChord(s1);
    BOOST_CHECK_EQUAL(v1.size(),4);
    BOOST_CHECK_EQUAL(v1[0],"G5");
    BOOST_CHECK_EQUAL(v1[1],"Bb5");
    BOOST_CHECK_EQUAL(v1[2],"D6");
    BOOST_CHECK_EQUAL(v1[3],"E#6");

    std::string s2 = "D#2+E#4";
    GroupNoteName v2 = note_creator_utils::str2GroupNoteNameChord(s2);
    BOOST_CHECK_EQUAL(v2.size(),2);
    BOOST_CHECK_EQUAL(v2[0],"D#2");
    BOOST_CHECK_EQUAL(v2[1],"E#4");
}

// Test str2GroupNoteNameTuplet
BOOST_AUTO_TEST_CASE(test6_str2GroupNoteNameTuplet) {
    std::string s1 = "G5-Bb5-D6-F6-D6";
    GroupNoteName v1 = note_creator_utils::str2GroupNoteNameTuplet(s1);
    BOOST_CHECK_EQUAL(v1.size(),5);
    BOOST_CHECK_EQUAL(v1[0],"G5");
    BOOST_CHECK_EQUAL(v1[1],"Bb5");
    BOOST_CHECK_EQUAL(v1[2],"D6");
    BOOST_CHECK_EQUAL(v1[3],"F6");
    BOOST_CHECK_EQUAL(v1[4],"D6");

    std::string s2 = "D#2-E#4-F#5";
    GroupNoteName v2 = note_creator_utils::str2GroupNoteNameTuplet(s2);
    BOOST_CHECK_EQUAL(v2.size(),3);
    BOOST_CHECK_EQUAL(v2[0],"D#2");
    BOOST_CHECK_EQUAL(v2[1],"E#4");
    BOOST_CHECK_EQUAL(v2[2],"F#5");
}

// Test checkIfSingleDuration
BOOST_AUTO_TEST_CASE(test7_checkIfSingleDuration) {
    BOOST_CHECK(note_creator_utils::checkIfSingleDuration("1/4"));
    BOOST_CHECK(note_creator_utils::checkIfSingleDuration("1/8"));
    BOOST_CHECK(!note_creator_utils::checkIfSingleDuration("1/4+1/4"));
    BOOST_CHECK(!note_creator_utils::checkIfSingleDuration("1/4+1/4+1/8"));
}

// Test checkNoteType
BOOST_AUTO_TEST_CASE(test8_checkNoteType) {
    BOOST_CHECK(note_creator_utils::checkNoteType("Rest") == NoteType::REST);
    BOOST_CHECK(note_creator_utils::checkNoteType("rest") == NoteType::REST);
    BOOST_CHECK(note_creator_utils::checkNoteType("r") == NoteType::REST);
    BOOST_CHECK(note_creator_utils::checkNoteType("R") == NoteType::REST);

    BOOST_CHECK(note_creator_utils::checkNoteType("C4") == NoteType::MONO);
    BOOST_CHECK(note_creator_utils::checkNoteType("E#6") == NoteType::MONO);
    BOOST_CHECK(note_creator_utils::checkNoteType("Bb3") == NoteType::MONO);
    BOOST_CHECK(note_creator_utils::checkNoteType("Fb7") == NoteType::MONO);

    BOOST_CHECK(note_creator_utils::checkNoteType("C4+A5+G6") == NoteType::CHORD);
    BOOST_CHECK(note_creator_utils::checkNoteType("C#4+A#5") == NoteType::CHORD);
    BOOST_CHECK(note_creator_utils::checkNoteType("C4+A#5+Gb6+Db7") == NoteType::CHORD);
    
    BOOST_CHECK(note_creator_utils::checkNoteType("C4-A5-G6") == NoteType::TUPLET);
    BOOST_CHECK(note_creator_utils::checkNoteType("C#4-A#5") == NoteType::TUPLET);
    BOOST_CHECK(note_creator_utils::checkNoteType("C4-A#5-Gb6-Db7") == NoteType::TUPLET);
}

