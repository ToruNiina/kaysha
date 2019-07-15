#ifndef KAYSHA_LOG_HPP
#define KAYSHA_LOG_HPP
#include <type_traits>
#include <cstdint>
#include <cmath>
#include "tag.hpp"
#include "differentiation.hpp"
#include "division.hpp"

namespace kaysha
{

template<typename Term>
struct log_of: public kaysha_type<typename Term::value_type>
{
    using value_type = typename Term::value_type;

    constexpr log_of(const Term& t) noexcept: term(t) {}
    constexpr log_of(log_of const&) noexcept = default;
    constexpr log_of(log_of &&)     noexcept = default;
    log_of& operator=(log_of const&) noexcept = default;
    log_of& operator=(log_of &&)     noexcept = default;
    ~log_of() noexcept = default;

    value_type operator()(value_type x) const noexcept
    {
        return std::log(term(x));
    }

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    Term term;
};

template<typename Term>
struct differentiation<log_of<Term>>
{
    using antiderivative = log_of<Term>;
    using type           = division<differentiation_t<Term>, Term>;
    using value_type     = typename type::value_type;

    static constexpr type make(const antiderivative& ad) noexcept
    {
        return type(differentiate(ad.term), ad.term);
    }
};

template<typename Term>
constexpr typename std::enable_if<is_kaysha_type<Term>::value, log_of<Term>>::type
log(const Term& t) noexcept
{
    return log_of<Term>(t);
}

} // kaysha
#endif // KAYSHA_LOG_HPP
