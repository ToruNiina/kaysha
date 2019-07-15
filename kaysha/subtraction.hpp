#ifndef KAYSHA_SUBTRACTION_HPP
#define KAYSHA_SUBTRACTION_HPP
#include <type_traits>
#include "tag.hpp"
#include "differentiation.hpp"

namespace kaysha
{

template<typename Lhs, typename Rhs>
struct subtraction: public kaysha_type<common_value_type_t<Lhs, Rhs>>
{
    using lhs_value_type = typename Lhs::value_type;
    using rhs_value_type = typename Rhs::value_type;
    using value_type =
        typename std::common_type<lhs_value_type, rhs_value_type>::type;

    constexpr subtraction(const Lhs& l, const Rhs& r) noexcept: lhs(l), rhs(r) {}
    constexpr subtraction(subtraction const&) noexcept = default;
    constexpr subtraction(subtraction &&)     noexcept = default;
    subtraction& operator=(subtraction const&) noexcept = default;
    subtraction& operator=(subtraction &&)     noexcept = default;
    ~subtraction() noexcept = default;

    constexpr value_type operator()(value_type x) const noexcept
    {return lhs(x) - rhs(x);}

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Lhs lhs;
    Rhs rhs;
};

template<typename Lhs, typename Rhs>
struct differentiation<subtraction<Lhs, Rhs>>
{
    static_assert(std::is_same<
        typename Lhs::value_type, typename Rhs::value_type>::value, "");

    using antiderivative = subtraction<Lhs, Rhs>;
    using type = subtraction<differentiation_t<Lhs>, differentiation_t<Rhs>>;
    using value_type = typename type::value_type;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(differentiate(ad.lhs), differentiate(ad.rhs));
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
