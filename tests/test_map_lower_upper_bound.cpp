/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_lower_upper_bound.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/08 15:15:12 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if USE_STL
# include <map>
  namespace ft = std;
#else
# include "map.hpp"
#endif

// map::lower_bound/upper_bound

int main()
{
	{
		ft::map<char, int> mymap;
		ft::map<char, int>::iterator it;

		mymap['a'] = 50;
		mymap['b'] = 100;
		mymap['c'] = 150;
		mymap['d'] = 200;

		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase(it);

		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
	}
	{
		ft::map<char, int> mymap;
		char c;

		mymap['a'] = 101;
		mymap['c'] = 202;
		mymap['f'] = 303;

		for (c = 'a'; c < 'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c) > 0)
				std::cout << " is an element of mymap.\n";
			else
				std::cout << " is not an element of mymap.\n";
		}
	}
	{
		ft::map<char, int> mymap;
		ft::map<char, int>::iterator itlow, itup;

		mymap['a'] = 1;
		mymap['b'] = 2;
		// mymap['c'] = 3;
		mymap['d'] = 4;
		mymap['e'] = 5;
		mymap['f'] = 6;
		mymap['g'] = 7;
		mymap['h'] = 8;
		// mymap['i'] = 9;
		mymap['j'] = 10;

		itlow = mymap.lower_bound('c');
		itup = mymap.upper_bound('i');
		mymap.erase(itlow, itup);

		for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		ft::map<char, int> mymap;
		ft::map<char, int>::iterator itlow, itup;

		mymap['a'] = 1;
		mymap['b'] = 2;
		mymap['c'] = 3;
		mymap['d'] = 4;
		mymap['e'] = 5;
		mymap['f'] = 6;
		mymap['g'] = 7;
		mymap['h'] = 8;
		mymap['i'] = 9;
		mymap['j'] = 10;

		itlow = mymap.lower_bound('c');
		itup = mymap.upper_bound('i');

		mymap.erase(itlow, itup);

		for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}
	{
		ft::map<char, int> mymap;

		mymap['a'] = 10;
		mymap['b'] = 20;
		mymap['c'] = 30;

		ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
		ret = mymap.equal_range('b');

		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';

		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}
	return 0;
}
