#ifndef KAYSHA_TRIGONOMETRIC_HPP
#define KAYSHA_TRIGONOMETRIC_HPP
#include <type_traits>
#include <cstdint>
#include <cmath>
#include "tag.hpp"
#include "differentiation.hpp"
#include "negation.hpp"
#include "addition.hpp"
#include "constant.hpp"
#include "power.hpp"

namespace kaysha
{

template<typename Term>
struct sin_of: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr sin_of(const Term& t) noexcept: term(t) {}
    constexpr sin_of(sin_of const&) noexcept = default;
    constexpr sin_of(sin_of &&)     noexcept = default;
    sin_of& operator=(sin_of const&) noexcept = default;
    sin_of& operator=(sin_of &&)     noexcept = default;
    ~sin_of() noexcept = default;

    value_type operator()(value_type x) const noexcept
    {
        return std::sin(term(x));
    }

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Term term;
};

template<typename Term>
struct cos_of: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr cos_of(const Term& t) noexcept: term(t) {}
    constexpr cos_of(cos_of const&) noexcept = default;
    constexpr cos_of(cos_of &&)     noexcept = default;
    cos_of& operator=(cos_of const&) noexcept = default;
    cos_of& operator=(cos_of &&)     noexcept = default;
    ~cos_of() noexcept = default;

    value_type operator()(value_type x) const noexcept
    {
        return std::cos(term(x));
    }

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Term term;
};

template<typename Term>
struct differentiation<sin_of<Term>>
{
    using value_type = typename Term::value_type;

    using antiderivative = sin_of<Term>;
    using type = cos_of<Term>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(ad.term);
    }
};

template<typename Term>
struct differentiation<cos_of<Term>>
{
    using value_type = typename Term::value_type;

    using antiderivative = cos_of<Term>;
    using type = negation<sin_of<Term>>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(sin_of<Term>(ad.term));
    }
};

template<typename Term>
constexpr typename std::enable_if<is_kaysha_type<Term>::value, sin_of<Term>>::type
sin(const Term& t) noexcept
{
    return sin_of<Term>(t);
}
template<typename Term>
constexpr typename std::enable_if<is_kaysha_type<Term>::value, cos_of<Term>>::type
cos(const Term& t) noexcept
{
    return sin_of<Term>(t);
}


template<typename Term>
struct tan_of: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr tan_of(const Term& t) noexcept: term(t) {}
    constexpr tan_of(tan_of const&) noexcept = default;
    constexpr tan_of(tan_of &&)     noexcept = default;
    tan_of& operator=(tan_of const&) noexcept = default;
    tan_of& operator=(tan_of &&)     noexcept = default;
    ~tan_of() noexcept = default;

    value_type operator()(value_type x) const noexcept
    {
        return std::tan(term(x));
    }

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Term term;
};

template<typename Term>
constexpr typename std::enable_if<is_kaysha_type<Term>::value, tan_of<Term>>::type
tan(const Term& t) noexcept
{
    return tan_of<Term>(t);
}

template<typename Term>
struct differentiation<tan_of<Term>>
{
    using value_type = typename Term::value_type;

    using antiderivative = tan_of<Term>;
    using type = addition<one<value_type>, power_of<tan_of<Term>, 2>>;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return one<value_type>{} + power<2>(ad);
    }
};

} // kaysha
#endif// KAYSHA_MULTIPLY_HPP
