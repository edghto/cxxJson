#ifndef CXXJSON_HPP
#define CXXJSON_HPP

#include <iostream>
#include <type_traits>
#include "traits.hpp"

namespace cxxJson {

namespace detail {


template<typename S>
struct ScalarDeserializer
{
    template<typename J>
    static inline S deserialize(J json)
    {
        std::cout << "ScalarDeserializer" << std::endl;
        S s;
        return s;
    }
};


template<typename S>
struct ArrayDeserializer
{
    template<typename J>
    static inline S deserialize(J json)
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
    static inline S deserialize(J json)
    {
        std::cout << "ObjectDeserializer" << std::endl;
        S s;
        return s;
    }
};

template<bool Cond, typename Then, typename Else>
using if_ = typename std::conditional<Cond, Then, Else>::type;

template<typename S>
using Deserializer = typename std::conditional<Traits::isObject<S>{},
                         ObjectDeserializer<S>,
                         typename std::conditional<Traits::isArray<S>{},
                             ArrayDeserializer<S>,
                             ScalarDeserializer<S>
                         >::type
                     >::type;


} // namespace detail

template<typename S>
struct Json
{
    template<typename J>
    static inline S deserialize(J json)
    {
        return detail::Deserializer<S>::deserialize(json);
    }
};

} // namespace cxxJson


#endif // CXXJSON_HPP
