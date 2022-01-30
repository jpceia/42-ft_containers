/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_value_comp.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 14:48:43 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <map>
    namespace ft = std;
#else
    # include "map.hpp"
#endif

int main ()
{
    ft::map<char,int> mymap;

    mymap['x']=1001;
    mymap['y']=2002;
    mymap['z']=3003;

    std::cout << "mymap contains:\n";

    ft::pair<char,int> highest = *mymap.rbegin();          // last element

    ft::map<char,int>::iterator it = mymap.begin();
    do {
        std::cout << it->first << " => " << it->second << '\n';
    } while ( mymap.value_comp()(*it++, highest) );

    return 0;
}