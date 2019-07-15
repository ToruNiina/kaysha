#ifndef KAYSHA_EXP_HPP
#define KAYSHA_EXP_HPP
#include <type_traits>
#include <cstdint>
#include <cmath>
#include "tag.hpp"
#include "differentiation.hpp"
#include "division.hpp"

namespace kaysha
{

template<typename Term>
struct exp_of: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr exp_of(const Term& t) noexcept: term(t) {}
    constexpr exp_of(exp_of const&) noexcept = default;
    constexpr exp_of(exp_of &&)     noexcept = default;
    exp_of& operator=(exp_of const&) noexcept = default;
    exp_of& operator=(exp_of &&)     noexcept = default;
    ~exp_of() noexcept = default;

    value_type operator()(value_type x) const noexcept
    {
        return std::exp(term(x));
    }

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Term term;
};

template<typename Term>
struct differentiation<exp_of<Term>>
{
    using antiderivative = exp_of<Term>;
    using type           = multiplication<differentiation_t<Term>, exp_of<Term>>;
    using value_type     = typename type::value_type;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(differentiate(ad.term), ad.term);
    }
};

template<typename Term>
constexpr typename std::enable_if<is_kaysha_type<Term>::value, exp_of<Term>>::type
exp(const Term& t) noexcept
{
    return exp_of<Term>(t);
}

} // kaysha
#endif // KAYSHA_EXP_HPP
