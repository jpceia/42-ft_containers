/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_constructor.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/05 21:17:36 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <set>
    namespace ft = std;
#else
    # include "set.hpp"
#endif

bool fncomp (int lhs, int rhs)
{
    return lhs < rhs;
}

struct classcomp
{
    bool operator() (const int& lhs, const int& rhs) const
    {
        return lhs<rhs;
    }
};

int main ()
{
    ft::set<int> first;                           // empty set of ints

    int myints[]= {10,20,30,40,50};
    ft::set<int> second (myints,myints+5);        // range

    ft::set<int> third (second);                  // a copy of second

    ft::set<int> fourth (second.begin(), second.end());  // iterator ctor.

    ft::set<int, classcomp> fifth;                 // class as Compare

    bool(*fn_pt)(int,int) = fncomp;
    ft::set<int, bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

    return 0;
}
