/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_enum.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:45:02 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:48:53 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_ENUM_HPP
# define IS_ENUM_HPP

# include "integral_constant.hpp"

// https://www.cplusplus.com/reference/type_traits/is_enum/

namespace ft
{
    template <typename T>
    struct is_enum : public integral_constant<
        bool,
        is_enum<T>::value>
    {};
}

#endif
