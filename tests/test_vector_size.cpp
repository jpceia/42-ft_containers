/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_size.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:31:58 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/11 15:32:18 by jpceia           ###   ########.fr       */
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
    ft::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert (myints.end(),10,100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';

    return 0;
}