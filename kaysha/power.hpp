#ifndef KAYSHA_POWER_HPP
#define KAYSHA_POWER_HPP
#include <type_traits>
#include <cstdint>
#include "tag.hpp"
#include "differentiation.hpp"
#include "addition.hpp"
#include "multiplication.hpp"

namespace kaysha
{
namespace detail
{
template<typename Real, std::uint64_t N>
struct power_impl
{
    static constexpr Real invoke(const Real x) noexcept
    {
        return x * power_impl<Real, N-1>::invoke(x);
    }
};
template<typename Real>
struct power_impl<Real, 0>
{
    static constexpr Real invoke(const Real) noexcept
    {
        return Real(1);
    }
};
} // detail

template<typename Term, std::int64_t N>
struct power_of: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr power_of(const Term& t) noexcept: term(t) {}
    constexpr power_of(power_of const&) noexcept = default;
    constexpr power_of(power_of &&)     noexcept = default;
    power_of& operator=(power_of const&) noexcept = default;
    power_of& operator=(power_of &&)     noexcept = default;
    ~power_of() noexcept = default;

    constexpr value_type operator()(value_type x) const noexcept
    {
        return N >= 0 ? detail::power_impl<value_type, N>::invoke(term(x)) :
            value_type(1) / detail::power_impl<value_type, N>::invoke(term(x));
    }
    Term term;
};

template<typename Term, std::int64_t N>
struct differentiation<power_of<Term, N>>
{
    using value_type     = typename Term::value_type;
    using antiderivative = power_of<Term, N>;
    using type           = multiplication<constant<value_type>, power_of<Term, N-1>>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(constant<value_type>(value_type(N)),
                    power_of<Term, N-1>(ad.term));
    }
};

template<typename Term>
struct differentiation<power_of<Term, 0>>
{
    using value_type     = typename Term::value_type;
    using antiderivative = power_of<Term, 0>;
    using type           = zero<value_type>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return zero<value_type>();
    }
};


template<std::int64_t N, typename Term>
constexpr typename std::enable_if<
    is_kaysha_type<Term>::value, power_of<Term, N>
    >::type
power(const Term& t) noexcept
{
    return power_of<Term, N>(t);
}

} // kaysha
#endif// KAYSHA_MULTIPLY_HPP
