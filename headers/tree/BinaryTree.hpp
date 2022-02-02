/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinaryTree.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:58:49 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/02 15:45:17 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARYTREE_HPP
# define BINARYTREE_HPP

# include "tree/BSTNode.hpp"

namespace ft
{
    template <typename T>
    class BinaryTree
    {
    public:
        typedef T                                                       value_type;
        typedef value_type&                                             reference;
        typedef const value_type&                                       const_reference;
        typedef value_type*                                             pointer;
        typedef const value_type*                                       const_pointer;
        typedef BSTNode<T>                                              node_type;
        typedef node_type*                                              node_pointer;
        typedef const node_type*                                        const_node_pointer;

        BinaryTree(const node_pointer& root = NULL) : _root(root) {}

        BinaryTree(const BinaryTree& rhs) :
            _root(rhs._root)
        {}

        BinaryTree& operator= (const BinaryTree& rhs)
        {
            if (this != &rhs)
                _root = rhs._root;
            return *this;
        }

        virtual ~BinaryTree() {}

        bool empty() const
        {
            return !_root;
        }

        size_t size() const
        {
            return _root ? _root->size() : 0;
        }
        
        node_pointer minimum() const
        {
            return _root ? _root->minimum() : NULL;
        }

        node_pointer maximum() const
        {
            return _root ? _root->maximum() : NULL;
        }

        node_pointer successor(node_pointer node) const
        {
            if (!_root)
                return NULL;
            if (!node)
                return _root->minimum();
            if (node->right)
                return node->right->minimum();
            // checks if the node is the maximum
            if (node == _root->maximum())
                return NULL;
            // goes up until the node is the left child of its parent
            while (node->parent && node == node->parent->right)
                node = node->parent;
            return node->parent;
        }

        node_pointer predecessor(node_pointer node) const
        {
            if (!_root)
                return NULL;
            if (!node)
                return _root->maximum();
            if (node->left)
                return node->left->maximum();
            // checks if the node is the minimum
            if (node == _root->minimum())
                return NULL;
            // goes up until the node is the right child of its parent
            while (node->parent && node == node->parent->left)
                node = node->parent;
            return node->parent;
        }
        
    protected:
        node_pointer _root;
    };

    
} // namespace ft

#endif
