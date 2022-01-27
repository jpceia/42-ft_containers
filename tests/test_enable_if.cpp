/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_enable_if.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:16:57 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 06:59:35 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout, std::boolalpha

#if USE_STL
    #include <type_traits>    // std::lexicographical_compare
    namespace ft = std;
#else
    # include "type_traits/enable_if.hpp"
    # include "type_traits/is_integral.hpp"
#endif

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename ft::enable_if<ft::is_integral<T>::value,bool>::type
    is_odd (T i) {return bool(i%2);}

int main()
{
    short int i = 1;    // code does not compile if type of i is not integral

    std::cout << std::boolalpha;
    std::cout << "i is odd: " << is_odd(i) << std::endl;
    return 0;
}
