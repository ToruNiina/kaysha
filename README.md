# Kaysha

Kaysha is a tiny automatic differentiation library.

Automatic differentiation will be performed at a compile time.

## Usage

```cpp
#include <kaysha/kaysha.hpp>
#include <iostream>

int main()
{
    constexpr auto x  = kaysha::variable<double>{};
    constexpr auto _2 = kaysha::constant<double>{2.0};
    constexpr auto _1 = kaysha::constant<double>{1.0};

    constexpr auto f = x * x + _2 * x + _1;

    std::cout << "f(x) = x^2 + 2x + 1" << std::endl;
    std::cout << "f(1) = " << f(1.0)   << std::endl;
    std::cout << "f(2) = " << f(2.0)   << std::endl;
    std::cout << "f(3) = " << f(3.0)   << std::endl;
    std::cout << "f(4) = " << f(4.0)   << std::endl;

    constexpr auto df = kaysha::differentiate(f);

    std::cout << "f'(x) = 2x + 2"       << std::endl;
    std::cout << "f'(1) = " << df(1.0)  << std::endl;
    std::cout << "f'(2) = " << df(2.0)  << std::endl;
    std::cout << "f'(3) = " << df(3.0)  << std::endl;
    std::cout << "f'(4) = " << df(4.0)  << std::endl;

    constexpr auto ddf = kaysha::differentiate(df);

    std::cout << "f''(x) = 2"            << std::endl;
    std::cout << "f''(1) = " << ddf(1.0) << std::endl;
    std::cout << "f''(2) = " << ddf(2.0) << std::endl;
    std::cout << "f''(3) = " << ddf(3.0) << std::endl;
    std::cout << "f''(4) = " << ddf(4.0) << std::endl;

    return 0;
}
```

## How it works

The main idea is inspired by the "Expression-template" technique. It enables
the human-readable code to skip needless calculations by emulating syntax-tree
with templatized proxy classes.

Kaysha also constructs a syntax tree by overloading the arithmatic operators.
Then the function, named `differentiate`, transforms the tree into the
derivative of the original tree at the type level.

A brief example of the idea is demonstrated in the following snippet (the actual
code looks a bit more complicated than this).

```cpp
template<typename L, typename R>
struct addition
{
    value_type operator()(const value_type x) {return lhs(x) + rhs(x);}

    L lhs;
    R rhs;
};
template<typename L, typename R>
struct differentiate<addition<L, R>>
{
    // d(f(x) + g(x)) / dx = df/dx + dg/dx
    using type = addition<typename differentiate<L>::type,
                          typename differentiate<R>::type>;
};

template<typename L, typename R>
addition<L, R> operator+(const L&, const R&);

template<typename L, typename R>
addition<differentiation<L>, differentiation<R>>
differentiate(const addition<L, R>&);
```

## Why?

Just for fun.

## Supported functions

- `operator+`
- `operator-(unary negation)`
- `operator-(binary subtraction)`
- `operator*`
- `operator/`
- `kaysha::pow`
- `kaysha::sqrt`
- `kaysha::exp`
- `kaysha::log`
- `kaysha::sin`
- `kaysha::cos`
- `kaysha::tan`
- `kaysha::zero (constant value)`
- `kaysha::one (constant value)`
- `kaysha::two (constant value)`

## Licensing terms

This product is licensed under the terms of the [MIT License](LICENSE).

- Copyright (c) 2019 Toru Niina

All rights reserved.
