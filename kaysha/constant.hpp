#ifndef KAYSHA_CONSTANT_HPP
#define KAYSHA_CONSTANT_HPP
#include <type_traits>
#include "differentiation.hpp"

namespace kaysha
{

template<typename T>
struct constant : public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr constant()  noexcept = default;
    constexpr ~constant() noexcept = default;
    constexpr constant(constant const&) noexcept = default;
    constexpr constant(constant &&)     noexcept = default;
    constexpr constant& operator=(constant const&) noexcept = default;
    constexpr constant& operator=(constant &&)     noexcept = default;

    constexpr value_type operator()(value_type) noexcept {return v;}

    value_type v;
};

// c/dx = 0
template<typename T>
struct differentiation<constant<T>> : public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;
    using tag_type   = Tag;

    constexpr explicit differentiation(const constant&) noexcept = default;
    constexpr ~differentiation() noexcept = default;
    constexpr differentiation(differentiation const&) noexcept = default;
    constexpr differentiation(differentiation &&)     noexcept = default;
    constexpr differentiation& operator=(differentiation const&) noexcept = default;
    constexpr differentiation& operator=(differentiation &&)     noexcept = default;

    constexpr value_type operator()(value_type x) noexcept
    {return static_cast<value_type>(0);}
};

} // kaysha
#endif//KAYSHA_CONSTANT_HPP
