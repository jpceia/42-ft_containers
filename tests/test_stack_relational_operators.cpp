/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_relational_operators.cpp                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:55:58 by jceia             #+#    #+#             */
/*   Updated: 2022/01/27 07:26:45 by jpceia           ###   ########.fr       */
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

int main ()
{
    ft::vector<int> vfoo(3,100);   // three ints with a value of 100
    ft::vector<int> vbar(2,200);   // two ints with a value of 200
    ft::stack<int, ft::vector<int> > foo(vfoo);
    ft::stack<int, ft::vector<int> > bar(vbar);

    if (foo==bar) std::cout << "foo and bar are equal\n";
    if (foo!=bar) std::cout << "foo and bar are not equal\n";
    if (foo< bar) std::cout << "foo is less than bar\n";
    if (foo> bar) std::cout << "foo is greater than bar\n";
    if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
    if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

    return 0;
}
