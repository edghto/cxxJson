#include <iostream>

#include <boost/property_tree/ptree.hpp>

#include <cxxJson/cxxJson.hpp>


#include <boost/fusion/adapted/struct.hpp>
#include <vector>
#include <type_traits> // for static_assert

namespace TestTypes {

struct FooObject
{
    int i;
    bool b;
    std::string str;
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

#define TEST(testCase, test) void testCase##_##test()
#define TEST_RUN(testCase, test) testCase##_##test()

#define STR(x) #x

TEST(DeserializeTest, deserializerSelectionScalar)
{
    using DeserializerType = cxxJson::detail::Deserializer<TestTypes::FooScalar>;
    static_assert(std::is_same<DeserializerType,cxxJson::detail::ScalarDeserializer<TestTypes::FooScalar>>::value,"WrongType");
}

TEST(DeserializeTest, deserializerSelectionArray)
{
    using DeserializerType = cxxJson::detail::Deserializer<TestTypes::FooArray>;
    static_assert(std::is_same<DeserializerType,cxxJson::detail::ArrayDeserializer<TestTypes::FooArray>>::value,"WrongType");
}

TEST(DeserializeTest, deserializerSelectionObject)
{
    using DeserializerType = cxxJson::detail::Deserializer<TestTypes::FooObject>;
    static_assert(std::is_same<DeserializerType,cxxJson::detail::ObjectDeserializer<TestTypes::FooObject>>::value,"WrongType");
}


int main()
{
    TEST_RUN(DeserializeTest, deserializerSelectionScalar);
    TEST_RUN(DeserializeTest, deserializerSelectionArray);
    TEST_RUN(DeserializeTest, deserializerSelectionObject);

    return 0;
}

