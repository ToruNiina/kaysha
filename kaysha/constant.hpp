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
    constexpr constant(constant const&) noexcept = default;
    constexpr constant(constant &&)     noexcept = default;
    constexpr constant& operator=(constant const&) noexcept = default;
    constexpr constant& operator=(constant &&)     noexcept = default;
    ~constant() noexcept = default;

    constexpr value_type operator()(value_type) noexcept {return v;}

    value_type v;
};

// one of the special values.
template<typename T>
struct zero : public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr zero()  noexcept = default;
    constexpr zero(zero const&) noexcept = default;
    constexpr zero(zero &&)     noexcept = default;
    constexpr zero& operator=(zero const&) noexcept = default;
    constexpr zero& operator=(zero &&)     noexcept = default;
    ~zero() noexcept = default;

    constexpr value_type operator()(value_type) noexcept {return 0;}
};
// ditto.
template<typename T>
struct one : public kaysha_type
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr one()  noexcept = default;
    constexpr one(one const&) noexcept = default;
    constexpr one(one &&)     noexcept = default;
    constexpr one& operator=(one const&) noexcept = default;
    constexpr one& operator=(one &&)     noexcept = default;
    ~one() noexcept = default;

    constexpr value_type operator()(value_type) noexcept {return 1;}
};

template<typename T>
struct differentiation<constant<T>>
{
    using antiderivative = constant<T>;
    using type           = zero<T>;
    static constexpr type make(const antiderivative&) noexcept {return type{};}
};
template<typename T>
struct differentiation<zero<T>>
{
    using antiderivative = constant<T>;
    using type           = zero<T>;
    static constexpr type make(const antiderivative&) noexcept {return type{};}
};
template<typename T>
struct differentiation<one<T>>
{
    using antiderivative = constant<T>;
    using type           = zero<T>;
    static constexpr type make(const antiderivative&) noexcept {return type{};}
};

} // kaysha
#endif//KAYSHA_CONSTANT_HPP
