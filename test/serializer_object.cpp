#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>

using namespace ::testing;

TEST(ObjectSerializerTest, basic)
{
    TestTypes::FooObject obj{5, true, "str"};
    auto json = cxxJson::serialize(obj);

    EXPECT_THAT(5,     Eq(json.get<int>("i")));
    EXPECT_THAT(true,  Eq(json.get<bool>("b")));
    EXPECT_THAT("str", Eq(json.get<std::string>("str")));
}

TEST(ObjectSerializerTest, complex)
{
    TestTypes::BarObject obj{2.5, {1,2,3}, {5, true, "str"}};
    auto json = cxxJson::serialize(obj);

    EXPECT_THAT(2.5,     Eq(json.get<double>("d")));

    std::vector<int> actual, expected = std::vector<int>({ 1, 2, 3 });
    for(auto it : json.get_child("a"))
    {
        actual.push_back(it.second.get<int>(""));
    }
    EXPECT_THAT(expected, Eq(actual));

    EXPECT_THAT(5,     Eq(json.get_child("foo").get<int>("i")));
    EXPECT_THAT(true,  Eq(json.get_child("foo").get<bool>("b")));
    EXPECT_THAT("str", Eq(json.get_child("foo").get<std::string>("str")));
}
