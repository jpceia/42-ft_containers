/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_erase.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:14:52 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/02 20:33:56 by jpceia           ###   ########.fr       */
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
    ft::vector<int> myvector;

    // set some values (from 1 to 10)
    for (int i=1; i<=10; i++)
        myvector.push_back(i);

    // erase the 6th element
    myvector.erase (myvector.begin()+5);

    // erase the first 3 elements:
    myvector.erase (myvector.begin(),myvector.begin()+3);

    std::cout << "myvector contains:";
    for (unsigned i=0; i<myvector.size(); ++i)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';

    return 0;
}
