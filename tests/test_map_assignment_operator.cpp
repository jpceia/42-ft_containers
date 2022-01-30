/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_assignment_operator.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 12:54:11 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <map>
    namespace ft = std;
#else
    # include "map.hpp"
#endif

// assignment operator with maps
#include <iostream>
#include <map>

int main ()
{
    ft::map<char,int> first;
    ft::map<char,int> second;

    first['x']=8;
    first['y']=16;
    first['z']=32;

    second = first;               // second now contains 3 ints
    first = ft::map<char,int>();  // and first is now empty

    std::cout << "Size of first: " << first.size() << '\n';
    std::cout << "Size of second: " << second.size() << '\n';
    return 0;
}