#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>
#include <vector>

using namespace ::testing;

template<typename ObjectType>
using ObjectDeserializer = cxxJson::detail::ObjectDeserializer<ObjectType>;

TEST(ObjectDeserializerTest, basic)
{
    boost::property_tree::ptree json;
    json.put("i", 5);
    json.put("b", true);
    json.put("str", "str");
    auto actual = ObjectDeserializer<TestTypes::FooObject>::deserialize(json);
    TestTypes::FooObject expected{5, true, "str"};
    EXPECT_THAT(expected, Eq(actual));
}
