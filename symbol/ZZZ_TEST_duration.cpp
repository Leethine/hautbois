#define BOOST_TEST_MODULE DurationSymbolTest
#include <boost/test/included/unit_test.hpp>
#include <string>

#include "duration.hpp"
using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(DurationTestSuite)

BOOST_AUTO_TEST_CASE(test_constructor) {
  Duration d1(3,8);
  BOOST_TEST(d1.getNum() == 3);
  BOOST_TEST(d1.getDenom() == 8);
  BOOST_CHECK_NO_THROW(Duration d2(3,16));
  BOOST_CHECK_THROW(Duration d3(-1,8), std::invalid_argument);
  BOOST_CHECK_THROW(Duration d4(1,256), std::invalid_argument);
  BOOST_CHECK_THROW(Duration d5(0,0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_constructor_dots) {
  BOOST_CHECK_THROW(Duration d1(4, "..."), std::invalid_argument);
  BOOST_CHECK_THROW(Duration d2(4, "qsdlqjsfl"), std::invalid_argument);
  BOOST_CHECK_NO_THROW(Duration d3(8, "."));
  BOOST_CHECK_NO_THROW(Duration d4(4, ".."));
  Duration d5(8, ".");
  BOOST_TEST(d5.getNum() == 3);
  BOOST_TEST(d5.getDenom() == 16);
  Duration d6(8, "..");
  BOOST_TEST(d6.getNum() == 7);
  BOOST_TEST(d6.getDenom() == 32);
}

BOOST_AUTO_TEST_CASE(test_comparison) {
  Duration d1(1,4);
  Duration d2(1,8);
  Duration d3(1,16);
  Duration d4(1,4);
  if (d1 == d4) { BOOST_TEST(true );  }
  else          { BOOST_TEST(false); }
  if (d2 < d1)  { BOOST_TEST(true );  }
  else          { BOOST_TEST(false); }
  if (d2 > d3)  { BOOST_TEST(true );  }
  else          { BOOST_TEST(false); }
  if (d3 != d4) { BOOST_TEST(true );  }
  else          { BOOST_TEST(false); }
}

BOOST_AUTO_TEST_CASE(test_operators_plusminus) {
  Duration d1(1,4);
  Duration d2(1,8);
  Duration d3(1,16);
  Duration d4(1,4);

  Duration dd1 = d1 + d4;
  Duration dd2 = d2 + d4;
  Duration dd3 = d4 - d3;
  Duration dd4 = d2 - d4;
  BOOST_TEST(dd1.getNum() == 1);
  BOOST_TEST(dd1.getDenom() == 2);
  BOOST_TEST(dd2.getNum() == 3);
  BOOST_TEST(dd2.getDenom() == 8);
  BOOST_TEST(dd3.getNum() == 3);
  BOOST_TEST(dd3.getDenom() == 16);
  BOOST_TEST(dd4.getNum() == 1);
  BOOST_TEST(dd4.getDenom() == 8);

  try {
    d1 - d4;
  }
  catch(std::logic_error& e) {
    std::string err_msg (e.what());
    if (err_msg == "d1 == d2") {
      BOOST_TEST(true);
    }
    else {
      BOOST_TEST(false);
    }
  }
}

BOOST_AUTO_TEST_CASE(test_operators_multi_div) {
  Duration d1(1,4);
  Duration d2 = d1 / 2;
  Duration d3 = d1 * 2;
  BOOST_TEST(d2.getNum() == 1);
  BOOST_TEST(d2.getDenom() == 8);
  BOOST_TEST(d3.getNum() == 1);
  BOOST_TEST(d3.getDenom() == 2);
}

BOOST_AUTO_TEST_SUITE_END()
