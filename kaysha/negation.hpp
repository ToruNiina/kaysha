#ifndef KAYSHA_NEGATION_HPP
#define KAYSHA_NEGATION_HPP
#include <type_traits>
#include "tag.hpp"
#include "differentiation.hpp"

namespace kaysha
{

template<typename Term>
struct negation: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr negation(const Term& t) noexcept: term(t) {}
    constexpr negation(negation const&) noexcept = default;
    constexpr negation(negation &&)     noexcept = default;
    negation& operator=(negation const&) noexcept = default;
    negation& operator=(negation &&)     noexcept = default;
    ~negation() noexcept = default;

    constexpr value_type operator()(value_type x) const noexcept
    {return -term(x);}

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Term term;
};

template<typename Term>
struct differentiation<negation<Term>>
{
    using antiderivative = negation<Term>;
    using type = negation<differentiation_t<Term>>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(differentiate(ad.term));
    }
};

template<typename Term>
constexpr typename std::enable_if<is_kaysha_type<Term>::value, negation<Term>>::type
operator-(const Term& t) noexcept
{
    return negation<Term>(t);
}

} // kaysha
#endif// KAYSHA_ADDITION_HPP
