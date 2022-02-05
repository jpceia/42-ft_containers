/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:28:21 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/05 13:50:46 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include "tree/BinarySearchTree.hpp"
#include "type_traits/enable_if.hpp"
#include "type_traits/is_integral.hpp"
#include "pair.hpp"

namespace ft
{
    template <
        typename Key,                                              // map::key_type
        typename T,                                                // map::mapped_type
        typename Compare = std::less<Key>,                         // map::key_compare
        typename Alloc = std::allocator<ft::pair<const Key, T> >   // map::allocator_type
    >
    class map
    { 
    public:
        typedef Key                                                 key_type;
        typedef T                                                   mapped_type;
        typedef Compare                                             key_compare;
        typedef Alloc                                               allocator_type;
        typedef pair<const key_type, mapped_type>                   value_type;
        typedef typename allocator_type::size_type                  size_type;
        typedef typename allocator_type::difference_type            difference_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;

        class value_compare
        {
        protected:
            Compare _cmp;
        public:
            value_compare(Compare cmp) : _cmp(cmp) {}
            bool operator()(const value_type& lhs, const value_type& rhs) const
            {
                return _cmp(lhs.first, rhs.first);
            }
        };

    private:
        typedef ft::BinarySearchTree<value_type, value_compare, allocator_type> tree_type;

    public:

        typedef typename tree_type::iterator                        iterator;
        typedef typename tree_type::const_iterator                  const_iterator;
        typedef typename tree_type::reverse_iterator                reverse_iterator;
        typedef typename tree_type::const_reverse_iterator          const_reverse_iterator;

