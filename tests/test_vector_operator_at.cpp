/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_operator_at.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:42:00 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/02 20:33:27 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <vector>
    namespace ft = std;
#else
    # include "vector.hpp"
#endif

int main()
{
    ft::vector<int> myvector (10);   // 10 zero-initialized elements

    ft::vector<int>::size_type sz = myvector.size();

    // assign some values:
    for (unsigned i=0; i<sz; i++)
        myvector[i]=i;

    // reverse vector using operator[]:
    for (unsigned i=0; i<sz/2; i++)
    {
        int temp;
        temp = myvector[sz-1-i];
        myvector[sz-1-i]=myvector[i];
        myvector[i]=temp;
    }

    std::cout << "myvector contains:";
    for (unsigned i=0; i<sz; i++)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';

    return 0;
}
