/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_constructor.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 12:53:08 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <map>
    namespace ft = std;
#else
    # include "map.hpp"
#endif

bool fncomp (char lhs, char rhs)
{
    return lhs < rhs;
}

struct classcomp {
    bool operator() (const char& lhs, const char& rhs) const
    {
        return lhs < rhs;
    }
};

int main ()
{
    ft::map<char,int> first;

    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    ft::map<char, int> second (first.begin(),first.end());

    ft::map<char, int> third (second);

    ft::map<char, int, classcomp> fourth;                 // class as Compare

    bool(*fn_pt)(char,char) = fncomp;
    ft::map<char, int, bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

    return 0;
}
