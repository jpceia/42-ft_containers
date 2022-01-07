/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:50:27 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/07 22:54:31 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <iostream>

/*
 * Member types
 * ---------------------------------------------------------------------------
 * member type	          definition
 * ---------------------------------------------------------------------------
 * value_type	          The first template parameter (T)	
 * allocator_type	      The second template parameter (Alloc)
 *                        defaults to: allocator<value_type>
 * reference	          allocator_type::reference
 *                        for the default allocator: value_type&
 * const_reference	      allocator_type::const_reference
 *                        for the default allocator: const value_type&
 * pointer	              allocator_type::pointer
 *                        for the default allocator: value_type*
 * const_pointer	      allocator_type::const_pointer
 *                        for the default allocator: const value_type*
 * iterator               a random access iterator to value_type
 *                        convertible to const_iterator
 * const_iterator         a random access iterator to const value_type	
 * reverse_iterator	      reverse_iterator<iterator>	
 * const_reverse_iterator reverse_iterator<const_iterator>	
 * difference_type        a signed integral type, identical to:
 *                        iterator_traits<iterator>::difference_type
 *                        usually the same as ptrdiff_t
 * size_type              an unsigned integral type that can represent any
 *                        non-negative value of difference_type
 *                        usually the same as size_t
 */

namespace ft
{
    template <class T, class Alloc = ::std::allocator<T> >
    class vector
    {
    public:
        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef typename allocator_type::pointer                    iterator;
        typedef typename allocator_type::const_pointer              const_iterator;
        typedef typename ::std::reverse_iterator<iterator>          reverse_iterator;
        typedef typename ::std::reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef typename allocator_type::difference_type            difference_type;
        typedef typename allocator_type::size_type                  size_type;

        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------

        // Default constructor
        vector(const allocator_type& alloc = allocator_type()) :
            _alloc(alloc)
        {
            _begin = _end = _alloc.allocate(1);
            _end_of_storage = _begin + 1;
        }
        
        // Fill constructor
        vector(size_type n, const value_type& val = value_type(),
               const allocator_type& alloc = allocator_type()) :
            _alloc(alloc)
        {
            _begin = _alloc.allocate(n);
            _end = _end_of_storage = _begin + n;
            std::uninitialized_fill(_begin, _end, val);
        }

        // Range constructor
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type()) :
            _alloc(alloc)
        {
            size_type n = last - first; //::std::distance(first, last);
            _begin = _alloc.allocate(n);
            _end = _end_of_storage = _begin + n;
            std::uninitialized_copy(first, last, _begin);
        }

        // Copy constructor
        vector(const vector& v) :
            _alloc(allocator_type())
        {
            _begin = _alloc.allocate(v.size());
            _end = _end_of_storage = _begin + v.size();
            std::uninitialized_copy<iterator, iterator>(v.begin(), v.end(), _begin);
        }
        
        // Destructor
        ~vector()
        {
            for (iterator it = _begin; it != _end; ++it)
                _alloc.destroy(it);
            _alloc.deallocate(_begin, _end_of_storage - _begin);
        }
        
        // Assignment operator overload
        vector& operator=(const vector& rhs)
        {
            if (this != &rhs)
            {
                // _alloc.deallocate(_begin, _end_of_storage - _begin);
                _begin = _alloc.allocate(rhs.size(), _begin);
                std::uninitialized_copy(rhs.begin(), rhs.end(), _begin);
                _end = _end_of_storage = _begin + rhs.size();
            }
            return *this;
        }

        // ---------------------------------------------------------------------
        // Iterators
        // ---------------------------------------------------------------------

        // begin
        iterator begin()
        {
            return _begin;
        }
        
        const_iterator begin() const
        {
            return _begin;
        }

        // end
        iterator end()
        {
            return _end;
        }
        
        const_iterator end() const
        {
            return _end;
        }

