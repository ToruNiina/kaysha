#ifndef KAYSHA_ADDITION_HPP
#define KAYSHA_ADDITION_HPP
#include <type_traits>
#include "tag.hpp"
#include "differentiation.hpp"

namespace kaysha
{

template<typename Lhs, typename Rhs>
struct addition: public kaysha_type
{
    using lhs_value_type = typename Lhs::value_type;
    using rhs_value_type = typename Rhs::value_type;
    using value_type =
        typename std::common_type<lhs_value_type, rhs_value_type>::type;

    constexpr addition(const Lhs& l, const Rhs& r) noexcept: lhs(l), rhs(r) {}
    constexpr addition(addition const&) noexcept = default;
    constexpr addition(addition &&)     noexcept = default;
    addition& operator=(addition const&) noexcept = default;
    addition& operator=(addition &&)     noexcept = default;
    ~addition() noexcept = default;

    constexpr value_type operator()(value_type x) const noexcept
    {return lhs(x) + rhs(x);}

    Lhs lhs;
    Rhs rhs;
};

template<typename Lhs, typename Rhs>
struct differentiation<addition<Lhs, Rhs>>
{
    static_assert(std::is_same<
        typename Lhs::value_type, typename Rhs::value_type>::value, "");

    using antiderivative = addition<Lhs, Rhs>;
    using type = addition<differentiation<Lhs>, differentiation<Rhs>>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(differentiation<Lhs>::make(ad.lhs),
                    differentiation<Rhs>::make(ad.rhs));
    }
};

template<typename Lhs, typename Rhs>
constexpr typename std::enable_if<
    is_kaysha_type<Lhs>::value && is_kaysha_type<Rhs>::value, addition<Lhs, Rhs>
    >::type
operator+(const Lhs& l, const Rhs& r) noexcept
{
    return addition<Lhs, Rhs>(l, r);
}

} // kaysha
#endif// KAYSHA_ADDITION_HPP
