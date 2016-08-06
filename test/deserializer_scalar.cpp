#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace ::testing;

template<typename ScalarType>
using ScalarDeserializer = cxxJson::detail::ScalarDeserializer<ScalarType>;


namespace {

class ScalarDeserializerTest : public Test
{
public:
    template<typename T>
    void check(T t)
    {
        json_.put("", t);
        auto expected = t;
        auto actual = ScalarDeserializer<T>::deserialize(json_);
        EXPECT_THAT(expected, Eq(actual));
    }

protected:
    boost::property_tree::ptree json_;
};

}

TEST_F(ScalarDeserializerTest, integer)
{
    int in = 5;
    check(in);
}

TEST_F(ScalarDeserializerTest, double)
{
    double in = 2.5;
    check(in);
}

TEST_F(ScalarDeserializerTest, bool)
{
    bool in = true;
    check(in);
}

TEST_F(ScalarDeserializerTest, string)
{
    std::string in = "foo";
    check(in);
}
