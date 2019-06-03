#ifndef KAYSHA_SUBTRACTION_HPP
#define KAYSHA_SUBTRACTION_HPP
#include <type_traits>
#include "tag.hpp"
#include "differentiation.hpp"

namespace kaysha
{

template<typename Lhs, typename Rhs>
struct subtraction: public kaysha_type
{
    using lhs_value_type = typename Lhs::value_type;
    using rhs_value_type = typename Rhs::value_type;
    using value_type =
        typename std::common_type<lhs_value_type, rhs_value_type>::type;

    constexpr subtraction(const Lhs& l, const Rhs& r) noexcept: lhs(l), rhs(r) {}
    constexpr ~subtraction() noexcept = default;
    constexpr subtraction(subtraction const&) noexcept = default;
    constexpr subtraction(subtraction &&)     noexcept = default;
    constexpr subtraction& operator=(subtraction const&) noexcept = default;
    constexpr subtraction& operator=(subtraction &&)     noexcept = default;

    constexpr value_type operator()(value_type x) noexcept
    {return lhs(x) - rhs(x);}

    Lhs lhs;
    Rhs rhs;
};

template<typename Lhs, typename Rhs>
struct differentiation<subtraction<Lhs, Rhs>>: public kaysha_type
{
    static_assert(std::is_same<
        typename Lhs::value_type, typename Rhs::value_type>::value, "");

    using antiderivative = subtraction<Lhs, Rhs>;
    using type = subtraction<differentiation<Lhs>, differentiation<Rhs>>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(differentiation<Lhs>::make(ad.lhs),
                    differentiation<Rhs>::make(ad.rhs));
    }
};

template<typename Lhs, typename Rhs>
constexpr typename std::enable_if<
    is_kaysha_type<Lhs>::value && is_kaysha_type<Rhs>::value, subtraction<Lhs, Rhs>
    >::type
operator-(const Lhs& l, const Rhs& r) noexcept
{
    return subtraction<Lhs, Rhs>(l, r);
}

} // kaysha
#endif// KAYSHA_SUBTRACTION_HPP
