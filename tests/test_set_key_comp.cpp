/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_key_comp.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 00:15:41 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
# include <set>
  namespace ft = std;
#else
# include "set.hpp"
#endif

int main()
{
    ft::set<int> myset;
    int highest;

    ft::set<int>::key_compare mycomp = myset.key_comp();

    for (int i = 0; i <= 5; i++)
        myset.insert(i);

    std::cout << "myset contains:";

    highest = *myset.rbegin();
    ft::set<int>::iterator it = myset.begin();
    do
    {
        std::cout << ' ' << *it;
    } while (mycomp(*(++it), highest));

    std::cout << '\n';

    return 0;
}
