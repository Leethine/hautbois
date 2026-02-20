#define BOOST_TEST_MODULE RawSymbolsTest
#include <boost/test/included/unit_test.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <string>
#include <cstring>

#include "duration_raw.hpp"
#include "pitch_raw.hpp"
#include "property_raw.hpp"

using namespace hautbois;
using namespace core;

BOOST_AUTO_TEST_SUITE(DurationRawTestSuite)

BOOST_AUTO_TEST_CASE(set_get) {
  DurationRaw d(1,4);
  BOOST_TEST(d.getNum() == 1);
  BOOST_TEST(d.getDenom() == 4);
  d.setNum(3);
  d.setDenom(8);
  BOOST_TEST(d.getNum() == 3);
  BOOST_TEST(d.getDenom() == 8);
}

BOOST_AUTO_TEST_CASE(serialization) {
  DurationRaw d1(7,16);
  std::ofstream ofs("serial_object1");
  {
    boost::archive::text_oarchive oa(ofs);
    oa << d1;
  }
  DurationRaw d2;
  {
    std::ifstream ifs("serial_object1");
    boost::archive::text_iarchive ia(ifs);
    ia >> d2;
  }
  BOOST_TEST(d2.getNum() == 7);
  BOOST_TEST(d2.getDenom() == 16);
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(PitchRawTestSuite)

BOOST_AUTO_TEST_CASE(set_get) {
  PitchRaw p('C', 'n', 4);
  BOOST_TEST(p.getName() == 'C');
  BOOST_TEST(p.getAccidental() == 'n');
  BOOST_TEST(p.getOctave() == 4);
  p.setName('D');
  p.setAccidental('s');
  p.setOctave(5);
  BOOST_TEST(p.getName() == 'D');
  BOOST_TEST(p.getAccidental() == 's');
  BOOST_TEST(p.getOctave() == 5);
}

BOOST_AUTO_TEST_CASE(serialization) {
  PitchRaw p1('G', 'x', 6);
  std::ofstream ofs("serial_object2");
  {
    boost::archive::text_oarchive oa(ofs);
    oa << p1;
  }
  PitchRaw p2;
  {
    std::ifstream ifs("serial_object2");
    boost::archive::text_iarchive ia(ifs);
    ia >> p2;
  }
  BOOST_TEST(p2.getName() == 'G');
  BOOST_TEST(p2.getAccidental() == 'x');
  BOOST_TEST(p2.getOctave() == 6);
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(PropertyRawTestSuite)

BOOST_AUTO_TEST_CASE(set_get) {
  PropertyRaw p;
  BOOST_ASSERT(!p.hasValue());
  std::string s ("test string");
  p.set(s.c_str());
  BOOST_ASSERT(p.hasValue());
  BOOST_TEST(p.getStr() == s);
  BOOST_TEST(std::strcmp(s.c_str(),p.get()) == 0);
}

BOOST_AUTO_TEST_CASE(serialization) {
  PropertyRaw p1;
  std::string s ("test string string");
  p1.set(s.c_str());
  std::ofstream ofs("serial_object3");
  {
    boost::archive::text_oarchive oa(ofs);
    oa << p1;
  }
  PropertyRaw p2;
  {
    std::ifstream ifs("serial_object3");
    boost::archive::text_iarchive ia(ifs);
    ia >> p2;
  }
  BOOST_ASSERT(p2.hasValue());
  BOOST_TEST(p2.getStr() == s);
}

BOOST_AUTO_TEST_SUITE_END()