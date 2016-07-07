#ifndef IF_HPP
#define IF_HPP

namespace cxxJson {

template <bool condition, typename Then, typename Else>
struct IF
{
    typedef Else type;
};

template <typename Then, typename Else>
struct IF <true, Then, Else>
{
    typedef Then type;
};

} // namespace cxxJson

#endif // IF_HPP
