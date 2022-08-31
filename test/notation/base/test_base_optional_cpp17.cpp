#define BOOST_TEST_MODULE Base Optional STL
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../../../src/notation/base/base_optional.hpp"
#define __CXX17

using hautbois::BaseOptional;

// Test on string container
BOOST_AUTO_TEST_CASE(test1_string) {
    BaseOptional<std::string> optionalStrValue;
    BOOST_TEST(!optionalStrValue.hasValue());
    optionalStrValue.emplaceValue("MyString");
    BOOST_TEST(optionalStrValue.hasValue());
    BOOST_TEST(optionalStrValue.getValue() == "MyString");
}

// Test on self-defined container
BOOST_AUTO_TEST_CASE(test2_class) {
    class MyClass {
    public:
        int elem1;
        std::string elem2;
        MyClass(int e1, std::string e2):
        elem1 { e1 },
        elem2 { e2 }
        {}
    };
    BaseOptional<MyClass> optionalMyClass;
    BOOST_TEST(!optionalMyClass.hasValue());
    optionalMyClass.emplaceValue(MyClass(12435,"MyString"));
    BOOST_TEST(optionalMyClass.hasValue());
    BOOST_TEST(optionalMyClass.getValue().elem1 == 12435);
    BOOST_TEST(optionalMyClass.getValue().elem2 == "MyString");
}