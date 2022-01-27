/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexicographical_compare.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:29:40 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 07:49:12 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lexicographical_compare example
#include <iostream>     // std::cout, std::boolalpha

#include <cctype>       // std::tolower

#if USE_STL
    #include <algorithm>    // std::lexicographical_compare
    namespace ft = std;
#else
    #include "iterator/lexicographical_compare.hpp"
#endif

// a case-insensitive comparison function:
bool mycomp (char c1, char c2)
{
    return std::tolower(c1) < std::tolower(c2);
}

int main ()
{
    char foo[] = "Apple";
    char bar[] = "apartment";

    std::cout << std::boolalpha;

    std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

    std::cout << "Using default comparison (operator<): ";
    std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
    std::cout << '\n';

    std::cout << "Using mycomp as comparison object: ";
    std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
    std::cout << '\n';

    return 0;
}
