/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:28:21 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 09:49:53 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include "pair.hpp"

namespace ft
{
    template <
        class Key,                                              // map::key_type
        class T,                                                // map::mapped_type
        class Compare = std::less<Key>,                         // map::key_compare
        class Alloc = std::allocator<ft::pair<const Key, T>>    // map::allocator_type
    > class map
    {
    public:
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef pair<const key_type, mapped_type>               value_type;
        typedef typename allocator_type::size_type              size_type;
        typedef typename allocator_type::difference_type        difference_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        typedef typename allocator_type::pointer                iterator;
        typedef typename allocator_type::const_pointer          const_iterator;
        typedef typename allocator_type::pointer                reverse_iterator;
        typedef typename allocator_type::const_pointer          const_reverse_iterator;

        // Constructors
        explicit map(const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
            _comp(comp),
            _alloc(alloc)
        {
        }
            
        map(InputIterator first,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
            _comp(comp),
            _alloc(alloc)
        {
        }
            
        map(const map& rhs) :
            _comp(rhs._comp),
            _alloc(rhs._alloc)
        {
        }

        // Assignment Operators
        map& operator=(const map& rhs)
        {
            _comp = rhs._comp;
            _alloc = rhs._alloc;
            return *this;
        }

        // Destructor
        ~map(void)
        {
            
        }

        // ---------------------------------------------------------------------
        // Iterators
        // ---------------------------------------------------------------------

        /**
         * @brief   Returns an iterator referring to the first element in the
         *          map container.
         * 
         * Because map containers keep their elements ordered at all times,
         * begin points to the element that goes first following the container's
         * sorting criterion.
         * 
         * If the container is empty, the returned iterator value shall not be
         * dereferenced.
         * 
         * @return iterator 
         */
        iterator begin();
        const_iterator begin() const;
        
        /**
         * @brief   Returns an iterator referring to the past-the-end element in
         *          the map container.
         * 
         * The past-the-end element is the theoretical element that would follow
         * the last element in the map container. It does not point to any
         * element, and thus shall not be dereferenced.
         * 
         * Because the ranges used by functions of the standard library do not
         * include the element pointed by their closing iterator, this function
         * is often used in combination with map::begin to specify a range
         * including all the elements in the container.
         * 
         * If the container is empty, this function returns the same as map::begin.
         * 
         * @return iterator 
         */
        iterator end();
        const_iterator end() const;

        /**
         * @brief   Returns a reverse iterator pointing to the last element in
         *          the container (i.e., its reverse beginning).
         * 
         * Reverse iterators iterate backwards: increasing them moves them
         * towards the beginning of the container.
         * 
         * rbegin points to the element preceding the one that would be pointed
         * to by member end.
         * 
         * @return reverse_iterator 
         */
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;

        /**
         * @brief   Returns a reverse iterator pointing to the theoretical
         * element right before the first element in the map container (which is
         * considered its reverse end).
         * 
         * The range between map::rbegin and map::rend contains all the elements
         * of the container (in reverse order).
         * 
         * @return reverse_iterator 
         */
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        // ---------------------------------------------------------------------
        // Capacity
        // ---------------------------------------------------------------------
        
        /**
         * @brief   Test whether container is empty
         * 
         * Returns whether the map container is empty (i.e. whether its size is
         * 0).
         * This function does not modify the container in any way. To clear the
         * content of a map container, see map::clear.
         * 
         * @return true 
         * @return false 
         */
        bool empty() const;
        
        /**
         * @brief   Return container size
         * 
         * Returns the number of elements in the map container.
         * @return  size_type
         */
        size_type size() const;

        /**
         * @brief   Return maximum size
         * 
         * Returns the maximum number of elements that the map container can
         * hold.
         * 
         * This is the maximum potential size the container can reach due to
         * known system or library implementation limitations, but the container
         * is by no means guaranteed to be able to reach that size: it can still
         * fail to allocate storage at any point before that size is reached.
         * @return size_type 
         */
        size_type max_size() const;

        // ---------------------------------------------------------------------
        // Element Access
        // ---------------------------------------------------------------------

        /**
         * @brief Access element
         * 
         * If k matches the key of an element in the container, the function
         * returns a reference to its mapped value.
         * 
         * If k does not match the key of any element in the container, the
         * function inserts a new element with that key and returns a reference
         * to its mapped value. Notice that this always increases the container
         * size by one, even if no mapped value is assigned to the element (the
         * element is constructed using its default constructor).
         * 
         * @param key 
         * @return mapped_type& 
         */
        mapped_type& operator[](const key_type& key)
        {
            (*((this->insert(make_pair(k,mapped_type()))).first)).second;
        }
        
        const mapped_type& operator[](const key_type& key) const
        {
            (*((this->insert(make_pair(k,mapped_type()))).first)).second
        }

        // ---------------------------------------------------------------------
        // Modifiers
        // ---------------------------------------------------------------------
        
        /**
         * @brief Insert single element
         * 
         * Extends the container by inserting new elements, effectively
         * increasing the container size by the number of elements inserted.
         * 
         * Because element keys in a map are unique, the insertion operation
         * checks whether each inserted element has a key equivalent to the one
         * of an element already in the container, and if so, the element is not
         * inserted, returning an iterator to this existing element (if the
         * function returns a value).
         * 
         * An alternative way to insert elements in a map is by using member
         * function map::operator[].
         * 
         * Internally, map containers keep all their elements sorted by their
         * key following the criterion specified by its comparison object. The
         * elements are always inserted in its respective position following
         * this ordering.
         * 
         * @param value 
         * @return ft::pair<iterator, bool> 
         */
        ft::pair<iterator, bool> insert(const value_type& value);

        /**
         * @brief Insert with hint
         * 
         * @param hint 
         * @param value 
         * @return iterator 
         */
        iterator insert(const_iterator hint, const value_type& value);

        /**
         * @brief Insert range
         * 
         * @tparam InputIterator 
         * @param first 
         * @param last 
         */
        template <class InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
        insert(
            InputIterator first,
            InputIterator last
        );

        /**
         * @brief   Erase element
         * 
         * Removes from the map container a single element.
         * 
         * This effectively reduces the container size by the number of elements
         * removed, which are destroyed.
         * @param key 
         */
        void erase(const key_type& key);

        /**
         * @brief   Erase element
         * 
         * @param position 
         * @return size_type 
         */
        size_type erase(const_iterator position);

        /**
         * @brief   Erase elements
         * 
         * Removes from the map container a range of elements ([first,last)).
         * 
         * @param first 
         * @param last 
         */
        void erase(const_iterator first, const_iterator last);

        /**
         * @brief   Swap content
         * 
         * Exchanges the content of the container by the content of x, which is
         * another map of the same type. Sizes may differ.
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
         * @param other 
         */
        void swap(map& other);

        /**
         * @brief   Clear content
         * 
         * Removes all elements from the map container (which are destroyed),
         * leaving the container with a size of 0.
         */
        void clear();

        // ---------------------------------------------------------------------
        // Observers
        // ---------------------------------------------------------------------

        /**
         * @brief   Return key comparison object
         * 
         * Returns a copy of the comparison object used by the container to
         * compare keys.
         * 
         * The comparison object of a map object is set on construction. Its
         * type (member key_compare) is the third template parameter of the map
         * template. By default, this is a less object, which returns the same
         * as operator<.
         * 
         * This object determines the order of the elements in the container: it
         * is a function pointer or a function object that takes two arguments
         * of the same type as the element keys, and returns true if the first
         * argument is considered to go before the second in the strict weak
         * ordering it defines, and false otherwise.
         * 
         * Two keys are considered equivalent if key_comp returns false
         * reflexively (i.e., no matter the order in which the keys are passed
         * as arguments).
         * 
         * @return key_compare 
         */
        key_compare key_comp() const
        {
            return _comp;
        }
        
        value_compare value_comp() const;

        // ---------------------------------------------------------------------
        // Operations
        // ---------------------------------------------------------------------
        iterator find(const key_type& key);
        const_iterator find(const key_type& key) const;
        size_type count(const key_type& key) const;
        iterator lower_bound(const key_type& key);
        const_iterator lower_bound(const key_type& key) const;
        iterator upper_bound(const key_type& key);
        const_iterator upper_bound(const key_type& key) const;
        pair<iterator, iterator> equal_range(const key_type& key);
        pair<const_iterator, const_iterator> equal_range(const key_type& key) const;
        
        // ---------------------------------------------------------------------
        // Allocator
        // ---------------------------------------------------------------------
        allocator_type get_allocator() const;
    
    private:
        // Data Members
        key_compare _comp;
        allocator_type _alloc;
    };
} // namespace ft


#endif
