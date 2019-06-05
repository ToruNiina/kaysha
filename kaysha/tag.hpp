#ifndef KAYSHA_TAG_HPP
#define KAYSHA_TAG_HPP
#include <type_traits>

namespace kaysha
{
template<typename T>
struct kaysha_type
{
    using value_type = T;
    virtual value_type eval(value_type) const noexcept = 0;
};

template<typename T>
struct is_kaysha_type: public std::is_base_of<kaysha_type<typename T::value_type>, T> {};

template<typename T1, typename T2>
using common_value_type_t = typename std::common_type<
    typename T1::value_type, typename T2::value_type
    >::type;

} // kaysha
#endif// KAYSHA_TAG_HPP
