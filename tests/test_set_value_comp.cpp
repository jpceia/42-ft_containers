/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_value_comp.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:59:28 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 01:02:14 by jpceia           ###   ########.fr       */
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

    ft::set<int>::value_compare mycomp = myset.value_comp();

    for (int i = 0; i <= 5; i++)
        myset.insert(i);

    std::cout << "myset contains:";

    int highest = *myset.rbegin();
    ft::set<int>::iterator it = myset.begin();
    do
    {
        std::cout << ' ' << *it;
    } while (mycomp(*(++it), highest));

    std::cout << '\n';

    return 0;
}
