/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:42:16 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/20 02:51:37 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    class pair
    {
        public:
            pair(T1 t1, T t2);
            pair(const pair &rhs);
            ~pair(void);
            
            pair &operator=(const pair &rhs);

            T1 first;
            T2 second;
    };
} // namespace ft

#endif
