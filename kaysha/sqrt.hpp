#ifndef KAYSHA_SQRT_HPP
#define KAYSHA_SQRT_HPP
#include <type_traits>
#include <cstdint>
#include <cmath>
#include "tag.hpp"
#include "differentiation.hpp"
#include "constant.hpp"
#include "multiplication.hpp"
#include "division.hpp"

namespace kaysha
{

template<typename Term>
struct sqrt_of: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr sqrt_of(const Term& t) noexcept: term(t) {}
    constexpr sqrt_of(sqrt_of const&) noexcept = default;
    constexpr sqrt_of(sqrt_of &&)     noexcept = default;
    sqrt_of& operator=(sqrt_of const&) noexcept = default;
    sqrt_of& operator=(sqrt_of &&)     noexcept = default;
    ~sqrt_of() noexcept = default;

    value_type operator()(value_type x) const noexcept
    {
        return std::sqrt(term(x));
    }

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Term term;
};

template<typename Term>
struct differentiation<sqrt_of<Term>>
{
    using antiderivative = sqrt_of<Term>;
    using value_type     = typename Term::value_type;
    using type           = division<differentiation_t<Term>,
                                    multiplication<two<value_type>, sqrt_of<Term>>>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(differentiate(ad.term), two<value_type>{} * ad);
    }
};

template<typename Term>
constexpr typename std::enable_if<is_kaysha_type<Term>::value, sqrt_of<Term>>::type
sqrt(const Term& t) noexcept
{
    return sqrt_of<Term>(t);
}

} // kaysha
#endif // KAYSHA_SQRT_HPP
