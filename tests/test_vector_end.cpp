/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_end.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:30:00 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/08 17:07:14 by jceia            ###   ########.fr       */
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
    for (int i = 1; i <= 5; i++)
        myvector.push_back(i);

    std::cout << "myvector contains:";
    ft::vector<int>::iterator it = myvector.end();
    *(it + 2) = 100;
    while (it != myvector.begin())
    {
        std::cout << ' ' << *(it - 1);
        --it;
    }
    std::cout << '\n';
    ft::vector<int>::const_iterator cit = myvector.end();
    while (cit != myvector.begin())
    {
        std::cout << ' ' << *(cit - 1);
        --cit;
    }
    std::cout << '\n';

    return 0;
}
