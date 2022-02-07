/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:50:39 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 00:38:00 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "pair.hpp"
# include "tree/BinarySearchTree.hpp"
# include "type_traits/enable_if.hpp"
# include "type_traits/is_integral.hpp"


namespace ft
{
    template<
        typename T,
        typename Compare = std::less<T>,
        typename Alloc = std::allocator<T>
    >
    class set
    {
    private:
        typedef ft::BinarySearchTree<T, Compare, Alloc>     tree_type;
    public:
        // ---------------------------------------------------------------------
        // Member types
        // ---------------------------------------------------------------------
        typedef T                                           key_type;
        typedef T                                           value_type;
        typedef Compare                                     key_compare;
        typedef Compare                                     value_compare;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename tree_type::iterator                iterator;
        typedef typename tree_type::const_iterator          const_iterator;
        typedef typename tree_type::reverse_iterator        reverse_iterator;
        typedef typename tree_type::const_reverse_iterator  const_reverse_iterator;
        typedef typename tree_type::difference_type         difference_type;
        typedef typename tree_type::size_type               size_type;

        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------

        /**
         * @brief Empty container constructor (default constructor)
         * 
         * Constructs an empty container, with no elements.
         * 
         * @param cmp 
         * @param alloc 
         */
        explicit set(
            const key_compare& cmp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
            _bst(cmp, alloc)
        {}

        /**
         * @brief Range constructor
         * 
         * Constructs a container with as many elements as the range
         * [first,last), with each element constructed from its corresponding
         * element in that range.
         * 
         * @tparam InputIterator 
         * @param first 
         * @param last 
         * @param cmp 
         * @param alloc 
         */
        template<typename InputIterator>
        set(InputIterator first,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last,
            const key_compare& cmp = key_compare(),
            const allocator_type& alloc = allocator_type()) :
            _bst(cmp, alloc)
        {
            this->insert(first, last);
        }

        /**
         * @brief Copy constructor
         * 
         * Constructs a container with a copy of each of the elements in x.
         * 
         * @param rhs 
         */
        set(const set& rhs) :
            _bst(rhs._bst)
        {}

        /**
         * @brief Copy container content
         * 
         * Copies all the elements from x into the container, changing its size
         * accordingly.
         * 
         * The container preserves its current allocator, which is used to
         * allocate additional storage if needed.
         * 
         * @param rhs 
         * @return set& 
         */
        set& operator= (const set& rhs)
        {
            if (this != &rhs)
            {
                _bst = rhs._bst;
            }
            return *this;
        }

        /**
         * @brief Set destructor
         * 
         * This destroys all container elements, and deallocates all the storage
         * capacity allocated by the set container using its allocator.
         */
        virtual ~set()
        {}

        // ---------------------------------------------------------------------
        // Iterators
        // ---------------------------------------------------------------------
        
        /**
         * @brief Return iterator to beginning
         * 
         * Returns an iterator referring to the first element in the set
         * container.
         * 
         * Because set containers keep their elements ordered at all times,
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
         * @brief Return iterator to end
         * 
         * Returns an iterator referring to the past-the-end element in the set
         * container.
         * The past-the-end element is the theoretical element that would follow
         * the last element in the set container. It does not point to any
         * element, and thus shall not be dereferenced.
         * 
         * Because the ranges used by functions of the standard library do not
         * include the element pointed by their closing iterator, this function
         * is often used in combination with set::begin to specify a range
         * including all the elements in the container.
         * 
         * If the container is empty, this function returns the same as
         * set::begin.
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
         * @brief Return reverse iterator to reverse beginning
         * 
         * Returns a reverse iterator pointing to the last element in the
         * container (i.e., its reverse beginning).
         * 
         * Reverse iterators iterate backwards: increasing them moves them
         * towards the beginning of the container.
         * 
         * rbegin points to the element preceding the one that would be pointed
         * to by member end.
         * 
         * @return iterator 
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
         * @brief Return reverse iterator to reverse end
         * 
         * Returns a reverse iterator pointing to the theoretical element right
         * before the first element in the set container (which is considered
         * its reverse end).
         * 
         * The range between set::rbegin and set::rend contains all the elements
         * of the container (in reverse order).
         * 
         * @return iterator 
         */
        reverse_iterator rend()
        {
            return _bst.rend();
        }

        const_reverse_iterator rend() const
        {
            return _bst.rend();
        }

        // ---------------------------------------------------------------------
        // Capacity
        // ---------------------------------------------------------------------

        /**
         * @brief Test whether container is empty
         * 
         * Returns whether the set container is empty
         * (i.e. whether its size is 0).
         * 
         * This function does not modify the container in any way.
         * 
         * @return true 
         * @return false 
         */
        bool empty() const
        {
            return _bst.empty();
        }

        /**
         * @brief Return container size
         * 
         * Returns the number of elements in the set container.
         * 
         * @return size_type 
         */
        size_type size() const
        {
            return _bst.size();
        }

        /**
         * @brief Return maximum size
         * 
         * Returns the maximum number of elements that the set container can
         * hold.
         * 
         * This is the maximum potential size the container can reach due to
         * known system or library implementation limitations, but the container
         * is by no means guaranteed to be able to reach that size: it can still
         * fail to allocate storage at any point before that size is reached.
         * 
         * @return size_type 
         */
        size_type max_size() const
        {
            return _bst.max_size();
        }

        // ---------------------------------------------------------------------
        // Modifiers
        // ---------------------------------------------------------------------

        ft::pair<iterator, bool> insert(const value_type& val)
        {
            ft::pair<iterator, bool> result;
            iterator it = _bst.find(val);
            if (it != this->end())
            {
                result.first = it;
                result.second = false;
            }
            else
            {
                result.first = _bst.insert(val);
                result.second = true;
            }
            return result;
        }

        iterator insert(const_iterator hint, const value_type& val)
        {
            ft::pair<iterator, bool> result;
            iterator it = _bst.find(hint, val);
            if (it != this->end())
                return it;
            return _bst.insert(val);
        }

        template<typename InputIterator>
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
        insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                this->insert(*first);
        }

