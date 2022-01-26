/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_insert.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:49:58 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/26 16:36:40 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
    # include <vector>
    namespace ft = std;
#else
    # include "vector.hpp"
#endif

template <typename T>
void print_vector(ft::vector<T> const& v)
{
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
}

int main()
{
    ft::vector<int> myvector (3,100); 
    ft::vector<int>::iterator it;
    print_vector(myvector);
    
    it = myvector.begin();
    it = myvector.insert ( it , 200 );
    print_vector(myvector);
    
    myvector.insert (it,2,300);
    print_vector(myvector);
    
    // "it" no longer valid, get a new one:
    it = myvector.begin();

    ft::vector<int> anothervector (2,400);
    myvector.insert (it+2,anothervector.begin(),anothervector.end());
    print_vector(myvector);

    int myarray [] = { 501,502,503 };
    myvector.insert (myvector.begin(), myarray, myarray+3);
    print_vector(myvector);

    return 0;
}
