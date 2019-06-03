#ifndef KAYSHA_DIFFERENTIATION_HPP
#define KAYSHA_DIFFERENTIATION_HPP

namespace kaysha
{
template<typename T>
struct differentiation;

template<typename T>
using differentiation_t = typename differentiation<T>::type;

} // kaysha
#endif// KAYSHA_DIFFERENTIATION_HPP
