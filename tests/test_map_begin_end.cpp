/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_begin_end.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 12:57:20 by jpceia           ###   ########.fr       */
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
    ft::map<char,int> mymap;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    // show content:
    for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}