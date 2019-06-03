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

// one of the special values.
template<typename T>
struct zero : public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr constant()  noexcept = default;
    constexpr ~constant() noexcept = default;
    constexpr constant(constant const&) noexcept = default;
    constexpr constant(constant &&)     noexcept = default;
    constexpr constant& operator=(constant const&) noexcept = default;
    constexpr constant& operator=(constant &&)     noexcept = default;

    constexpr value_type operator()(value_type) noexcept {return 0;}
};
// ditto.
template<typename T>
struct one : public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr constant()  noexcept = default;
    constexpr ~constant() noexcept = default;
    constexpr constant(constant const&) noexcept = default;
    constexpr constant(constant &&)     noexcept = default;
    constexpr constant& operator=(constant const&) noexcept = default;
    constexpr constant& operator=(constant &&)     noexcept = default;

    constexpr value_type operator()(value_type) noexcept {return 1;}
};

template<typename T>
struct differentiation<constant<T>>
{
    using type = zero<T>;
};

} // kaysha
#endif//KAYSHA_CONSTANT_HPP
