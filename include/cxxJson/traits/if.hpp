#ifndef CXXJSON_TRAITS_IF_HPP
#define CXXJSON_TRAITS_IF_HPP

#include <boost/fusion/adapted.hpp>
#include <type_traits>

namespace cxxJson {
namespace traits {

template<bool Cond, typename Then, typename Else>
using if_ = typename std::conditional<Cond, Then, Else>::type;

} // namespace traits
} // namespace cxxJson


#endif // CXXJSON_TRAITS_IF_HPP
