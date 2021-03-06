/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_max_size.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:32:48 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 01:06:55 by jpceia           ###   ########.fr       */
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

    // set some content in the vector:
    for (int i = 0; i < 100; i++)
        myvector.push_back(i);

    std::cout << "size: " << myvector.size() << "\n";
    std::cout << "capacity: " << myvector.capacity() << "\n";
    std::cout << "max_size: " << myvector.max_size() << "\n";

    return 0;
}
