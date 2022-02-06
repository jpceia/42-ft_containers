/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_count.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 01:00:26 by jpceia           ###   ########.fr       */
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

    // set some initial values:
    for (int i = 1; i < 5; ++i)
        myset.insert(i * 3); // set: 3 6 9 12

    for (int i = 0; i < 10; ++i)
    {
        std::cout << i;
        if (myset.count(i) != 0)
            std::cout << " is an element of myset.\n";
        else
            std::cout << " is not an element of myset.\n";
    }

    return 0;
}
