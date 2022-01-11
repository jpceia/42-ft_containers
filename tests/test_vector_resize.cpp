/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_resize.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:36:10 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/11 15:36:29 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if USE_STL
    # include <vector>
    # include <iostream>
    namespace ft = std;
#else
    # include "vector.hpp"
    # include <iostream>
#endif

int main()
{
    ft::vector<int> myvector;

    // set some initial content:
    for (int i=1;i<10;i++) myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (unsigned int i=0;i<myvector.size();i++)
        std::cout << ' ' << myvector[i];
    std::cout << '\n';

    return 0;
}