#include <gmock/gmock.h>
#include <test_types.hpp>
#include <type_traits>
#include <cxxJson/cxxJson.hpp>

TEST(DeserializeTest, deserializerSelectionScalar)
{
    using ActualDeserializerType = cxxJson::detail::Deserializer<TestTypes::FooScalar>;
    using ExpectedDeserializerType = cxxJson::detail::ScalarDeserializer<TestTypes::FooScalar>;
    static_assert(std::is_base_of<ExpectedDeserializerType,ActualDeserializerType>::value,"WrongType");
}

TEST(DeserializeTest, deserializerSelectionArray)
{
    using ActualDeserializerType = cxxJson::detail::Deserializer<TestTypes::FooArray>;
    using ExpectedDeserializerType = cxxJson::detail::ArrayDeserializer<TestTypes::FooArray>;
    static_assert(std::is_base_of<ExpectedDeserializerType,ActualDeserializerType>::value,"WrongType");
}

TEST(DeserializeTest, deserializerSelectionObject)
{
    using ActualDeserializerType = cxxJson::detail::Deserializer<TestTypes::FooObject>;
    using ExpectedDeserializerType = cxxJson::detail::ObjectDeserializer<TestTypes::FooObject>;
    static_assert(std::is_base_of<ExpectedDeserializerType,ActualDeserializerType>::value,"WrongType");
}
