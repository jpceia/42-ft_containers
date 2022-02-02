/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:07:20 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/02 15:47:20 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSTITERATOR_HPP
# define BSTITERATOR_HPP

# include "tree/BSTNode.hpp"
# include "tree/BinaryTree.hpp"
# include "iterator/iterator_traits.hpp"
# include "type_traits/remove_const.hpp"
#include <map>
namespace ft
{
    template <typename T>
    class BSTIterator //: public std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename ft::remove_const<T>::type  value_type;
        typedef ptrdiff_t                           difference_type;
        typedef T*                         pointer; // T*
        //typedef const value_type*                   const_pointer; // const T*
        typedef T&                         reference; // T&
        //typedef const value_type&                   const_reference; // const T&
        typedef std::bidirectional_iterator_tag     iterator_category;
        typedef ft::BSTNode<value_type>             node_type;
        typedef node_type*                          node_pointer;
        typedef ft::BinaryTree<value_type>          tree_type;
        
        BSTIterator() {}
        BSTIterator(const tree_type& tree, const node_pointer& node) :
            _tree(tree),
            _node(node)
        {}
        
        BSTIterator(const BSTIterator& rhs) :
            _tree(rhs._tree),
            _node(rhs._node)
        {}

        virtual BSTIterator& operator=(const BSTIterator& rhs)
        {
            if (this != &rhs)
            {
                _tree = rhs._tree;
                _node = rhs._node;
            }
            return *this;
        }

        virtual ~BSTIterator() {}

        // Conversion operator to const iterator
        operator BSTIterator<const value_type>() const
        {
            return BSTIterator<const value_type>(_tree, _node);
        }

        reference operator*() const
        {
            return _node->data;
        }

        pointer operator->() const
        {
            return &_node->data;
        }

        BSTIterator& operator++()
        {
            _node = _tree.successor(_node);
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
            _node = _tree.predecessor(_node);
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

    protected:
        tree_type _tree;
        node_pointer _node;
    };
} // namespace ft

#endif
