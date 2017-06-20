#ifndef CXXJSON_SERIALIZER_HPP
#define CXXJSON_SERIALIZER_HPP

#include <cxxJson/traits.hpp>
#include <cxxJson/adapters/adapter.hpp>
#include <vector>

namespace cxxJson {
namespace detail {

template<typename S, typename J>
struct Serializer;

template<typename S, typename J>
struct ScalarSerializer
{
    static inline J serialize(S& s)
    {
        std::cout << "ScalarSerializer" << std::endl;

        J json;
        adapters::setScalar(json, s);
        return json;
    }
};

template<typename S, typename J>
struct ArraySerializer
{
    static inline J serialize(S& s)
    {
        std::cout << "ArraySerializer" << std::endl;
        J json;
        for(auto item : s)
        {
            adapters::appendArray(json, Serializer<typename S::value_type,J>::serialize(item));
        };
        return json;
    }
};


template<typename S, typename J>
struct ObjectSerializer
{
    template<typename Json>
    struct Impl
    {
        Impl(Json& json)
            : json_(json) {}

        template<typename T>
        void operator()(const char* n, T& t)
        {
            std::cout << typeid(T).name() << " " << n << std::endl;
            auto item = Serializer<T,J>::serialize(t);
            adapters::setObjectMember(json_, n, item);
        }

        Json& json_;
    };

    static inline J serialize(S& s)
    {
        std::cout << "ObjectSerializer" << std::endl;
        J json;
        Impl<J> impl(json);
        traits::Iterate<S>::for_each(s, impl);
        return json;
    }
};


template<typename S, typename J>
struct Serializer : traits::if_<traits::isObject<S>{},
                         ObjectSerializer<S,J>,
                         traits::if_<traits::isArray<S>{},
                             ArraySerializer<S,J>,
                             ScalarSerializer<S,J>
                         >
                     >
{
};


} // namespace detail
} // namespace cxxJson

#endif // CXXJSON_SERIALIZER_HPP
