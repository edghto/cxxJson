#ifndef CXXJSON_TRAITS_FOREACH_HPP
#define CXXJSON_TRAITS_FOREACH_HPP

#include <cxxJson/traits/fusion_visitor.hpp>
#include <utility>

namespace cxxJson {
namespace traits {

template<typename Struct>
struct Iterate
{
    template<typename Functor>
    static inline void for_each(Struct& s, Functor&& f)
    {
        FusionVisitor<Struct, Functor>::visit(s, std::forward<Functor>(f));
    }
};

} // namespace traits
} // namespace cxxJson


#endif // CXXJSON_TRAITS_FOREACH_HPP
