/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_constructor.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 01:02:24 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
# include <vector>
# include <stack>
  namespace ft = std;
#else
# include "vector.hpp"
# include "stack.hpp"
#endif

int main()
{
    ft::vector<int> myvector(2, 200); // vector with 2 elements

    ft::stack<int> first; // empty stack

    ft::stack<int, ft::vector<int> > second; // empty stack using vector
    ft::stack<int, ft::vector<int> > third(myvector);

    std::cout << "size of first: "  << first.size()  << '\n';
    std::cout << "size of second: " << second.size() << '\n';
    std::cout << "size of third: "  << third.size()  << '\n';

    return 0;
}
