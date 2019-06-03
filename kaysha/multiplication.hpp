#ifndef KAYSHA_MULTIPLY_HPP
#define KAYSHA_MULTIPLY_HPP
#include <type_traits>
#include "tag.hpp"
#include "differentiation.hpp"
#include "addition.hpp"

namespace kaysha
{

template<typename Lhs, typename Rhs>
struct multiplication: public kaysha_type
{
    using lhs_value_type = typename Lhs::value_type;
    using rhs_value_type = typename Rhs::value_type;
    using value_type =
        typename std::common_type<lhs_value_type, rhs_value_type>::type;

    constexpr multiplication(const Lhs& l, const Rhs& r) noexcept: lhs(l), rhs(r) {}
    constexpr multiplication(multiplication const&) noexcept = default;
    constexpr multiplication(multiplication &&)     noexcept = default;
    multiplication& operator=(multiplication const&) noexcept = default;
    multiplication& operator=(multiplication &&)     noexcept = default;
    ~multiplication() noexcept = default;

    constexpr value_type operator()(value_type x) const noexcept
    {return lhs(x) * rhs(x);}

    Lhs lhs;
    Rhs rhs;
};

template<typename Lhs, typename Rhs>
struct differentiation<multiplication<Lhs, Rhs>>
{
    static_assert(std::is_same<
        typename Lhs::value_type, typename Rhs::value_type>::value, "");

    using antiderivative = multiplication<Lhs, Rhs>;
    using type = addition<
            multiplication<differentiation<Lhs>, Rhs>,
            multiplication<differentiation<Rhs>, Lhs>
        >;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(
                multiplication<differentiation<Lhs>, Rhs>(
                    differentiation<Lhs>::make(ad.lhs), ad.rhs),
                multiplication<differentiation<Rhs>, Lhs>(
                    differentiation<Rhs>::make(ad.rhs), ad.lhs)
            );
    }
};

template<typename Lhs, typename Rhs>
constexpr typename std::enable_if<
    is_kaysha_type<Lhs>::value && is_kaysha_type<Rhs>::value, multiplication<Lhs, Rhs>
    >::type
operator*(const Lhs& l, const Rhs& r) noexcept
{
    return multiplication<Lhs, Rhs>(l, r);
}

} // kaysha
#endif// KAYSHA_MULTIPLY_HPP
