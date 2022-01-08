/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:18:59 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:18:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.cplusplus.com/reference/iterator/iterator_traits/

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include "random_access_iterator_tag.hpp"

namespace ft
{
    template <typename Iterator>
    class iterator_traits
    {
    public:
        // Member types
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    // Pointer specialization
    template <typename T>
    class iterator_traits<T*>
    {
    public:
        // Member types
        typedef T                                       value_type;
        typedef ptrdiff_t                               difference_type;
        typedef T*                                      pointer;
        typedef T&                                      reference;
        typedef random_access_iterator_tag              iterator_category;
    };

    // Const pointer specialization
    template <typename T>
    class iterator_traits<const T*>
    {
    public:
        // Member types
        typedef T                                       value_type;
        typedef ptrdiff_t                               difference_type;
        typedef const T*                                pointer;
        typedef const T&                                reference;
        typedef random_access_iterator_tag              iterator_category;
    };
}

#endif
