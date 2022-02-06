/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_find.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 01:01:08 by jpceia           ###   ########.fr       */
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
    ft::set<int>::iterator it;

    // set some initial values:
    for (int i = 1; i <= 5; i++)
        myset.insert(i * 10); // set: 10 20 30 40 50

    it = myset.find(20);
    myset.erase(it);
    myset.erase(myset.find(40));

    std::cout << "myset contains:";
    for (it = myset.begin(); it != myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}
