#ifndef KAYSHA_TAG_HPP
#define KAYSHA_TAG_HPP
#include <type_traits>

namespace kaysha
{
struct kaysha_type{};

template<typename T>
struct is_kaysha_type: public std::is_base_of<kaysha_type, T> {};
} // kaysha
#endif// KAYSHA_TAG_HPP
