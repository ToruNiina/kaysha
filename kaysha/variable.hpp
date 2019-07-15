#ifndef KAYSHA_VARIABLE_HPP
#define KAYSHA_VARIABLE_HPP
#include <type_traits>
#include "differentiation.hpp"
#include "constant.hpp"

namespace kaysha
{

template<typename T>
struct variable: public kaysha_type<T>
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr variable()  noexcept = default;
    constexpr variable(variable const&) noexcept = default;
    constexpr variable(variable &&)     noexcept = default;
    variable& operator=(variable const&) noexcept = default;
    variable& operator=(variable &&)     noexcept = default;
    ~variable() noexcept = default;

    constexpr value_type operator()(value_type x) const noexcept {return x;}

    value_type eval(value_type x) const noexcept override {return (*this)(x);}
};

// dx/dx = 1
template<typename T>
struct differentiation<variable<T>>
{
    using antiderivative = variable<T>;
    using type           = one<T>;
    using value_type     = typename type::value_type;
    static constexpr type make(const antiderivative&) noexcept {return type{};}
};

} // kaysha
#endif// KAYSHA_VARIABLE_HPP
