#ifndef CXXJSON_DESERIALIZER_HPP
#define CXXJSON_DESERIALIZER_HPP

#include <cxxJson/traits.hpp>
#include <vector>

namespace cxxJson {
namespace detail {

template<typename S>
struct Deserializer;

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
        for(auto i : json)
        {
            s.push_back(Deserializer<typename S::value_type>::deserialize(i.second));
        };
        return s;
    }
};


template<typename S>
struct ObjectDeserializer
{
    template<typename Json>
    struct Impl
    {
        Impl(Json& json)
            : json_(json) {}

        template<typename T>
        void operator()(const char* n, T& t)
        {
            t = json_.template get<T>(n);
        }

        Json& json_;
    };

    template<typename J>
    static inline S deserialize(J& json)
    {
        std::cout << "ObjectDeserializer" << std::endl;
        S s;
        Impl<J> impl(json);
        traits::Iterate<S>::for_each(s, impl);
        return s;
    }
};


template<typename S>
struct Deserializer : traits::if_<traits::isObject<S>{},
                         ObjectDeserializer<S>,
                         traits::if_<traits::isArray<S>{},
                             ArrayDeserializer<S>,
                             ScalarDeserializer<S>
                         >
                     >
{
};


} // namespace detail
} // namespace cxxJson

#endif // CXXJSON_DESERIALIZER_HPP
