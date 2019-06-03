#ifndef KAYSHA_DIFFERENTIATION_HPP
#define KAYSHA_DIFFERENTIATION_HPP

namespace kaysha
{

template<typename T>
struct differentiation;

template<typename T>
using differentiation_t = typename differentiation<T>::type;

template<typename T>
constexpr inline differentiation_t<T> differentiate(const T& f) noexcept
{
    return differentiation<T>::make(f);
}

} // kaysha
#endif// KAYSHA_DIFFERENTIATION_HPP
