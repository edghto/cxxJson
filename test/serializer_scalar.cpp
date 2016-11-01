#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace ::testing;

TEST(ScalarSerializerTest, integer)
{
    TestTypes::FooObject obj{5, true, "str"};
    auto json = cxxJson::serialize(obj);

    EXPECT_EQ(5,     json.get<int>("i"));
    EXPECT_EQ(true,  json.get<bool>("b"));
    EXPECT_EQ("str", json.get<std::string>("str"));
}
