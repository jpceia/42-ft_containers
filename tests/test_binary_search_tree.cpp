/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_binary_search_tree.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 19:06:17 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
# include <map>
  namespace ft = std;
#else
# include "map.hpp"
#endif

void print_keys(const ft::map<char, int>& mymap)
{
    for (ft::map<char, int>::const_iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << ' ';
    std::cout << '\n';
}

int main()
{
    ft::map<char, int> mymap;
    mymap['t'] = 1;
    mymap['a'] = 2;
    mymap['v'] = 3;
    mymap['b'] = 4;
    mymap['i'] = 5;
    print_keys(mymap);
    mymap['e'] = 6;
    mymap['s'] = 7;
    mymap['l'] = 8;
    mymap['z'] = 9;
    mymap['u'] = 10;
    print_keys(mymap);
    mymap['w'] = 11;
    mymap['q'] = 12;
    mymap['c'] = 13;
    mymap['x'] = 14;
    mymap['j'] = 15;
    print_keys(mymap);
    mymap['p'] = 16;
    mymap['n'] = 17;
    mymap['y'] = 18;
    mymap['k'] = 19;
    mymap['m'] = 20;
    print_keys(mymap);

    mymap.erase('y');
    mymap.erase('m');
    mymap.erase('j');
    mymap.erase('k');
    mymap.erase('n');
    print_keys(mymap);
    mymap.erase('e');
    mymap.erase('u');
    mymap.erase('s');
    mymap.erase('b');
    mymap.erase('l');
    print_keys(mymap);
    mymap.erase('i');
    mymap.erase('a');
    mymap.erase('q');
    mymap.erase('w');
    mymap.erase('p');
    print_keys(mymap);
    mymap.erase('x');
    mymap.erase('c');
    mymap.erase('t');
    mymap.erase('v');
    mymap.erase('z');
    print_keys(mymap);

    return 0;
}
