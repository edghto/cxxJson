#ifndef CXXJSON_CXXJSON_HPP
#define CXXJSON_CXXJSON_HPP

#include <cxxJson/deserializer.hpp>

namespace cxxJson {

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


#endif // CXXJSON_CXXJSON_HPP
