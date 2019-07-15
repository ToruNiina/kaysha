#ifndef KAYSHA_CONSTANT_HPP
#define KAYSHA_CONSTANT_HPP
#include <type_traits>
#include "differentiation.hpp"

namespace kaysha
{

template<typename T>
struct constant : public kaysha_type<T>
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr constant() noexcept = default;
    constexpr constant(const value_type x) noexcept: v(x) {}
    constexpr constant(constant const&) noexcept = default;
    constexpr constant(constant &&)     noexcept = default;
    constant& operator=(constant const&) noexcept = default;
    constant& operator=(constant &&)     noexcept = default;
    ~constant() noexcept = default;

    constexpr value_type operator()(value_type) const noexcept {return v;}

    value_type eval(value_type x) const noexcept override {return (*this)(x);}

    value_type v;
};

// one of the special values.
template<typename T>
struct zero : public kaysha_type<T>
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr zero()  noexcept = default;
    constexpr zero(zero const&) noexcept = default;
    constexpr zero(zero &&)     noexcept = default;
    zero& operator=(zero const&) noexcept = default;
    zero& operator=(zero &&)     noexcept = default;
    ~zero() noexcept = default;

    constexpr value_type operator()(value_type) const noexcept {return 0;}

    value_type eval(value_type x) const noexcept override {return (*this)(x);}
};
// ditto.
template<typename T>
struct one : public kaysha_type<T>
{
    static_assert(std::is_floating_point<T>::value, "");
    using value_type = T;

    constexpr one()  noexcept = default;
    constexpr one(one const&) noexcept = default;
    constexpr one(one &&)     noexcept = default;
    one& operator=(one const&) noexcept = default;
    one& operator=(one &&)     noexcept = default;
    ~one() noexcept = default;

    constexpr value_type operator()(value_type) const noexcept {return 1;}

    value_type eval(value_type x) const noexcept override {return (*this)(x);}
};

template<typename T>
struct differentiation<constant<T>>
{
    using antiderivative = constant<T>;
    using type           = zero<T>;
    using value_type     = typename type::value_type;
    static constexpr type make(const antiderivative&) noexcept {return type{};}
};
template<typename T>
struct differentiation<zero<T>>
{
    using antiderivative = zero<T>;
    using type           = zero<T>;
    using value_type     = typename type::value_type;
    static constexpr type make(const antiderivative&) noexcept {return type{};}
};
template<typename T>
struct differentiation<one<T>>
{
    using antiderivative = one<T>;
    using type           = zero<T>;
    using value_type     = typename type::value_type;
    static constexpr type make(const antiderivative&) noexcept {return type{};}
};

} // kaysha
#endif//KAYSHA_CONSTANT_HPP
