/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_integral_constant.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:16:57 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/26 21:22:03 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout, std::boolalpha

#if USE_STL
    #include <type_traits>    // std::lexicographical_compare
    namespace ft = std;
#else
    #include "type_traits/integral_constant.hpp"
#endif

template <unsigned n>
struct factorial : ft::integral_constant<int,n * factorial<n-1>::value> {};

template <>
struct factorial<0> : ft::integral_constant<int,1> {};

int main() {
    std::cout << factorial<5>::value;  // constexpr (no calculations on runtime)
    return 0;
}
