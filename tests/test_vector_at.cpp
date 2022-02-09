/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_at.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:43:04 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/09 01:45:49 by jpceia           ###   ########.fr       */
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
    ft::vector<int> myvector(10); // 10 zero-initialized ints

    // assign some values:
    for (unsigned i = 0; i < myvector.size(); i++)
        myvector.at(i) = i;

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++)
        std::cout << ' ' << myvector.at(i);
    std::cout << '\n';

    try
    {
        myvector.at(-1);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    try
    {
        myvector.at(11);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
