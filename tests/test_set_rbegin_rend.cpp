/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_rbegin_rend.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 00:15:57 by jpceia           ###   ########.fr       */
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
    int myints[] = {21, 64, 17, 78, 49};
    ft::set<int> myset(myints, myints + 5);

    ft::set<int>::reverse_iterator rit;

    std::cout << "myset contains:";
    for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
        std::cout << ' ' << *rit;

    std::cout << '\n';

    return 0;
}
