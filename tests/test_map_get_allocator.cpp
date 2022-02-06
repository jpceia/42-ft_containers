/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_get_allocator.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:39:48 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 00:12:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
# include <map>
  namespace ft = std;
#else
# include "map.hpp"
#endif

// map::get_allocator

int main()
{
    int psize;
    ft::map<char, int> mymap;
    ft::pair<const char, int> *p;

    // allocate an array of 5 elements using mymap's allocator:
    p = mymap.get_allocator().allocate(5);

    // assign some values to array
    psize = sizeof(ft::map<char, int>::value_type) * 5;

    std::cout << "The allocated array has a size of " << psize << " bytes.\n";

    mymap.get_allocator().deallocate(p, 5);

    return 0;
}
