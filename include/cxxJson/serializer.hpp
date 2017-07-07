#ifndef CXXJSON_SERIALIZER_HPP
#define CXXJSON_SERIALIZER_HPP

#include <cxxJson/traits.hpp>
#include <cxxJson/adapters/adapter.hpp>
#include <vector>
#include <boost/optional.hpp>

namespace cxxJson {
namespace detail {

class OptionalField
    : public std::runtime_error
{
public:
    OptionalField(std::string msg = "Missing optional field")
        : std::runtime_error(msg)
    {}
};

template<typename S, typename J>
struct Serializer;

template<typename S, typename J>
struct ScalarSerializer
{
    static inline J serialize(S& s)
    {
        J json;
        adapters::setScalar(json, s);
        return json;
    }
};

template<typename S, typename J>
struct ScalarSerializer<boost::optional<S>,J>
{
    static inline J serialize(boost::optional<S>& s)
    {
        if(!s.is_initialized())
            throw OptionalField{};

        J json;
        adapters::setScalar(json, s.get());
        return json;
    }
};

template<typename S, typename J>
struct ArraySerializer
{
    static inline J serialize(S& s)
    {
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
            try
            {
                auto item = Serializer<T,J>::serialize(t);
                adapters::setObjectMember(json_, n, item);
            }
            catch(OptionalField& )
            {
                // nothing, just keep going
            }
        }

        Json& json_;
    };

    static inline J serialize(S& s)
    {
        J json;
        Impl<J> impl(json);
        traits::Iterate<S>::for_each(s, impl);
        return json;
    }
};


template<typename S, typename J>
struct ObjectSerializer<boost::optional<S>, J>
{
    template<typename Json>
    struct Impl
    {
        Impl(Json& json)
            : json_(json) {}

        template<typename T>
        void operator()(const char* n, T& t)
        {
            try
            {
                auto item = Serializer<T,J>::serialize(t);
                adapters::setObjectMember(json_, n, item);
            }
            catch(OptionalField& )
            {
                // nothing, just keep going
            }
        }

        Json& json_;
    };

    static inline J serialize(boost::optional<S>& s)
    {
        if(!s.is_initialized())
            throw OptionalField{};

        J json;
        Impl<J> impl(json);
        traits::Iterate<S>::for_each(s.get(), impl);
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
