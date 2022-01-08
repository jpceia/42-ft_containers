/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:39:54 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/08 17:26:28 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

// #include <vector>
# include "vector.hpp"

namespace ft
{
    template <typename T, typename Container = vector<T> >
    class stack
    {
    public:
        typedef T                               value_type;
        typedef Container                       container_type;
        typedef typename Container::size_type   size_type;

        stack(const container_type& c = container_type())
            : _c(c)
        {}

        ~stack() {}

        bool empty() const
        {
            return _c.empty();
        }

        size_type size() const
        {
            return _c.size();
        }

        value_type& top()
        {
            return _c.back();
        }

        const value_type& top() const
        {
            return _c.back();
        }

        void push(const value_type& val)
        {
            _c.push_back(val);
        }

        void pop()
        {
            _c.pop_back();
        }
        
    private:
        // TODO: Add friend operators

        // Member variables
        Container _c;
    };

    // ---------------------------------------------------------------------
    //                          Relational operators
    // ---------------------------------------------------------------------
    template <typename T, typename Container>
    bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs._c == rhs._c;
    }

    template <typename T, typename Container>
    bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Container>
    bool operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs._c < rhs._c;
    }

    template <typename T, typename Container>
    bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs._c <= rhs._c;
    }

    template <typename T, typename Container>
    bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs._c > rhs._c;
    }

    // TODO: check this
    template <typename T, typename Container>
    bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs._c >= rhs._c;
    }

    // ---------------------------------------------------------------------
} // namespace ft

#endif
