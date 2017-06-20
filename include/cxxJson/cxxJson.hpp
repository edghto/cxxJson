#ifndef CXXJSON_CXXJSON_HPP
#define CXXJSON_CXXJSON_HPP

#include <cxxJson/adapters/adapter.hpp>
#include <cxxJson/deserializer.hpp>
#include <cxxJson/serializer.hpp>

namespace cxxJson {

template<typename S,typename J>
static inline S deserialize(J json)
{
    return detail::Deserializer<S>::deserialize(json);
}

template<typename S>
static inline Json serialize(S s)
{
    return detail::Serializer<S,Json>::serialize(s);
}

} // namespace cxxJson


#endif // CXXJSON_CXXJSON_HPP
