#ifndef CXXJSON_DESERIALIZER_HPP
#define CXXJSON_DESERIALIZER_HPP

#include <type_traits>
#include <cxxJson/traits.hpp>

namespace cxxJson {
namespace detail {


template<typename S>
struct ScalarDeserializer
{
    template<typename J>
    static inline S deserialize(J& json)
    {
        std::cout << "ScalarDeserializer" << std::endl;
        S s = json.template get<S>("");
        return s;
    }
};


template<typename S>
struct ArrayDeserializer
{
    template<typename J>
    static inline S deserialize(J& json)
    {
        std::cout << "ArrayDeserializer" << std::endl;
        S s;
        return s;
    }
};


template<typename S>
struct ObjectDeserializer
{
    template<typename J>
    static inline S deserialize(J& json)
    {
        std::cout << "ObjectDeserializer" << std::endl;
        S s;
        return s;
    }
};

template<typename S>
using Deserializer = typename std::conditional<traits::isObject<S>{},
                         ObjectDeserializer<S>,
                         typename std::conditional<traits::isArray<S>{},
                             ArrayDeserializer<S>,
                             ScalarDeserializer<S>
                         >::type
                     >::type;


} // namespace detail
} // namespace cxxJson

#endif // CXXJSON_DESERIALIZER_HPP
