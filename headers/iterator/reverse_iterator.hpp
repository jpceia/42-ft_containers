/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:05:51 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/01 10:47:33 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
    template <typename Iterator>
    class reverse_iterator
    {
    public:
        // ---------------------------------------------------------------------
        // Member types
        // ---------------------------------------------------------------------
        typedef Iterator                                                iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;

        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------

        // Default constructor
        reverse_iterator() :
            _it()
        {}
        
        // Initialization constructor
        reverse_iterator(iterator_type it) :
            _it(it)
        {}

        // Copy constructor
        template <typename Iter>
        reverse_iterator(const reverse_iterator<Iter>& it) :
            _it(it.base())
        {}

        // ---------------------------------------------------------------------

        // base
        iterator_type base() const
        {
            return _it;
        }

        // ---------------------------------------------------------------------
        // Operators
        // ---------------------------------------------------------------------
        // Dereference operator
        reference operator*() const
        {
            iterator_type tmp = _it;
            return *--tmp;
        }

        // Addition operator
        reverse_iterator operator+ (difference_type n) const
        {
            return reverse_iterator(_it - n);
        }

        // Increment operator - prefix
        reverse_iterator& operator++()
        {
            --_it;
            return *this;
        }

        // Increment operator - postfix
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            --_it;
            return tmp;
        }

        // Advance operator
        reverse_iterator operator+= (difference_type n)
        {
            _it -= n;
            return *this;
        }

        // Subtraction operator
        reverse_iterator operator- (difference_type n) const
        {
            return reverse_iterator(_it + n);
        }

        // Decrement operator - prefix
        reverse_iterator& operator--()
        {
            ++_it;
            return *this;
        }

        // Decrement operator - postfix
        reverse_iterator operator-- (int)
        {
            reverse_iterator tmp = *this;
            ++_it;
            return tmp;
        }

        // Arrow / Dereference operator
        pointer operator->() const
        {
            return &(operator*());
        }

        // At / Dereference operator with offset
        reference operator[] (difference_type n) const
        {
            return *(*this + n);
        }

    private:
        // ---------------------------------------------------------------------
        // Member variables
        // ---------------------------------------------------------------------

        iterator_type _it;
    };

    // -------------------------------------------------------------------------
    // Relational operators
    // -------------------------------------------------------------------------

    template <typename Iterator>
    bool operator== (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator>
    bool operator!= (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename Iterator>
    bool operator< (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator>
    bool operator<= (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <typename Iterator>
    bool operator> (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator>
    bool operator>= (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    // -------------------------------------------------------------------------
    // Arithmetic operators
    // -------------------------------------------------------------------------
    
    // Addition operator
    template <typename Iterator>
    reverse_iterator<Iterator> operator+ (
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& rev_it)
    {
        return rev_it + n;
    }

    // Difference operator
    template <typename Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    }
}

#endif
