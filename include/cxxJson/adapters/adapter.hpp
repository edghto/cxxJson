#ifndef CXXJSON_ADAPTERS_ADAPTER_HPP
#define CXXJSON_ADAPTERS_ADAPTER_HPP

#include <stdexcept>
#include <string>

namespace cxxJson {
namespace adapters {

class MemberNotFound : public std::runtime_error
{
public:
    MemberNotFound(const std::string& msg) : std::runtime_error(msg) {}
};

template<typename ValueType, typename Json>
inline ValueType getScalar(const Json& json);

template<typename Json, typename ValueType>
inline void setScalar(Json& json, ValueType& val);

template<typename Json, typename Functor>
inline void iterateArray(const Json& json, Functor f);

template<typename Json>
inline void appendArray(Json& json, const Json& item);

/**
 * Throws MemberNotFound
 */
template<typename Json, typename Member>
inline Json getObjectMember(const Json& json, const Member& m);

template<typename Json, typename Member, typename ValueType>
inline void setObjectMember(Json& json, Member& m, ValueType& item);

} // namespace adapters
} // namespace cxxJson


#if defined(WITH_BOOSTPTREE)
#include <cxxJson/adapters/boostptree.hpp>
#endif


#endif // CXXJSON_ADAPTERS_ADAPTER_HPP
