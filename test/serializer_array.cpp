#include <gmock/gmock.h>
#include <test_types.hpp>
#include <cxxJson/cxxJson.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace ::testing;

namespace {

class ArraySerializerTest : public Test
{
public:
    template<typename T>
    void checkArray(T t)
    {
        static_assert(cxxJson::traits::isArray<T>::value, "Expected vector");

        auto serialized = cxxJson::serialize(t);
        T actual;
        for(auto it : serialized)
        {
            actual.push_back(it.second.template get<typename T::value_type>(""));
        }

        auto expected = t;
        EXPECT_THAT(expected, Eq(actual));
    }

protected:
    boost::property_tree::ptree json_;
};

}

TEST_F(ArraySerializerTest, integer)
{
    auto in = std::vector<int>({ 1, 2, 3 });
    checkArray(in);
}

TEST_F(ArraySerializerTest, string)
{
    auto in = std::vector<std::string>({ "a", "b", "c"  });
    checkArray(in);
}
