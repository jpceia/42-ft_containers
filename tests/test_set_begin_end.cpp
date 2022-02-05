/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_begin_end.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/05 21:34:06 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <set>
    namespace ft = std;
#else
    # include "set.hpp"
#endif

int main ()
{
    int myints[] = {75,23,65,42,13};
    ft::set<int> myset (myints,myints+5);

    std::cout << "myset contains:";
    for (ft::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';

    return 0;
}