        void erase(iterator position)
        {
            _bst.erase(position);
        }

        size_type erase(const value_type& val)
        {
            iterator position = this->find(val);
            if (position == this->end())
                return 0;
            this->erase(position);
            return 1;
        }

        void erase(iterator first, iterator last)
        {
            while (first != last && first != this->end())
                this->erase(first++);
        }

        void swap(set& rhs)
        {
            ft::swap(_bst, rhs._bst);
        }

        void clear()
        {
            _bst.clear();
        }

        // ---------------------------------------------------------------------
        // Observers
        // ---------------------------------------------------------------------

        /**
         * @brief Return comparison object
         * 
         * Returns a copy of the comparison object used by the container.
         * 
         * By default, this is a less object, which returns the same as
         * operator<.
         * 
         * This object determines the order of the elements in the container:
         * it is a function pointer or a function object that takes two
         * arguments of the same type as the container elements, and returns
         * true if the first argument is considered to go before the second in
         * the strict weak ordering it defines, and false otherwise.
         * 
         * Two elements of a set are considered equivalent if key_comp returns
         * false reflexively (i.e., no matter the order in which the elements
         * are passed as arguments).
         * 
         * In set containers, the keys to sort the elements are the values
         * themselves, therefore key_comp and its sibling member function
         * value_comp are equivalent.
         * 
         * @return key_compare 
         */
        key_compare key_comp() const
        {
            return _bst.value_comp();
        }

        /**
         * @brief Return comparison object
         * 
         * Returns a copy of the comparison object used by the container.
         * 
         * @return value_compare 
         */
        value_compare value_comp() const
        {
            return _bst.value_comp();
        }
        
        // ---------------------------------------------------------------------
        // Operations
        // ---------------------------------------------------------------------
        
        /**
         * @brief Get iterator to element
         * 
         * Searches the container for an element equivalent to val and returns
         * an iterator to it if found, otherwise it returns an iterator to
         * set::end.
         * 
         * Two elements of a set are considered equivalent if the container's
         * comparison object returns false reflexively (i.e., no matter the
         * order in which the elements are passed as arguments).
         * 
         * @param val 
         * @return iterator 
         */
        iterator find (const value_type& val) const
        {
            return _bst.find(val);
        }

        /**
         * @brief Count elements with a specific value
         * 
         * Searches the container for elements equivalent to val and returns the
         * number of matches.
         * 
         * Because all elements in a set container are unique, the function can
         * only return 1 (if the element is found) or zero (otherwise).
         * 
         * Two elements of a set are considered equivalent if the container's
         * comparison object returns false reflexively (i.e., no matter the
         * order in which the elements are passed as arguments).
         * 
         * @param val 
         * @return size_type 
         */
        size_type count(const value_type& val) const
        {
            return this->find(val) != this->end() ? 1 : 0;
        }

        /**
         * @brief Return iterator to lower bound
         * 
         * Returns an iterator pointing to the first element in the container
         * which is not considered to go before val (i.e., either it is
         * equivalent o<<r goes after).
         * 
         * The function uses its internal comparison object (key_comp) to
         * determine this, returning an iterator to the first element for which
         * key_comp(element,val) would return false.
         * 
         * If the set class is instantiated with the default comparison type
         * (less), the function returns an iterator to the first element that
         * is not less than val.
         * 
         * @param val 
         * @return iterator 
         */
        iterator lower_bound(const value_type& val) const
        {
            return this->find(val);
        }

        /**
         * @brief Return iterator to upper bound
         * 
         * Returns an iterator pointing to the first element in the container
         * which is considered to go after val.
         * 
         * The function uses its internal comparison object (key_comp) to
         * determine this, returning an iterator to the first element for which
         * key_comp(val,element) would return true.
         * 
         * If the set class is instantiated with the default comparison type
         * (less), the function returns an iterator to the first element that is
         * greater than val.
         * 
         * @param val 
         * @return iterator 
         */
        iterator upper_bound(const value_type& val) const
        {
            iterator it = this->find(val);
            return ++it;
        }

        /**
         * @brief Return range of equal elements
         * 
         * Returns the bounds of a range that includes all the elements in the
         * container that are equivalent to val.
         * 
         * Because all elements in a set container are unique, the range
         * returned will contain a single element at most.
         * 
         * If no matches are found, the range returned has a length of zero,
         * with both iterators pointing to the first element that is considered
         * to go after val according to the container's internal comparison
         * object (key_comp).
         * 
         * Two elements of a set are considered equivalent if the container's
         * comparison object returns false reflexively (i.e., no matter the
         * order in which the elements are passed as arguments).
         * 
         * @param val 
         * @return std::iterator<iterator,iterator> 
         */
        ft::pair<iterator,iterator> equal_range(const value_type& val) const
        {
            return ft::make_pair(this->lower_bound(val), this->upper_bound(val));
        }

        // ---------------------------------------------------------------------
        // Allocator
        // ---------------------------------------------------------------------
        
        /**
         * @brief Get the allocator object
         * 
         * Returns a copy of the allocator object associated with the set.
         * 
         * @return allocator_type 
         */
        allocator_type get_allocator() const
        {
            return _bst.get_allocator();
        }
        
    private:

        // ---------------------------------------------------------------------
        // Data Members
        // ---------------------------------------------------------------------

        tree_type _bst;

    };
} // namespace ft


#endif
