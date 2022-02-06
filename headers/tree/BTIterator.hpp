/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:07:20 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/06 13:51:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTITERATOR_HPP
# define BTITERATOR_HPP

# include "tree/Node.hpp"
# include "iterator/iterator_traits.hpp"
# include "type_traits/remove_const.hpp"
#include <map>
namespace ft
{
    template <typename T>
    class BTIterator
    {
    public:
        typedef typename ft::remove_const<T>::type  value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef NodeBase                            node_type;
        typedef node_type*                          node_pointer;
        
        BTIterator() {}
        BTIterator(const node_pointer& node) :
            _node(node)
        {}
        
        BTIterator(const BTIterator& rhs) :
            _node(rhs._node)
        {}

        virtual BTIterator& operator=(const BTIterator& rhs)
        {
            if (this != &rhs)
                _node = rhs._node;
            return *this;
        }

        virtual ~BTIterator() {}

        // Conversion operator to const iterator
        operator BTIterator<const value_type>() const
        {
            return BTIterator<const value_type>(_node);
        }

        reference operator*() const
        {
            return static_cast<NodeValue<T>*>(_node)->data;
        }

        pointer operator->() const
        {
            return &static_cast<NodeValue<T>*>(_node)->data;
        }

        BTIterator& operator++()
        {
            _node = _node->successor();
            return *this;
        }

        BTIterator operator++(int)
        {
            BTIterator it(*this);
            ++(*this);
            return it;
        }

        BTIterator operator--()
        {
            _node = _node->predecessor();
            return *this;
        }

        BTIterator operator--(int)
        {
            BTIterator it(*this);
            --(*this);
            return it;
        }

        friend bool operator==(const BTIterator& lhs, const BTIterator& rhs)
        {
            return lhs._node == rhs._node;
        }

        friend bool operator!=(const BTIterator& lhs, const BTIterator& rhs)
        {
            return lhs._node != rhs._node;
        }

        node_pointer _node;
    };
} // namespace ft

#endif
