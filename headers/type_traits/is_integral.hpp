/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:37:53 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 07:40:45 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include "integral_constant.hpp"

// https://www.cplusplus.com/reference/type_traits/is_integral/
// https://en.cppreference.com/w/cpp/types/is_integral

namespace ft
{
    template <typename T>
    struct is_integral : false_type {};

    template <>
    struct is_integral<bool> : true_type {};

    template <>
    struct is_integral<char> : true_type {};


    template <>
    struct is_integral<wchar_t> : true_type {};

    template <>
    struct is_integral<signed char> : true_type {};

    template <>
    struct is_integral<short int> : true_type {};

    template <>
    struct is_integral<int> : true_type {};

    template <>
    struct is_integral<long int> : true_type {};


    template <>
    struct is_integral<unsigned char> : true_type {};

    template <>
    struct is_integral<unsigned short int> : true_type {};

    template <>
    struct is_integral<unsigned int> : true_type {};
    
    template <>
    struct is_integral<unsigned long int> : true_type {};

# if __cplusplus >= 201103L

    template <>
    struct is_integral<char16_t> : true_type {};

    template <>
    struct is_integral<char32_t> : true_type {};

    template <>
    struct is_integral<long long int> : true_type {};
    
    template <>
    struct is_integral<unsigned long long int> : true_type {};

# endif
}

#endif
