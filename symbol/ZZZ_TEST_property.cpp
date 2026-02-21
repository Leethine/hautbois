#define BOOST_TEST_MODULE PropertySymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "property.hpp"
using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(PropertyTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  Property p("trillo");
  BOOST_TEST(p.toString() == "trillo");
}

BOOST_AUTO_TEST_SUITE_END()
