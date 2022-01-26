/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:50:27 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/26 11:14:40 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <iostream>

# include "iterator/lexicographical_compare.hpp"
# include "iterator/iterator_traits.hpp"
# include "iterator/reverse_iterator.hpp"

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
    template <typename T, typename Alloc = ::std::allocator<T> >
    class vector
    {
    public:
        // ---------------------------------------------------------------------
        // Member types
        // ---------------------------------------------------------------------
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::pointer            iterator;
        typedef typename allocator_type::const_pointer      const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        typedef typename allocator_type::difference_type    difference_type;  // iterator_traits<iterator>::difference_type
        typedef typename allocator_type::size_type          size_type;      // iterator_traits<iterator>::size_type

        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------

        // Default constructor
        explicit vector() :
            _alloc(allocator_type())
        {
            _begin = _end = _alloc.allocate(1);
            _end_of_storage = _begin + 1;
        }

        explicit vector(const allocator_type& alloc) :
            _alloc(alloc)
        {
            _begin = _end = _alloc.allocate(1);
            _end_of_storage = _begin + 1;
        }
        
        // Fill constructor
        explicit vector(
            size_type n,
            const value_type& val = value_type(),
            const allocator_type& alloc = allocator_type()
        ) :
            _alloc(alloc)
        {
            _begin = _alloc.allocate(n);
            _end = _end_of_storage = _begin + n;
            std::uninitialized_fill(_begin, _end, val);
        }

        /*
        // Range constructor
        template <typename InputIterator>
        vector(InputIterator first,
               ft::enable_if_t<ft::is_input_iterator<InputIterator>::value last,
               const allocator_type& alloc = allocator_type()) :
            _alloc(alloc)
        {
            size_type n = last - first;//::std::distance(first, last);
            _begin = _alloc.allocate(n);
            _end = _end_of_storage = _begin + n;
            std::uninitialized_copy(first, last, _begin);
        }
        */

        // Copy constructor
        vector(const vector& v) :
            _alloc(allocator_type())
        {
            _begin = _alloc.allocate(v.size());
            _end = _end_of_storage = _begin + v.size();
            std::uninitialized_copy(v.begin(), v.end(), _begin);
        }
        
        // Destructor
        virtual ~vector()
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

        /**
         * @brief   Returns an iterator pointing to the first element in the
         *          vector.
         * 
         * Notice that, unlike member vector::front, which returns a reference
         * to the first element, this function returns a random access iterator
         * pointing to it.
         * 
         * If the container is empty, the returned iterator value shall not be
         * dereferenced.
         * 
         * @return iterator 
         */
        iterator begin()
        {
            return _begin;
        }

        const_iterator begin() const
        {
            return _begin;
        }

        /**
         * @brief   Returns an iterator referring to the past-the-end element
         *          in the vector container.
         * 
         * The past-the-end element is the theoretical element that would follow
         * the last element in the vector. It does not point to any element, and
         * thus shall not be dereferenced.
         * 
         * Because the ranges used by functions of the standard library do not
         * include the element pointed by their closing iterator, this function
         * is often used in combination with vector::begin to specify a range
         * including all the elements in the container.
         * 
         * @return iterator 
         */
        iterator end()
        {
            return _end;
        }
        
        const_iterator end() const
        {
            return _end;
        }

        /**
         * @brief   Returns a reverse iterator pointing to the last element in
         *          the vector (i.e., its reverse beginning).
         * 
         * Reverse iterators iterate backwards: increasing them moves them
         * towards the beginning of the container.
         * 
         * rbegin points to the element right before the one that would be
         * pointed to by member end.
         * 
         * Notice that unlike member vector::back, which returns a reference to
         * this same element, this function returns a reverse random access
         * iterator.
         * 
         * @return reverse_iterator 
         */
        reverse_iterator rbegin()
        {
            return reverse_iterator(_end);
        }
        
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(_end);
        }

        /**
         * @brief   Return reverse iterator to reverse end
         * 
         * Returns a reverse iterator pointing to the theoretical element
         * preceding the first element in the vector (which is considered its
         * reverse end).
         * 
         * The range between vector::rbegin and vector::rend contains all the
         * elements of the vector (in reverse order).
         * 
         * @return reverse_iterator 
         */
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

        /**
         * @brief   Returns the number of elements in the vector.
         * 
         * This is the number of actual objects held in the vector, which is not
         * necessarily equal to its storage capacity.
         * 
         * @return size_type 
         */
        size_type size() const
        {
            return _end - _begin;
        }

        /**
         * @brief   Returns the maximum number of elements that the vector can
         *          hold.
         * 
         * This is the maximum potential size the container can reach due to
         * known system or library implementation limitations, but the container
         * is by no means guaranteed to be able to reach that size: it can still
         * fail to allocate storage at any point before that size is reached.
         * @return size_type 
         */
        size_type max_size() const 
        {
            return _alloc.max_size();
        }

        /**
         * @brief   Resizes the container so that it contains n elements.
         * 
         * @param n
         * @param val
         * 
         * If n is smaller than the current container size, the content is
         * reduced to its first n elements, removing those beyond (and
         * destroying them).
         * 
         * If n is greater than the current container size, the content is
         * expanded by inserting at the end as many elements as needed to reach
         * a size of n. If val is specified, the new elements are initialized as
         * copies of val, otherwise, they are value-initialized.
         * 
         * If n is also greater than the current container capacity, an
         * automatic reallocation of the allocated storage space takes place.
         * 
         * Notice that this function changes the actual content of the container
         * by inserting or erasing elements from it.
         */
        void resize(size_type n, value_type val = value_type())
        {
            if (n < this->size())
            {
                iterator it = _begin + n;
                for (; it != _end; ++it)
                    _alloc.destroy(it);
                _end = _begin + n;
            }
            else if (n > this->size())
            {
                _reallocate(n);
                std::uninitialized_fill(_end, _begin + n, val);
            }
        }
    
        /**
         * @brief   Returns the size of the storage space currently allocated
         *          for the vector, expressed in terms of elements.
         * 
         * This capacity is not necessarily equal to the vector size.
         * It can be equal or greater, with the extra space allowing to
         * accommodate for growth without the need to reallocate on each
         * insertion.
         * 
         * Notice that this capacity does not suppose a limit on the size of
         * the vector. When this capacity is exhausted and more is needed, it is
         * automatically expanded by the container (reallocating it storage
         * space). The theoretical limit on the size of a vector is given by
         * member max_size.
         * 
         * The capacity of a vector can be explicitly altered by calling member
         * vector::reserve.
         * 
         * @return size_type 
         */
        size_type capacity() const
        {
            return _end_of_storage - _begin;
        }           
        
        /**
         * @brief   Returns whether the vector is empty
         *          (i.e. whether its size is 0).
         * 
         * This function does not modify the container in any way. To clear the
         * content of a vector, see vector::clear.
         * 
         * @return true 
         * @return false 
         */
        bool empty() const
        {
            return _begin == _end;
        }

        /**
         * @brief   Requests that the vector capacity be at least enough to
         *          contain n elements.
         * 
         * @param n
         * 
         * If n is greater than the current vector capacity, the function causes
         * the container to reallocate its storage increasing its capacity to n
         * (or greater).
         * 
         * In all other cases, the function call does not cause a reallocation
         * and the vector capacity is not affected.
         * 
         * This function has no effect on the vector size and cannot alter its
         * elements.
         */
        void reserve(size_type n)
        {
            if (n > capacity())
                _reallocate(n);
        }

        // ---------------------------------------------------------------------
        // Element access
        // ---------------------------------------------------------------------

        /**
         * @brief   Access element
         * 
         * Returns a reference to the element at position n in the vector
         * container.
         * 
         * A similar member function, vector::at, has the same behavior as this
         * operator function, except that vector::at is bound-checked and
         * signals if the requested position is out of range by throwing an
         * out_of_range exception.
         * 
         * Portable programs should never call this function with an argument n
         * that is out of range, since this causes undefined behavior.
         * 
         * @param n 
         * @return reference 
         */
        reference operator[](size_type n)
        {
            return *(_begin + n);
        }
        
        const_reference operator[](size_type n) const
        {
            return *(_begin + n);
        }
        
        /**
         * @brief   Access element
         * 
         * Returns a reference to the element at position n in the vector.
         * 
         * The function automatically checks whether n is within the bounds of
         * valid elements in the vector, throwing an out_of_range exception if
         * it is not (i.e., if n is greater than, or equal to, its size). This
         * is in contrast with member operator[], that does not check against
         * bounds.
         * 
         * @param n 
         * @return reference 
         */
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

        /**
         * @brief   Access first element
         * 
         * Returns a reference to the first element in the vector.
         * 
         * Unlike member vector::begin, which returns an iterator to this same
         * element, this function returns a direct reference.
         * 
         * Calling this function on an empty container causes undefined
         * behavior.
         * 
         * @return reference 
         */
        reference front()
        {
            return *_begin;
        }
        
        const_reference front() const
        {
            return *_begin;
        }

        /**
         * @brief   Access last element
         * 
         * Returns a reference to the last element in the vector.
         * 
         * Unlike member vector::end, which returns an iterator just past this
         * element, this function returns a direct reference.
         * 
         * Calling this function on an empty container causes undefined
         * behavior.
         * 
         * @return reference 
         */
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

        


        /**
         * @brief   Assign vector content
         * 
         * Assigns new contents to the vector, replacing its current contents,
         * and modifying its size accordingly.
         * 
         * Any elements held in the container before the call are destroyed and
         * replaced by newly constructed elements (no assignments of elements
         * take place).
         * 
         * This causes an automatic reallocation of the allocated storage space
         * if -and only if- the new vector size surpasses the current vector
         * capacity.
         * 
         * @tparam InputIterator 
         * @param first 
         * @param last 
         */
        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last)
        {
            size_type n = last - first;
            (void)n;
            //this->clear();
            //_alloc.deallocate(_begin, _end_of_storage - _begin);
            //_begin = _end = _end_of_storage = _alloc.allocate(n);
            //std::uninitialized_copy(first, last, _begin);
        }

        // assign - fill
        void assign(size_type n, const value_type& val)
        {
            (void)n;
            (void)val;
            _alloc.destroy(_begin, _end);
            _end = _begin;
            //_reallocate(n);
            //std::uninitialized_fill(_begin, _end, val);
        }

        /**
         * @brief   Adds a new element at the end of the vector, after its
         *          current last element. The content of val is copied (or
         *          moved) to the new element.
         * 
         * @param val
         * 
         * This effectively increases the container size by one, which causes an
         * automatic reallocation of the allocated storage space if
         * -and only if- the new vector size surpasses the current vector
         * capacity.
         */
        void push_back(const value_type& val)
        {
            if (_end == _end_of_storage)
                _reallocate();
            _alloc.construct(_end, value);
            ++_end;
        }

        /**
         * @brief   Removes the last element in the vector, effectively reducing
         * the container size by one.
         * 
         * This destroys the removed element.
         */
        void pop_back()
        {
            if (_end != _begin)
            {
                --_end;
                _alloc.destroy(_end);
            }
        }

        /**
         * @brief   Insert single element
         * 
         * The vector is extended by inserting new elements before the element
         * at the specified position, effectively increasing the container size
         * by the number of elements inserted.
         * 
         * This causes an automatic reallocation of the allocated storage space
         * if -and only if- the new vector size surpasses the current vector
         * capacity.
         * 
         * Because vectors use an array as their underlying storage, inserting
         * elements in positions other than the vector end causes the container
         * to relocate all the elements that were after position to their new
         * positions. This is generally an inefficient operation compared to the
         * one performed for the same operation by other kinds of sequence
         * containers (such as list or forward_list).
         * 
         * @param position 
         * @param val 
         * @return iterator 
         */
        iterator insert(iterator position, const value_type& val)
        {
            (void)position;
            if (_end == _end_of_storage)
                _reallocate();
            // std::uninitialized_copy(position, _end, _end + 1);
            _alloc.construct(_end, val);
            ++_end;
            
            return _end - 1;
        }

        /**
         * @brief   Insert multiple elements with the same value (fill)
         * 
         * @param position 
         * @param n 
         * @param val 
         */
        void insert(iterator position, size_type n, const value_type& val)
        {
            (void)position;
            (void)val;
            // TODO: use position to check if we need to reallocate
            if (_end + n > _end_of_storage)
                _reallocate(n);
            //std::uninitialized_copy(position, _end, _end + n);
            //std::uninitialized_fill(position, position + n, val);
            _end += n;
        }
        
        // insert - range
        template <typename InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            (void)position;
            if (_end + (last - first) > _end_of_storage)
                _reallocate(last - first);
            // std::uninitialized_copy(position, _end, _end + (last - first));
            // std::uninitialized_copy(first, last, _end);
            _end += (last - first);
        }
       
        /**
         * @brief   Erase elements
         * 
         * Removes from the vector a single element (position).
         * 
         * This effectively reduces the container size by one, which is
         * destroyed.
         * 
         * Because vectors use an array as their underlying storage, erasing
         * elements in positions other than the vector end causes the container
         * to relocate all the elements after the segment erased to their new
         * positions.
         * This is generally an inefficient operation compared to the one
         * performed for the same operation by other kinds of sequence
         * containers (such as list or forward_list).
         * 
         * @param position 
         * @return iterator 
         */
        iterator erase(iterator position)
        {
            std::copy(position + 1, _end, position);
            _alloc.destroy(_end - 1);
            --_end;
            return position;
        }

        /**
         * @brief   Erase elements
         * 
         * Removes from the vector a range of elements [first, last).
         * 
         * This effectively reduces the container size by the number of elements
         * removed, which are destroyed.
         * 
         * @param first 
         * @param last 
         * @return iterator 
         */
        iterator erase(iterator first, iterator last)
        {
            iterator it = first;
            while (it != last)
            {
                _alloc.destroy(it);
                ++it;
            }
            std::copy(last, _end, first);
            _end -= (last - first);
            return first;
        }

        /**
         * @brief   Swap content
         * 
         * Exchanges the content of the container by the content of x, which is
         * another vector object of the same type. Sizes may differ.
         * 
         * After the call to this member function, the elements in this
         * container are those which were in x before the call, and the elements
         * of x are those which were in this. All iterators, references and
         * pointers remain valid for the swapped objects.
         * 
         * Notice that a non-member function exists with the same name, swap,
         * overloading that algorithm with an optimization that behaves like
         * this member function.
         * 
         * @param x 
         */
        void swap(vector& x)
        {
            // We just swap the pointers, no need to reallocate
            std::swap(_begin, x._begin);
            std::swap(_end, x._end);
            std::swap(_end_of_storage, x._end_of_storage);
        }

        /**
         * @brief   Removes all elements from the vector (which are destroyed),
         *          leaving the container with a size of 0.
         * 
         * A reallocation is not guaranteed to happen, and the vector capacity
         * is not guaranteed to change due to calling this function.
         */
        void clear()
        {
            for (iterator it = _begin; it != _end; ++it)
                _alloc.destroy(it);
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
            iterator new_begin = _alloc.allocate(new_capacity, _begin);
            std::uninitialized_copy(_begin, _end, new_begin);
            _alloc.deallocate(_begin, _end_of_storage - _begin);
            _begin = new_begin;
            _end = _begin + current_size;
            _end_of_storage = _begin + new_capacity;
        }

        void shrink_to_fit()
        {
            _reallocate(size());
        }
    };

    // ---------------------------------------------------------------------
    // Relational operators
    // ---------------------------------------------------------------------
    template <typename T, typename Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }

    template <typename T, typename Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T, typename Alloc>
    bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    
}

#endif
