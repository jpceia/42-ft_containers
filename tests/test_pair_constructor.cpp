/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pair_constructor.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:23:13 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 07:51:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>       // std::string
#include <iostream>     // std::cout

#if USE_STL
    # include <utility>      // std::pair, std::make_pair
    namespace ft = std;
#else
    # include "pair.hpp"
#endif

int main () {
    ft::pair <std::string, double> product1;                    // default constructor
    ft::pair <std::string, double> product2("tomatoes", 2.30);  // value init
    ft::pair <std::string, double> product3(product2);          // copy constructor

    product1 = ft::make_pair(std::string("lightbulbs"), 0.99);  // using make_pair (move)

    product2.first = "shoes";                  // the type of first is string
    product2.second = 39.90;                   // the type of second is double

    std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
    std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
    std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
    
    return 0;
}
