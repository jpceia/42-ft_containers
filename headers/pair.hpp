/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:42:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 16:03:34 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    template <typename T1, typename T2>
    struct pair
    {
    public:
        // Member types
        typedef T1  first_type;
        typedef T2  second_type;

        // ---------------------------------------------------------------------
        //                              Constructors
        // ---------------------------------------------------------------------

        // Default constructor
        pair()
            : first(), second()
        {}

        // Copy constructor
        template<typename U, typename V>
        pair(const pair<U, V>& p)
            : first(p.first), second(p.second)
        {}

        // Initialization constructor
        pair(const first_type& x, const second_type& y)
            : first(x), second(y)
        {}

        // ---------------------------------------------------------------------
        // ~pair() {}
        
        // Assignment operator overload
        pair &operator=(const pair &rhs)
        {
            first = rhs.first;
            second = rhs.second;
            return *this;
        }

        // ---------------------------------------------------------------------
        //                          Member variables
        // ---------------------------------------------------------------------

        T1 first;
        T2 second;
    };

    // ---------------------------------------------------------------------
    //                          Relational operators
    // ---------------------------------------------------------------------


    template <typename T1, typename T2>
    bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <typename T1, typename T2>
    bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T1, typename T2>
    bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <typename T1, typename T2>
    bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(rhs < lhs);
    }

    template <typename T1, typename T2>
    bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return rhs < lhs;
    }

    template <typename T1, typename T2>
    bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs < rhs);
    }

    // ---------------------------------------------------------------------
    //                          Make_pair function
    // ---------------------------------------------------------------------

    template<typename T1, typename T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return pair<T1, T2>(x, y);
    }

} // namespace ft


#endif
