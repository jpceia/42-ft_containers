/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:14:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/03 22:05:50 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <cstddef>
# include <iterator>

namespace ft
{
    // https://stackoverflow.com/questions/6471019/can-should-i-inherit-from-an-stl-iterator
    
    template <typename T>
    class random_access_iterator
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
        random_access_iterator()
            : _ptr(NULL)
        {}

        random_access_iterator(T* ptr)
            : _ptr(ptr)
        {}

        random_access_iterator(const random_access_iterator& rhs)
            : _ptr(rhs._ptr)
        {}

        random_access_iterator& operator=(const random_access_iterator& rhs)
        {
            if (this != &rhs)
                _ptr = rhs._ptr;
            return *this;
        }

        virtual ~random_access_iterator()
        {}

        // ---------------------------------------------------------------------
        // Cast operators
        // ---------------------------------------------------------------------
        operator random_access_iterator<const value_type>() const
        {
            return random_access_iterator<const value_type>(_ptr);
        }
        
        // ---------------------------------------------------------------------
        // Arithmetic operators
        // ---------------------------------------------------------------------
        
        // Increment
        random_access_iterator& operator++()
        {
            ++_ptr;
            return *this;
        }

        random_access_iterator operator++(int)
        {
            random_access_iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        // Decrement
        random_access_iterator& operator--()
        {
            --_ptr;
            return *this;
        }
        
        random_access_iterator operator--(int)
        {
            random_access_iterator tmp(*this);
            --_ptr;
            return tmp;
        }

        // Addition
        random_access_iterator& operator+=(const difference_type& n)
        {
            _ptr += n;
            return *this;
        }

        random_access_iterator operator+(const difference_type& n) const
        {
            random_access_iterator tmp(*this);
            tmp += n;
            return tmp;
        }

        friend random_access_iterator operator+(const difference_type& n, const random_access_iterator& rhs)
        {
            return rhs + n;
        }

        // Subtraction
        random_access_iterator& operator-=(const difference_type& n)
        {
            _ptr -= n;
            return *this;
        }

        random_access_iterator operator-(const difference_type& n) const
        {
            random_access_iterator tmp(*this);
            tmp -= n;
            return tmp;
        }

        difference_type operator-(const random_access_iterator& rhs) const
        {
            return _ptr - rhs._ptr;
        }

        // ---------------------------------------------------------------------
        // Relational operators
        // ---------------------------------------------------------------------
        bool operator==(const random_access_iterator& rhs) const
        {
            return _ptr == rhs._ptr;
        }

        bool operator!=(const random_access_iterator& rhs) const
        {
            return !(*this == rhs);
        }

        bool operator<(const random_access_iterator& rhs) const
        {
            return _ptr < rhs._ptr;
        }
        
        bool operator<=(const random_access_iterator& rhs) const
        {
            return !(rhs < *this);
        }

        bool operator>(const random_access_iterator& rhs) const
        {
            return rhs < *this;
        }

        bool operator>=(const random_access_iterator& rhs) const
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

    private:
        // ---------------------------------------------------------------------
        // Member variables
        // ---------------------------------------------------------------------
        
        T *_ptr;
    };
} // namespace ft

#endif
