/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pair_assignment_operator.cpp                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 21:23:13 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/26 10:34:12 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>       // std::string
#include <iostream>     // std::cout

#if USE_STL
    #include <utility>      // std::pair, std::make_pair
    namespace ft = std;
#else
    #include "pair.hpp"
#endif

int main () {
    ft::pair<std::string, int> planet, homeplanet;

    planet = ft::make_pair<std::string, int>("Earth",6371);

    homeplanet = planet;

    std::cout << "Home planet: " << homeplanet.first << '\n';
    std::cout << "Planet size: " << homeplanet.second << '\n';

    return 0;
}
