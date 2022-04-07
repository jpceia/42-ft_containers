/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:39:54 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/08 03:33:23 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
    template <typename T, typename Container = vector<T> >
    class stack
    {
    public:
        typedef T                                   value_type;
        typedef Container                           container_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;
        typedef typename Container::size_type       size_type;

        explicit stack(const container_type& c = container_type())
            : c(c)
        {}

        ~stack() {}

        bool empty() const
        {
            return c.empty();
        }

        size_type size() const
        {
            return c.size();
        }

        reference top()
        {
            return c.back();
        }

        const_reference top() const
        {
            return c.back();
        }

        void push(const value_type& val)
        {
            c.push_back(val);
        }

        void pop()
        {
            c.pop_back();
        }

        // ---------------------------------------------------------------------
        //                          Relational operators
        // ---------------------------------------------------------------------

        friend bool operator== (const stack& lhs, const stack& rhs)
        {
            return lhs.c == rhs.c;
        }

        friend bool operator!= (const stack& lhs, const stack& rhs)
        {
            return !(lhs == rhs);
        }

        friend bool operator<  (const stack& lhs, const stack& rhs)
        {
            return lhs.c < rhs.c;
        }

        friend bool operator<= (const stack& lhs, const stack& rhs)
        {
            return lhs.c <= rhs.c;
        }

        friend bool operator>  (const stack& lhs, const stack& rhs)
        {
            return lhs.c > rhs.c;
        }

        friend bool operator>= (const stack& lhs, const stack& rhs)
        {
            return lhs.c >= rhs.c;
        }

    protected:

        // Member variables
        container_type c;
    };

    // Swap function
    template <typename T, typename Container>
    void swap(stack<T, Container>& lhs, stack<T, Container>& rhs)
    {
        lhs.swap(rhs);
    }

    // -------------------------------------------------------------------------
} // namespace ft

#endif
