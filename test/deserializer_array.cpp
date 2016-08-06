#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>
#include <vector>

using namespace ::testing;

template<typename ArrayType>
using ArrayDeserializer = cxxJson::detail::ArrayDeserializer<ArrayType>;

namespace {

class ArrayDeserializerTest : public Test
{
public:
    template<typename T>
    void checkArray(T t)
    {
        static_assert(cxxJson::traits::isArray<T>::value, "Expected vector");
        for(auto item : t)
        {
            boost::property_tree::ptree p;
            p.put("", item);
            json_.push_back(std::make_pair("",p));
        }

        auto expected = t;
        auto actual = ArrayDeserializer<T>::deserialize(json_);
        EXPECT_THAT(expected, Eq(actual));
    }

protected:
    boost::property_tree::ptree json_;
};

}

TEST_F(ArrayDeserializerTest, integer)
{
    auto in = std::vector<int>({1,2,3});
    checkArray(in);
}

TEST_F(ArrayDeserializerTest, string)
{
    auto in = std::vector<std::string>({"1","2","3"});
    checkArray(in);
}
