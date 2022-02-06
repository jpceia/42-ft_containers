/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_lower_upper_bound.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 01:01:55 by jpceia           ###   ########.fr       */
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
    ft::set<int>::iterator itlow, itup;

    for (int i = 1; i < 10; i++)
        myset.insert(i * 10);       // 10 20 30 40 50 60 70 80 90

    itlow = myset.lower_bound(30);  //      ^
    itup = myset.upper_bound(60);   //                  ^

    myset.erase(itlow, itup);       // 10 20 70 80 90

    std::cout << "myset contains:";
    for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}
