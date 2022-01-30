/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_size.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 12:55:11 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 13:07:49 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <map>
    namespace ft = std;
#else
    # include "map.hpp"
#endif

// map::size

int main ()
{
    ft::map<char,int> mymap;
    mymap['a']=101;
    mymap['b']=202;
    mymap['c']=302;

    std::cout << "mymap.size() is " << mymap.size() << '\n';

    return 0;
}
