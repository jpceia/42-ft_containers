/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_find.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 14:57:16 by jpceia           ###   ########.fr       */
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
    ft::map<char,int>::iterator it;

    mymap['a']=50;
    mymap['b']=100;
    mymap['c']=150;
    mymap['d']=200;

    it = mymap.find('b');
    if (it != mymap.end())
    mymap.erase (it);

    // print content:
    std::cout << "elements in mymap:" << '\n';
    std::cout << "a => " << mymap.find('a')->second << '\n';
    std::cout << "c => " << mymap.find('c')->second << '\n';
    std::cout << "d => " << mymap.find('d')->second << '\n';

    return 0;
}