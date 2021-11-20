/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:28:21 by jpceia            #+#    #+#             */
/*   Updated: 2021/11/20 02:51:40 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include "pair.hpp"

namespace ft
{
    template < class Key,                                           // map::key_type
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
            map(const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type());
            map(InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type());
            map(const map& rhs);

            // Assignment Operators
            map& operator=(const map& rhs);

            // Destructor
            ~map(void);

            // Iterators
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            // Capacity
            bool empty() const;
            size_type size() const;
            size_type max_size() const;

            // Element Access
            mapped_type& operator[](const key_type& key);
            const mapped_type& operator[](const key_type& key) const;

            // Modifiers
            pair<iterator, bool> insert(const value_type& value);
            iterator insert(const_iterator hint, const value_type& value);
            template <class InputIterator>
            void insert(InputIterator first, InputIterator last);

            void erase(const key_type& key);
            void erase(const_iterator position);
            void erase(const_iterator first, const_iterator last);
            void swap(map& other);
            void clear();

            // Observers
            key_compare key_comp() const;
            value_compare value_comp() const;


            // Operations
            iterator find(const key_type& key);
            const_iterator find(const key_type& key) const;
            size_type count(const key_type& key) const;
            iterator lower_bound(const key_type& key);
            const_iterator lower_bound(const key_type& key) const;
            iterator upper_bound(const key_type& key);
            const_iterator upper_bound(const key_type& key) const;
            pair<iterator, iterator> equal_range(const key_type& key);
            pair<const_iterator, const_iterator> equal_range(const key_type& key) const;
            
            // Allocator
            allocator_type get_allocator() const;
    };
} // namespace ft

#endif
