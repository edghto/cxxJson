#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace ::testing;

namespace {

class OptionalDeserializerTest : public Test
{
public:
    void SetUp() override
    {
        boost::property_tree::ptree fooJson;
        fooJson.put("i", 5);
        fooJson.put("b", true);
        fooJson.put("str", "str");

        json_.put("i", 5);
        json_.add_child("foo", fooJson);
    }


    boost::property_tree::ptree json_;
};

}

TEST_F(OptionalDeserializerTest, unintializedScalar)
{
    auto actual = cxxJson::deserialize<TestTypes::BooObjectWithOptional>(json_);

    EXPECT_FALSE(actual.opt_i.is_initialized());
}

TEST_F(OptionalDeserializerTest, initializedScalar)
{
    const int opt_i_target_value = 10;
    json_.put("opt_i", opt_i_target_value);
    auto actual = cxxJson::deserialize<TestTypes::BooObjectWithOptional>(json_);

    ASSERT_TRUE(actual.opt_i.is_initialized());
    EXPECT_THAT(opt_i_target_value, Eq(actual.opt_i.get()));
}

TEST_F(OptionalDeserializerTest, uninitializedObject)
{
    auto actual = cxxJson::deserialize<TestTypes::BooObjectWithOptional>(json_);

    EXPECT_FALSE(actual.opt_foo.is_initialized());
}

TEST_F(OptionalDeserializerTest, initializedObject)
{
    boost::property_tree::ptree opt_foo;
    opt_foo.put("i", 5);
    opt_foo.put("b", true);
    opt_foo.put("str", "str");
    json_.add_child("opt_foo", opt_foo);

    auto actual = cxxJson::deserialize<TestTypes::BooObjectWithOptional>(json_);

    ASSERT_TRUE(actual.opt_foo.is_initialized());
    EXPECT_THAT(5, Eq(actual.opt_foo.get().i));
    EXPECT_TRUE(actual.opt_foo.get().b);
    EXPECT_THAT("str", Eq(actual.opt_foo.get().str));
}
