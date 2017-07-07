#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace ::testing;

TEST(OptionalSerializerTest, scalar)
{
    TestTypes::BooObjectWithOptional obj;
    auto json = cxxJson::serialize(obj);

    EXPECT_EQ(1, json.count("i"));
    EXPECT_EQ(0, json.count("opt_i"));
}

TEST(OptionalSerializerTest, object)
{
    TestTypes::BooObjectWithOptional obj;
    auto json = cxxJson::serialize(obj);

    EXPECT_EQ(1, json.count("foo"));
    EXPECT_EQ(0, json.count("opt_foo"));
}
