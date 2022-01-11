/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_rend.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:31:23 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/11 15:31:42 by jpceia           ###   ########.fr       */
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

    ft::vector<int>::reverse_iterator rit = myvector.rbegin();

    int i=0;
    for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
    *rit = ++i;

    std::cout << "myvector contains:";
    for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}