/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:07:20 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/05 20:22:48 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSTITERATOR_HPP
# define BSTITERATOR_HPP

# include "tree/Node.hpp"
# include "iterator/iterator_traits.hpp"
# include "type_traits/remove_const.hpp"
#include <map>
namespace ft
{
    template <typename T>
    class BSTIterator
    {
    public:
        typedef typename ft::remove_const<T>::type  value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef NodeBase                            node_type;
        typedef node_type*                          node_pointer;
        
        BSTIterator() {}
        BSTIterator(const node_pointer& node) :
            _node(node)
        {}
        
        BSTIterator(const BSTIterator& rhs) :
            _node(rhs._node)
        {}

        virtual BSTIterator& operator=(const BSTIterator& rhs)
        {
            if (this != &rhs)
                _node = rhs._node;
            return *this;
        }

        virtual ~BSTIterator() {}

        // Conversion operator to const iterator
        operator BSTIterator<const value_type>() const
        {
            return BSTIterator<const value_type>(_node);
        }

        reference operator*() const
        {
            return static_cast<NodeValue<T>*>(_node)->data;
        }

        pointer operator->() const
        {
            return &static_cast<NodeValue<T>*>(_node)->data;
        }

        BSTIterator& operator++()
        {
            _node = _node->successor();
            return *this;
        }

        BSTIterator operator++(int)
        {
            BSTIterator it(*this);
            ++(*this);
            return it;
        }

        BSTIterator operator--()
        {
            _node = _node->predecessor();
            return *this;
        }

        BSTIterator operator--(int)
        {
            BSTIterator it(*this);
            --(*this);
            return it;
        }

        friend bool operator==(const BSTIterator& lhs, const BSTIterator& rhs)
        {
            return lhs._node == rhs._node;
        }

        friend bool operator!=(const BSTIterator& lhs, const BSTIterator& rhs)
        {
            return lhs._node != rhs._node;
        }

        node_pointer _node;
    };
} // namespace ft

#endif
