/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integral_constant.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:40:21 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:48:58 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGRAL_CONSTANT_HPP
# define INTEGRAL_CONSTANT_HPP

// https://www.cplusplus.com/reference/type_traits/integral_constant/

namespace ft
{
    template <typename T, T v>
    struct integral_constant
    {
        // Member types
        typedef T value_type;
        typedef integral_constant<T, v> type;

        // Member constants
        static const T value = v;

        // Member functions
        operator T() const
        {
            return (value);
        }
    };

    // Instantiations
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
}

#endif
