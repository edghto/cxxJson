#ifndef CXXJSON_TEST_TESTTYPES_HPP
#define CXXJSON_TEST_TESTTYPES_HPP

#include <boost/fusion/adapted/struct.hpp>
#include <string>
#include <vector>

namespace TestTypes {

struct FooObject
{
    int i;
    bool b;
    std::string str;

    bool operator ==(const FooObject& that) const
    {
        return i == that.i
                && b == that.b
                && str == that.str;
    }
};

struct BarObject
{
    double d;
    std::vector<int> a;
    FooObject foo;

    bool operator ==(const BarObject& that) const
    {
        return d == that.d
                && a == that.a
                && foo == that.foo;
    }
};

using FooArray = std::vector<int>;
using FooScalar = int;

} // namespace TestTypes

BOOST_FUSION_ADAPT_STRUCT(
    TestTypes::FooObject,
    (int, i)
    (bool, b)
    (std::string, str)
);

BOOST_FUSION_ADAPT_STRUCT(
    TestTypes::BarObject,
    (double, d)
    (std::vector<int>, a)
    (TestTypes::FooObject, foo)
);

#endif // CXXJSON_TEST_TESTTYPES_HPP
