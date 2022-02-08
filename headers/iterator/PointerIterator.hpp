/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PointerIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:14:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/08 16:25:04 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINTERITERATOR_HPP
# define POINTERITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft
{
    // https://stackoverflow.com/questions/6471019/can-should-i-inherit-from-an-stl-iterator
    
    template <typename T>
    class PointerIterator
    {
    public:
        // Member types
        typedef T                                  value_type;
        typedef ptrdiff_t                          difference_type;
        typedef T*                                 pointer;
        typedef T&                                 reference;
        typedef std::random_access_iterator_tag    iterator_category;
        
        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------
        PointerIterator()
            : _ptr(NULL)
        {}

        PointerIterator(T* ptr)
            : _ptr(ptr)
        {}

        PointerIterator(const PointerIterator& rhs)
            : _ptr(rhs._ptr)
        {}

        PointerIterator& operator=(const PointerIterator& rhs)
        {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        virtual ~PointerIterator()
        {}

        // ---------------------------------------------------------------------
        // Cast operators
        // ---------------------------------------------------------------------
        operator PointerIterator<const value_type>() const
        {
            return PointerIterator<const value_type>(_ptr);
        }
        
        // ---------------------------------------------------------------------
        // Arithmetic operators
        // ---------------------------------------------------------------------
        
        // Increment
        PointerIterator& operator++()
        {
            ++_ptr;
            return *this;
        }

        PointerIterator operator++(int)
        {
            PointerIterator it(*this);
            ++_ptr;
            return it;
        }

        // Decrement
        PointerIterator& operator--()
        {
            --_ptr;
            return *this;
        }
        
        PointerIterator operator--(int)
        {
            PointerIterator it(*this);
            --_ptr;
            return it;
        }

        // Addition
        PointerIterator& operator+=(const difference_type& n)
        {
            _ptr += n;
            return *this;
        }

        PointerIterator operator+(const difference_type& n) const
        {
            PointerIterator it(*this);
            it += n;
            return it;
        }

        friend PointerIterator operator+(const difference_type& n, const PointerIterator& rhs)
        {
            return rhs + n;
        }

        // Subtraction
        PointerIterator& operator-=(const difference_type& n)
        {
            _ptr -= n;
            return *this;
        }

        PointerIterator operator-(const difference_type& n) const
        {
            PointerIterator it(*this);
            it -= n;
            return it;
        }

        difference_type operator-(const PointerIterator& rhs) const
        {
            return _ptr - rhs._ptr;
        }

        // ---------------------------------------------------------------------
        // Relational operators
        // ---------------------------------------------------------------------
        bool operator==(const PointerIterator& rhs) const
        {
            return _ptr == rhs._ptr;
        }

        bool operator!=(const PointerIterator& rhs) const
        {
            return !(*this == rhs);
        }

        bool operator<(const PointerIterator& rhs) const
        {
            return _ptr < rhs._ptr;
        }
        
        bool operator<=(const PointerIterator& rhs) const
        {
            return !(rhs < *this);
        }

        bool operator>(const PointerIterator& rhs) const
        {
            return rhs < *this;
        }

        bool operator>=(const PointerIterator& rhs) const
        {
            return !(*this < rhs);
        }

        // ---------------------------------------------------------------------
        // Dereference
        // ---------------------------------------------------------------------
        reference operator*() const
        {
            return *_ptr;
        }
        
        pointer operator->() const
        {
            return _ptr;
        }

        // offset dereference operator
        reference operator[](const difference_type& n) const
        {
            return _ptr[n];
        }

    // private:
        // ---------------------------------------------------------------------
        // Member variables
        // ---------------------------------------------------------------------
        
        T* _ptr;
    };
} // namespace ft

#endif
