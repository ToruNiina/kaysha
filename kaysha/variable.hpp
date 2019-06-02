#ifndef KAYSHA_VARIABLE_HPP
#define KAYSHA_VARIABLE_HPP
#include <type_traits>
#include "differentiation.hpp"

namespace kaysha
{

template<typename T>
struct variable: public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr variable()  noexcept = default;
    constexpr ~variable() noexcept = default;
    constexpr variable(variable const&) noexcept = default;
    constexpr variable(variable &&)     noexcept = default;
    constexpr variable& operator=(variable const&) noexcept = default;
    constexpr variable& operator=(variable &&)     noexcept = default;

    constexpr value_type operator()(value_type x) noexcept {return x;}
};

// dx/dx = 1
template<typename T>
struct differentiation<variable<T>>: public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr explicit differentiation(const variable&) noexcept = default;
    constexpr ~differentiation() noexcept = default;
    constexpr differentiation(differentiation const&) noexcept = default;
    constexpr differentiation(differentiation &&)     noexcept = default;
    constexpr differentiation& operator=(differentiation const&) noexcept = default;
    constexpr differentiation& operator=(differentiation &&)     noexcept = default;

    constexpr value_type operator()(value_type x) noexcept
    {return static_cast<value_type>(1);}
};

} // kaysha
#endif// KAYSHA_VARIABLE_HPP
