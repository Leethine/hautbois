#define BOOST_TEST_MODULE Note Duration
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/base/syntax_regexp.hpp"
#include <regex>

using namespace hautbois;

// Test duration token pattern
BOOST_AUTO_TEST_CASE(test1_pattern) {
    std::regex e(base_syntax_regexp::DURATION_TOKEN_PTN);
    // should match
    BOOST_CHECK(std::regex_match("1/4",e));
    BOOST_CHECK(std::regex_match("1/16",e));
    BOOST_CHECK(std::regex_match("15/16",e));
    BOOST_CHECK(std::regex_match("3/4",e));
    BOOST_CHECK(std::regex_match("4/4",e));
    // not match
    BOOST_CHECK(!std::regex_match("124135",e));
    BOOST_CHECK(!std::regex_match("123",e));
}

// Test group duration token pattern
BOOST_AUTO_TEST_CASE(test2_pattern) {
    std::regex e(base_syntax_regexp::GROUP_DURATION_TOKEN_PTN);
    // should match
    BOOST_CHECK(std::regex_match("1/4+1/4+1/4",e));
    BOOST_CHECK(std::regex_match("1/4+1/4+1/8",e));
    BOOST_CHECK(std::regex_match("1/4+1/8",e));
    // not match
    BOOST_CHECK(!std::regex_match("1/16",e));
    BOOST_CHECK(!std::regex_match("15/16",e));
    BOOST_CHECK(!std::regex_match("3/4",e));
}

// Test mononote token pattern
BOOST_AUTO_TEST_CASE(test3_pattern) {
    std::regex e(base_syntax_regexp::MONO_NOTE_TOKEN_PTN);
    // should match
    BOOST_CHECK(std::regex_match("C4",e));
    BOOST_CHECK(std::regex_match("A#5",e));
    BOOST_CHECK(std::regex_match("Bb6",e));
    // not match
    BOOST_CHECK(!std::regex_match("C",e));
    BOOST_CHECK(!std::regex_match("A#",e));
    BOOST_CHECK(!std::regex_match("Bb",e));
    BOOST_CHECK(!std::regex_match("B6b",e));
}

// Test chord pattern
BOOST_AUTO_TEST_CASE(test4_pattern) {
    std::regex e(base_syntax_regexp::CHORD_NOTE_TOKEN_PTN);
    // should match
    BOOST_CHECK(std::regex_match("C4+E4",e));
    BOOST_CHECK(std::regex_match("A#5+C#6+E6",e));
    BOOST_CHECK(std::regex_match("B6+D7+G7+B7",e));
    // not match
    BOOST_CHECK(!std::regex_match("B6-D7-G7-B7",e));
    BOOST_CHECK(!std::regex_match("C4",e));
    BOOST_CHECK(!std::regex_match("A#5",e));
    BOOST_CHECK(!std::regex_match("Bb6",e));
}

// Test tuplet pattern
BOOST_AUTO_TEST_CASE(test5_pattern) {
    std::regex e(base_syntax_regexp::TUPLET_NOTE_TOKEN_PTN);
    // should match
    BOOST_CHECK(std::regex_match("A#5-C#6-E6",e));
    BOOST_CHECK(std::regex_match("B6-D7-G7-B7-C8",e));
    // not match
    BOOST_CHECK(!std::regex_match("B6+D7+G7+B7",e));
    BOOST_CHECK(!std::regex_match("B6+D7+G7",e));
    BOOST_CHECK(!std::regex_match("C4",e));
    BOOST_CHECK(!std::regex_match("A#5",e));
    BOOST_CHECK(!std::regex_match("Bb6",e));
}

// Test rest note pattern
BOOST_AUTO_TEST_CASE(test6_pattern) {
    std::regex e(base_syntax_regexp::REST_NOTE_TOKEN_PTN);
    // should match
    BOOST_CHECK(std::regex_match("rest",e));
    BOOST_CHECK(std::regex_match("Rest",e));
    BOOST_CHECK(std::regex_match("r",e));
    BOOST_CHECK(std::regex_match("R",e));
    // not match
    BOOST_CHECK(!std::regex_match("B6+D7+G7+B7",e));
    BOOST_CHECK(!std::regex_match("B6+D7+G7",e));
    BOOST_CHECK(!std::regex_match("C4",e));
    BOOST_CHECK(!std::regex_match("A#5",e));
    BOOST_CHECK(!std::regex_match("Bb6",e));
    BOOST_CHECK(!std::regex_match("restrest",e));
    BOOST_CHECK(!std::regex_match("RestRest",e));
    BOOST_CHECK(!std::regex_match("Restrest",e));
    BOOST_CHECK(!std::regex_match("restRest",e));
}
