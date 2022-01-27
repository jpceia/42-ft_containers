/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:39:54 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 07:25:04 by jpceia           ###   ########.fr       */
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

        reference top()
        {
            return _c.back();
        }

        const_reference top() const
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

        template <typename _T, typename _Container>
        friend bool operator== (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

        template <typename _T, typename _Container>
        friend bool operator!= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

        template <typename _T, typename _Container>
        friend bool operator<  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

        template <typename _T, typename _Container>
        friend bool operator<= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

        template <typename _T, typename _Container>
        friend bool operator>  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

        template <typename _T, typename _Container>
        friend bool operator>= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);
        
    private:

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

    template <typename T, typename Container>
    bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
    {
        return lhs._c >= rhs._c;
    }

    // ---------------------------------------------------------------------
} // namespace ft

#endif
