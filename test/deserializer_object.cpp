#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>

using namespace ::testing;

template<typename ObjectType>
using ObjectDeserializer = cxxJson::detail::ObjectDeserializer<ObjectType>;

#include <iostream>
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

TEST(ObjectDeserializerTest, complex)
{
    std::string strJson = R"({
    "d": 2.5,
    "a": [ 1, 2, 3 ],
    "foo": {
        "i": 5,
        "b": true,
        "str": "str"
    }
})";
    std::istringstream iss(strJson);
    boost::property_tree::ptree json;
    boost::property_tree::read_json(iss, json);
    auto actual = ObjectDeserializer<TestTypes::BarObject>::deserialize(json);
    TestTypes::BarObject expected{2.5, {1,2,3}, {5, true, "str"}};
    EXPECT_THAT(expected, Eq(actual));
}
