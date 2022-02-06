/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_max_size.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 00:15:49 by jpceia           ###   ########.fr       */
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
    int i;
    ft::set<int> myset;

    if (myset.max_size() > 1000)
    {
        for (i = 0; i < 1000; i++)
            myset.insert(i);
        std::cout << "The set contains 1000 elements.\n";
    }
    else
        std::cout << "The set could not hold 1000 elements.\n";

    return 0;
}
