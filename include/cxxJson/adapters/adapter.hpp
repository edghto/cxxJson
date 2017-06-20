#ifndef CXXJSON_ADAPTERS_ADAPTER_HPP
#define CXXJSON_ADAPTERS_ADAPTER_HPP

namespace cxxJson {
namespace adapters {

template<typename ValueType, typename Json>
inline ValueType getScalar(const Json& json);

template<typename Json, typename ValueType>
inline void setScalar(Json& json, ValueType& val);

template<typename Json, typename Functor>
inline void iterateArray(const Json& json, Functor f);

template<typename Json>
inline void appendArray(Json& json, const Json& item);

template<typename Json, typename Member>
inline Json getObjectMember(const Json& json, const Member& m);

template<typename Json, typename Member, typename ValueType>
inline void setObjectMember(Json& json, Member& m, ValueType& item);

} // namespace adapters
} // namespace cxxJson


#if 1 ||defined(WITH_RAPIDJSON)
#include <cxxJson/adapters/rapidjson.hpp>
#endif


#endif // CXXJSON_ADAPTERS_ADAPTER_HPP