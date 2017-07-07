#ifndef CXXJSON_TEST_TESTTYPES_HPP
#define CXXJSON_TEST_TESTTYPES_HPP

#include <boost/fusion/adapted/struct.hpp>
#include <boost/optional.hpp>
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

struct BooObjectWithOptional
{
    int i;
    boost::optional<int> opt_i;

    FooObject foo;
    boost::optional<FooObject> opt_foo;
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
    TestTypes::BooObjectWithOptional,
    (int, i)
    (boost::optional<int>, opt_i)
    (TestTypes::FooObject, foo)
    (boost::optional<TestTypes::FooObject>, opt_foo)
);

BOOST_FUSION_ADAPT_STRUCT(
    TestTypes::BarObject,
    (double, d)
    (std::vector<int>, a)
    (TestTypes::FooObject, foo)
);

#endif // CXXJSON_TEST_TESTTYPES_HPP
