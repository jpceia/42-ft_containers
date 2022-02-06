/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_assignment_operator.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 00:14:15 by jpceia           ###   ########.fr       */
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
    int myints[] = {12, 82, 37, 64, 15};
    ft::set<int> first(myints, myints + 5); // set with 5 ints
    ft::set<int> second;                    // empty set

    second = first;         // now second contains the 5 ints
    first = ft::set<int>(); // and first is empty

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';

    return 0;
}
