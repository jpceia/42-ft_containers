/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_const.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:54:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/02 11:54:48 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMOVE_CONST_HPP
# define REMOVE_CONST_HPP

namespace ft
{
    template <typename T>
    struct remove_const
    {
        typedef T type;
    };

    template <typename T>
    struct remove_const<const T>
    {
        typedef T type;
    };

} // namespace ft

#endif
