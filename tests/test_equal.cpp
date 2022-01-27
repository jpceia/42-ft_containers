/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_equal.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:29:40 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 07:51:41 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lexicographical_compare example
#include <iostream>     // std::cout, std::boolalpha

#include <cctype>       // std::tolower

#if USE_STL
    # include <algorithm>    // std::lexicographical_compare
    # include <vector>
    namespace ft = std;
#else
    # include "iterator/equal.hpp"
    # include "vector.hpp"
#endif

bool mypredicate (int i, int j) {
  return (i==j);
}

int main () {
    int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
    ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

    // using default comparison:
    if ( ft::equal (myvector.begin(), myvector.end(), myints) )
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";

    myvector[3]=81;                                 // myvector: 20 40 60 81 100

    // using predicate comparison:
    if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
        std::cout << "The contents of both sequences are equal.\n";
    else
        std::cout << "The contents of both sequences differ.\n";

    return 0;
}
