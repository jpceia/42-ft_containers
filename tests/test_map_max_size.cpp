/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_max_size.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 13:08:38 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <map>
    namespace ft = std;
#else
    # include "map.hpp"
#endif

// map::max_size

int main ()
{
    int i;
    ft::map<int,int> mymap;

    if (mymap.max_size()>1000)
    {
    for (i=0; i<1000; i++) mymap[i]=0;
    std::cout << "The map contains 1000 elements.\n";
    }
    else std::cout << "The map could not hold 1000 elements.\n";

    return 0;
}