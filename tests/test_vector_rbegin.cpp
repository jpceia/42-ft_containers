/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_rbegin.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:30:37 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/11 15:31:06 by jpceia           ###   ########.fr       */
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
    ft::vector<int> myvector (5);  // 5 default-constructed ints

    int i=0;

    ft::vector<int>::reverse_iterator rit = myvector.rbegin();
    for (; rit!= myvector.rend(); ++rit)
        *rit = ++i;

    std::cout << "myvector contains:";
    for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}