        // rbegin
        reverse_iterator rbegin()
        {
            return reverse_iterator(_end);
        }
        
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(_end);
        }

        // rend
        reverse_iterator rend()
        {
            return reverse_iterator(_begin);
        }
        
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(_begin);
        }

        // ---------------------------------------------------------------------
        // Capacity
        // ---------------------------------------------------------------------

        // size
        size_type size() const
        {
            return _end - _begin;
        }

        // max_size
        size_type max_size() const 
        {
            return _alloc.max_size();
        }
        
        // resize
        void resize(size_type n, value_type val = value_type())
        {
            if (n < size())
            {
                _alloc.destroy(_begin + n, _end);
                _end = _begin + n;
            }
            else if (n > size())
            {
                _reallocate(n);
                std::uninitialized_fill(_end, _begin + n, val);
            }
        }

        // capacity
        size_type capacity() const
        {
            return _end_of_storage - _begin;
        }           
        
        // empty
        bool empty() const
        {
            return _begin == _end;
        }

        // reserve
        void reserve(size_type n)
        {
            if (n > capacity())
                _reallocate(n);
        }

        // ---------------------------------------------------------------------
        // Element access
        // ---------------------------------------------------------------------

        // operator[]
        reference operator[](size_type n)
        {
            return *(_begin + n);
        }
        
        const_reference operator[](size_type n) const
        {
            return *(_begin + n);
        }
        
        // at
        reference at(size_type n)
        {
            if (n >= this->size())
                throw std::out_of_range("Index out of range");
            return *(_begin + n);
        }
        
        const_reference at(size_type n) const
        {
            if (n >= this->size())
                throw std::out_of_range("Index out of range");
            return *(_begin + n);
        }

        // front
        reference front()
        {
            return *_begin;
        }
        
        const_reference front() const
        {
            return *_begin;
        }

        // back
        reference back()
        {
            return *(_end - 1);
        }
        
        const_reference back() const
        {
            return *(_end - 1);
        }

        // ---------------------------------------------------------------------
        // Modifiers
        // ---------------------------------------------------------------------


        // assign - range
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            size_type n = ::std::distance(first, last);
            _alloc.destroy(_begin, _end);
            _alloc.deallocate(_begin, _end_of_storage - _begin);
            _begin = _end = _end_of_storage = _alloc.allocate(n);
            std::uninitialized_copy(first, last, _begin);
        }

        // assign - fill
        void assign(size_type n, const value_type& val)
        {
            _alloc.destroy(_begin, _end);
            _end = _begin;
            _reallocate(n);
            std::uninitialized_fill(_begin, _end, val);
        }

        // push_back
        void push_back(const value_type& value)
        {
            if (_end == _end_of_storage)
                _reallocate();
            _alloc.construct(_end, value);
            ++_end;
        }
        
        // pop_back
        void pop_back()
        {
            if (_end != _begin)
            {
                --_end;
                _alloc.destroy(_end);
            }
        }
        
        // insert - single element
        iterator insert(const_iterator position, const value_type& val)
        {
            if (_end == _end_of_storage)
                _reallocate();
            std::uninitialized_copy(position, _end, _end + 1);
            _alloc.construct(_end, val);
            ++_end;
            
            return _end - 1;
        }
        
        // insert - fill
        void insert(const_iterator position, size_type n, const value_type& val)
        {
            if (_end + n > _end_of_storage)
                _reallocate(n);
            std::uninitialized_copy(position, _end, _end + n);
            std::uninitialized_fill(_end, _end + n, val);
            _end += n;
        }
        
        // insert - range
        template <class InputIterator>
        void insert(const_iterator position, InputIterator first, InputIterator last)
        {
            if (_end + (last - first) > _end_of_storage)
                _reallocate(last - first);
            std::uninitialized_copy(position, _end, _end + (last - first));
            std::uninitialized_copy(first, last, _end);
            _end += (last - first);
        }
        
        // erase - single element
        iterator erase(const_iterator position)
        {
            std::copy(position + 1, _end, position);
            _alloc.destroy(_end - 1);
            --_end;
            return position;
        }
        
        // erase - range
        iterator erase(const_iterator first, const_iterator last) 
        {
            std::copy(last, _end, first);
            _alloc.destroy(_end - (last - first));
            _end -= (last - first);
            return first;
        }
        
        // swap
        void swap(vector& x)
        {
            std::swap(_begin, x._begin);
            std::swap(_end, x._end);
            std::swap(_end_of_storage, x._end_of_storage);
        }
        
        void clear()
        {
            _alloc.destroy(_begin, _end);
            _end = _begin;
        }

        // ---------------------------------------------------------------------
        // Allocator
        // ---------------------------------------------------------------------

        // get_allocator
        allocator_type get_allocator() const
        {
            return _alloc;
        }
        
    private:
        iterator _begin;
        iterator _end;
        iterator _end_of_storage;
        allocator_type _alloc;

        void _reallocate(size_type n = 0)
        {
            size_type new_capacity = (n == 0) ? capacity() * 2 : n;
            size_type current_size = size();
            std::cout << "reallocate from " << capacity() << " to " << new_capacity << std::endl;
            iterator new_begin = _alloc.allocate(new_capacity, _begin);
            std::uninitialized_copy(_begin, _end, new_begin);
            _alloc.deallocate(_begin, _end_of_storage - _begin);
            _begin = new_begin;
            _end = _begin + current_size;
            _end_of_storage = _begin + new_capacity;
            /*
            size_type new_capacity = (n == 0) ? capacity() * 2 : n;
            size_type current_size = size();
            std::cout << "reallocate from " << capacity() << " to " << new_capacity << std::endl;
            iterator new_begin = _alloc.allocate(new_capacity, _begin);
            _begin = new_begin;
            _end = _begin + current_size;
            _end_of_storage = _begin + new_capacity;
            */
        }

        void shrink_to_fit()
        {
            _reallocate(size());
        }
    };
}

#endif
