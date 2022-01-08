/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:37:53 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:44:47 by jpceia           ###   ########.fr       */
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
    struct is_integral : public integral_constant<
        bool,
        is_integral<T>::value || std::is_enum<T>::value>
    {};
}

#endif
