#ifndef KAYSHA_DIVISION_HPP
#define KAYSHA_DIVISION_HPP
#include <type_traits>
#include "tag.hpp"
#include "differentiation.hpp"
#include "addition.hpp"
#include "subtraction.hpp"
#include "multiplication.hpp"

namespace kaysha
{

template<typename Lhs, typename Rhs>
struct division: public kaysha_type<common_value_type_t<Lhs, Rhs>>
{
    using lhs_value_type = typename Lhs::value_type;
    using rhs_value_type = typename Rhs::value_type;
    using value_type =
        typename std::common_type<lhs_value_type, rhs_value_type>::type;

    constexpr division(const Lhs& l, const Rhs& r) noexcept: lhs(l), rhs(r) {}
    constexpr division(division const&) noexcept = default;
    constexpr division(division &&)     noexcept = default;
    division& operator=(division const&) noexcept = default;
    division& operator=(division &&)     noexcept = default;
    ~division() noexcept = default;

    constexpr value_type operator()(value_type x) const noexcept
    {return lhs(x) / rhs(x);}

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Lhs lhs;
    Rhs rhs;
};

template<typename Lhs, typename Rhs>
struct differentiation<division<Lhs, Rhs>>
{
    static_assert(std::is_same<
        typename Lhs::value_type, typename Rhs::value_type>::value, "");

    using antiderivative = division<Lhs, Rhs>;
    using type = division<subtraction<
            multiplication<differentiation_t<Lhs>, Rhs>,
            multiplication<differentiation_t<Rhs>, Lhs>
            >,
            multiplication<Rhs, Rhs>
        >;
    using value_type = typename type::value_type;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(
            differentiate(ad.lhs) * ad.rhs - differentiate(ad.rhs) * ad.lhs,
            ad.rhs * ad.rhs);
    }
};

template<typename Lhs, typename Rhs>
constexpr typename std::enable_if<
    is_kaysha_type<Lhs>::value && is_kaysha_type<Rhs>::value, division<Lhs, Rhs>
    >::type
operator/(const Lhs& l, const Rhs& r) noexcept
{
    return division<Lhs, Rhs>(l, r);
}

} // kaysha
#endif// KAYSHA_DIVISION_HPP
