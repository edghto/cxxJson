#ifndef CXXJSON_ADAPTERS_BOOSTPTREE_HPP
#define CXXJSON_ADAPTERS_BOOSTPTREE_HPP

#include <boost/property_tree/ptree.hpp>

namespace cxxJson {
namespace adapters {

template<typename ValueType, typename Json>
inline ValueType getScalar(const Json& json)
{
    return json.template get<ValueType>("");
}

template<typename Json, typename ValueType>
inline void setScalar(Json& json, ValueType& val)
{
    json.put("", val);
}

template<typename Json, typename Functor>
inline void iterateArray(const Json& json, Functor f)
{
    for(auto i : json)
    {
        f(i.second);
    };
}

template<typename Json>
inline void appendArray(Json& json, const Json& item)
{
    json.push_back(std::make_pair("",item));
}

template<typename Json, typename Member>
inline Json getObjectMember(const Json& json, const Member& m)
{
    return json.get_child(m);
}

template<typename Json, typename Member, typename ValueType>
inline void setObjectMember(Json& json, Member& m, ValueType& item)
{
    json.push_back(std::make_pair(m, item));
}

} // namespace adapters

using Json = boost::property_tree::ptree;

} // namespace cxxJson

#endif // CXXJSON_ADAPTERS_BOOSTPTREE_HPP
