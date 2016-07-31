#ifndef CXXJSON_TRAITS_TYPE_HPP
#define CXXJSON_TRAITS_TYPE_HPP

#include <boost/fusion/adapted.hpp>
#include <type_traits>

namespace cxxJson {
namespace traits {

template<typename S>
struct isObject : std::integral_constant<bool, boost::fusion::traits::is_sequence<S>::value> {};

template<typename S>
struct isArray : std::false_type {};

template<typename S>
struct isArray<std::vector<S>> : std::true_type {};

} // namespace traits
} // namespace cxxJson


#endif // CXXJSON_TRAITS_TYPE_HPP
