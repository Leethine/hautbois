#define BOOST_TEST_MODULE Note Duration
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "../../../src/notation/note/duration.hpp"

using hautbois::Duration;

// Test constructors
BOOST_AUTO_TEST_CASE(test1_constructors) {
    Duration d1;
    BOOST_CHECK_EQUAL(d1.getNum(), 0);
    BOOST_CHECK_EQUAL(d1.getDenom(), 1);

    Duration d2(1,4);
    BOOST_CHECK_EQUAL(d2.getNum(), 1);
    BOOST_CHECK_EQUAL(d2.getDenom(), 4);

    // test default constructor
    Duration d3 = {3,4};
    BOOST_CHECK_EQUAL(d3.getNum(), 3);
    BOOST_CHECK_EQUAL(d3.getDenom(), 4);
}

// Test operators
BOOST_AUTO_TEST_CASE(test2_operators) {
    Duration d1(1,4);
    Duration d2(1,2);
    Duration d3(1,2);
    
    // == , !=
    BOOST_CHECK(d1 != d2);
    BOOST_CHECK(d1 != d3);
    BOOST_CHECK(d2 == d3);
    // + , -
    BOOST_CHECK_EQUAL(d1 + d2, Duration(3,4));
    BOOST_CHECK_EQUAL(d1 - d2, Duration(1,4));
    BOOST_CHECK_EQUAL(d2 - d1, Duration(1,4));
    // >, <
    BOOST_CHECK(d1 < d2);
    BOOST_CHECK(Duration(3,4) > d2);
    // << (printDuration)
    BOOST_CHECK_EQUAL(d1.printDuration(), "1/4");
    BOOST_CHECK_EQUAL(d2.printDuration(), "1/2");
}