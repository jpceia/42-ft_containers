/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_convertible.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:24:19 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/10 00:26:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CONVERTIBLE_HPP
# define IS_CONVERTIBLE_HPP

namespace ft
{
    template <typename From, typename To>
    struct is_convertible
    {
        static const bool value = false;
    };

    template <>
    struct is_convertible<void, void>
    {
        static const bool value = true;
    };

    template <typename To>
    struct is_convertible<void, To>
    {
        static const bool value = false;
    };

    template <typename From>
    struct is_convertible<From, void>
    {
        static const bool value = false;
    };
}

#endif