        // Constructors
        explicit map(const key_compare& cmp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
            _alloc(alloc),
            _cmp(cmp),
            _bst(value_compare(cmp), alloc)
        {
        }

        template <typename InputIterator>
        map(InputIterator first,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
            const key_compare& cmp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
            _alloc(alloc),
            _cmp(cmp),
            _bst(value_compare(cmp), alloc)
        {
            for (; first != last; ++first)
                this->insert(*first);
        }

        map(const map& rhs) :
            _alloc(rhs._alloc),
            _cmp(rhs._cmp),
            _bst(rhs._bst)
        {
        }

        // Assignment Operators
        map& operator=(const map& rhs)
        {
            if (this != &rhs)
            {
                _alloc = rhs._alloc;
                _cmp = rhs._cmp;
                _bst = rhs._bst;
            }
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
        iterator begin()
        {
            return _bst.begin();    
        }

        const_iterator begin() const
        {
            return _bst.begin();
        }
        
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
        iterator end()
        {
            return _bst.end();
        }

        const_iterator end() const
        {
            return _bst.end();
        }

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
        reverse_iterator rbegin()
        {
            return _bst.rbegin();
        }

        const_reverse_iterator rbegin() const
        {
            return _bst.rbegin();
        }

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
        reverse_iterator rend()
        {
            return _bst.rend();
        }
        
        const_reverse_iterator rend() const
        {
            return _bst.rbegin();
        }

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
        bool empty() const
        {
            return _bst.empty();
        }
        
        /**
         * @brief   Return container size
         * 
         * Returns the number of elements in the map container.
         * @return  size_type
         */
        size_type size() const
        {
            return _bst.size();
        }

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
        size_type max_size() const
        {
            return _alloc.max_size();
        }

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
            return (*((this->insert(value_type(key, mapped_type()))).first)).second;
        }
        
        const mapped_type& operator[](const key_type& key) const
        {
            return (*((this->insert(value_type(key, mapped_type()))).first)).second;
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
        ft::pair<iterator, bool> insert(const value_type& value)
        {
            ft::pair<iterator, bool> result;
            iterator it = _bst.find(value);
            if (it != this->end())
            {
                result.first = it;
                result.second = false;
            }
            else
            {
                result.first = _bst.insert(value);
                result.second = true;
            }
            return result;
        }

        /**
         * @brief Insert with hint
         * 
         * @param position
         * @param value 
         * @return iterator 
         */
        iterator insert(iterator position, const value_type& value)
        {
            typename tree_type::node_pointer node = position.getNode();
            
            // check if the hint is valid
            if (position != this->end() && _cmp(position->first, value.first))
            {
                iterator it = node->maximum();
                // check if the value can be inserted under the hint_node subtree
                if (_cmp(value.first, it->first))
                    return _bst.insert(node->right, node, value);
                while (position != it)
                    ++position;
                return this->insert(++position, value);
            }
            return this->insert(value).first;
        }
        
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
            InputIterator last)
        {
            for (; first != last; ++first)
                this->insert(*first);
        }

        /**
         * @brief   Erase element
         * 
         * Removes from the map container a single element.
         * 
         * This effectively reduces the container size by the number of elements
         * removed, which are destroyed.
         * 
         * @param position 
         * @return size_type 
         */
        void erase(const_iterator position)
        {
            typename tree_type::node_pointer node = position.getNode();
            return _bst.erase(node);
        }

        /**
         * @brief   Erase element
         * 
         * @param key 
         */
        size_type erase(const key_type& key)
        {
            ft::pair<const_iterator, const_iterator> range = this->equal_range(key);
            return _erase(range.first, range.second);
        }

        /**
         * @brief   Erase elements
         * 
         * Removes from the map container a range of elements ([first,last)).
         * 
         * @param first 
         * @param last 
         */
        void erase(const_iterator first, const_iterator last)
        {
            _erase(first, last);
        }

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
         * @param rhs 
         */
        void swap(map& rhs)
        {
            ft::swap(_bst, rhs._bst);
            std::swap(_cmp, rhs._cmp);
            std::swap(_alloc, rhs._alloc);
        }

        /**
         * @brief   Clear content
         * 
         * Removes all elements from the map container (which are destroyed),
         * leaving the container with a size of 0.
         */
        void clear()
        {
            _bst.clear();
        }

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
            return _cmp;
        }
        
        value_compare value_comp() const
        {
            return value_compare(_cmp);
        }

        // ---------------------------------------------------------------------
        // Operations
        // ---------------------------------------------------------------------
        iterator find(const key_type& key)
        {
            return iterator(_bst.find(value_type(key, mapped_type())));
        }

        const_iterator find(const key_type& key) const
        {
            return const_iterator(_bst.find(value_type(key, mapped_type())));
        }

        size_type count(const key_type& key) const
        {
            value_type value(key, mapped_type());
            size_type result = 0;

            for (iterator it = _bst.find(value); it != this->end(); ++it)
                ++result;
            return result;
        }
        
        iterator lower_bound(const key_type& key)
        {
            return this->find(key);
        }
        
        const_iterator lower_bound(const key_type& key) const
        {
            return this->find(key);
        }
        
        iterator upper_bound(const key_type& key)
        {
            iterator it = this->lower_bound(key);
            for(; it != this->end() && _cmp(it->first, key); ++it);
            return ++it;
        }
        
        const_iterator upper_bound(const key_type& key) const
        {
            iterator it = this->lower_bound(key);
            for(; it != this->end() && _cmp(it->first, key); ++it);
            return ++it;
        }
        
        pair<iterator, iterator> equal_range(const key_type& key)
        {
            return make_pair(this->lower_bound(key), this->upper_bound(key));
        }
        
        pair<const_iterator, const_iterator> equal_range(const key_type& key) const
        {
            return make_pair(this->lower_bound(key), this->upper_bound(key));
        }
        
        // ---------------------------------------------------------------------
        // Allocator
        // ---------------------------------------------------------------------
        allocator_type get_allocator() const
        {
            return _alloc;
        }
    
    private:

        size_type _erase(const_iterator first, const_iterator last)
        {
            size_type count = 0;

            while (first != last)
            {
                this->erase(first++);
                ++count;
            }
            return count;
        }
        
        // Data Members
        allocator_type _alloc;
        key_compare _cmp;
        tree_type _bst;
    };
} // namespace ft


#endif
