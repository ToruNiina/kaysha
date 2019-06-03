#ifndef KAYSHA_MULTIPLY_HPP
#define KAYSHA_MULTIPLY_HPP
#include <type_traits>
#include "tag.hpp"
#include "differentiation.hpp"
#include "addition.hpp"

namespace kaysha
{

template<typename Lhs, typename Rhs>
struct multiply: public kaysha_type
{
    using lhs_value_type = typename Lhs::value_type;
    using rhs_value_type = typename Rhs::value_type;
    using value_type =
        typename std::common_type<lhs_value_type, rhs_value_type>::type;

    constexpr multiply(const Lhs& l, const Rhs& r) noexcept: lhs(l), rhs(r) {}
    constexpr ~multiply() noexcept = default;
    constexpr multiply(multiply const&) noexcept = default;
    constexpr multiply(multiply &&)     noexcept = default;
    constexpr multiply& operator=(multiply const&) noexcept = default;
    constexpr multiply& operator=(multiply &&)     noexcept = default;

    constexpr value_type operator()(value_type x) noexcept
    {return lhs(x) * rhs(x);}

    Lhs lhs;
    Rhs rhs;
};

template<typename Lhs, typename Rhs>
struct differentiation<multiply<Lhs, Rhs>>
{
    static_assert(std::is_same<
        typename Lhs::value_type, typename Rhs::value_type>::value, "");

    using type = addition<
            multiply<differentiation<Lhs>, Rhs>,
            multiply<differentiation<Rhs>, Lhs>
        >;
};

template<typename Lhs, typename Rhs>
constexpr typename std::enable_if<
    is_kaysha_type<Lhs>::value && is_kaysha_type<Rhs>::value, multiply<Lhs, Rhs>
    >::type
operator*(const Lhs& l, const Rhs& r) noexcept
{
    return multiply<Lhs, Rhs>(l, r);
}

} // kaysha
#endif// KAYSHA_MULTIPLY_HPP
