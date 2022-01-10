/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:14:49 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 20:17:15 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
    template <typename InputIterator1, typename InputIterator2>
    bool lexicographical_compare(
        InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
                return true;
            else if (*first2 < *first1)
                return false;
            ++first1;
            ++first2;
        }
        return first1 == last1 && first2 != last2;
    }

    template <typename InputIterator1, typename InputIterator2, typename Compare>
    bool lexicographical_compare(
        InputIterator1 first1, InputIterator1 last1,
        InputIterator2 first2, InputIterator2 last2,
        Compare comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(*first1, *first2))
                return true;
            else if (comp(*first2, *first1))
                return false;
            ++first1;
            ++first2;
        }
        return first1 == last1 && first2 != last2;
    }
}

#endif
