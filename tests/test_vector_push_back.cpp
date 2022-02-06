/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_push_back.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 01:06:19 by jpceia           ###   ########.fr       */
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

    myvector.push_back(1);
    myvector.push_back(2);
    myvector.push_back(3);

    std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

    return 0;
}
