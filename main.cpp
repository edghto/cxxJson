#include <iostream>

#include <boost/property_tree/ptree.hpp>

#include <cxxJson/cxxJson.hpp>


#include <boost/fusion/adapted/struct.hpp>
#include <vector>
#include <type_traits> // for static_assert
#include <cassert>

using ptree = boost::property_tree::ptree;

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
    static_assert(std::is_base_of<cxxJson::detail::ScalarDeserializer<TestTypes::FooScalar>,DeserializerType>::value,"WrongType");
}

TEST(DeserializeTest, deserializerSelectionArray)
{
    using DeserializerType = cxxJson::detail::Deserializer<TestTypes::FooArray>;
    static_assert(std::is_base_of<cxxJson::detail::ArrayDeserializer<TestTypes::FooArray>,DeserializerType>::value,"WrongType");
}

TEST(DeserializeTest, deserializerSelectionObject)
{
    using DeserializerType = cxxJson::detail::Deserializer<TestTypes::FooObject>;
    static_assert(std::is_base_of<cxxJson::detail::ObjectDeserializer<TestTypes::FooObject>,DeserializerType>::value,"WrongType");
}

template<typename ScalarType>
using ScalarDeserializer = cxxJson::detail::ScalarDeserializer<ScalarType>;

TEST(DeserializeTest, deserializerScalarInt)
{
    ptree json;
    int in = 5;
    json.put("", in);
    auto out = ScalarDeserializer<int>::deserialize(json);
    assert(in==out);
}

TEST(DeserializeTest, deserializerScalarDouble)
{
    ptree json;
    int in = 2.5;
    json.put("", in);
    auto out = ScalarDeserializer<double>::deserialize(json);
    assert(in==out);
}

TEST(DeserializeTest, deserializerScalarBool)
{
    ptree json;
    bool in = true;
    json.put("", in);
    auto out = ScalarDeserializer<bool>::deserialize(json);
    assert(in==out);
}

TEST(DeserializeTest, deserializerScalarString)
{
    ptree json;
    std::string in = "foo";
    json.put("", in);
    auto out = ScalarDeserializer<std::string>::deserialize(json);
    assert(in==out);
}

template<typename ArrayType>
using ArrayDeserializer = cxxJson::detail::ArrayDeserializer<ArrayType>;

template<typename T>
inline auto getChild(const T& t)
{
    ptree p;
    p.put("", t);
    return std::make_pair("",p);
}

TEST(DeserializeTest, deserializerArray)
{
    ptree json;
    json.push_back(getChild(1));
    json.push_back(getChild(2));
    json.push_back(getChild(3));
    auto out = ArrayDeserializer<std::vector<int>>::deserialize(json);
    assert(out == std::vector<int>({1,2,3}));
}

int main()
{
    TEST_RUN(DeserializeTest, deserializerSelectionScalar);
    TEST_RUN(DeserializeTest, deserializerSelectionArray);
    TEST_RUN(DeserializeTest, deserializerSelectionObject);
    TEST_RUN(DeserializeTest, deserializerScalarInt);
    TEST_RUN(DeserializeTest, deserializerScalarDouble);
    TEST_RUN(DeserializeTest, deserializerScalarBool);
    TEST_RUN(DeserializeTest, deserializerScalarString);
    TEST_RUN(DeserializeTest, deserializerArray);

    return 0;
}

