/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:04:50 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/02 15:58:31 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BINARYSEARCHTREE_HPP
# define BINARYSEARCHTREE_HPP

# include <memory>
# include <functional>
# include "iterator/reverse_iterator.hpp"
# include "tree/BSTIterator.hpp"
# include "tree/BinaryTree.hpp"
# include <map>

namespace ft
{
    template <
        typename T,
        typename Compare = std::less<T>,
        typename Alloc = std::allocator<T>
    >
    class BinarySearchTree : public BinaryTree<T>
    {
    public:
        typedef T                                                       value_type;
        // use rebind to change the T allocator to BSTNode<T> allocator
        typedef typename Alloc::template rebind<BSTNode<T> >::other     allocator_type;
        typedef value_type&                                             reference;
        typedef const value_type&                                       const_reference;
        typedef value_type*                                             pointer;
        typedef const value_type*                                       const_pointer;
        typedef Compare                                                 value_compare;
        typedef ft::BSTIterator<T>                                      iterator;
        typedef ft::BSTIterator<const T>                                const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename iterator::difference_type                      difference_type;
        typedef typename allocator_type::size_type                      size_type;
        typedef BSTNode<T>                                              node_type;
        typedef node_type*                                              node_pointer;
        typedef const node_type*                                        const_node_pointer;

        BinarySearchTree(
            const value_compare& cmp = value_compare(),
            const allocator_type& alloc = allocator_type()) :
            _alloc(alloc),
            _cmp(cmp)
        {
        }

        BinarySearchTree(const BinarySearchTree& rhs) :
            _alloc(rhs._alloc),
            _cmp(rhs._cmp)
        {
            this->_root = _copy(rhs._root);
        }

        virtual BinarySearchTree& operator=(const BinarySearchTree& rhs)
        {
            if (this != &rhs)
            {
                _clear(this->_root);
                this->_root = _copy(rhs._root);
            }
            return *this;
        }
        
        virtual ~BinarySearchTree()
        {
            this->clear();
        }

        iterator begin()
        {
            return _iterator(this->minimum());
        }

        const_iterator begin() const
        {
            return _iterator(this->minimum());
        }

        iterator end()
        {
            return _iterator(NULL);
        }

        const_iterator end() const
        {
            return _iterator(NULL);
        }

        reverse_iterator rbegin()
        {
            return this->end();
        }

        const_reverse_iterator rbegin() const
        {
            return this->end();
        }

        reverse_iterator rend()
        {
            return this->begin();
        }

        const_reverse_iterator rend() const
        {
            return this->begin();
        }

        iterator find(const value_type& val)
        {
            return _find(this->_root, val);
        }

        iterator insert(const value_type& val)
        {
        virtual iterator insert(node_pointer& node, node_pointer parent, const value_type& val)
        {
            if (!node)
            {
                node = _create_node(val);
                node->parent = parent;
                return _iterator(node);
            }
            if (_cmp(val, node->data))
                return insert(node->left, node, val);
            return insert(node->right, node, val);
        }

        void clear()
        {
            _clear(this->_root);
        }

        void erase(const value_type& val)
        {
            _erase(this->_root, val);
        }

        void erase(iterator it)
        {
            _erase(this->_root, it);
        }

        void erase(node_pointer& node)
        {
            if (!node->left && !node->right) // case 1: leaf node
            {
                // update parent's child pointer
                node->set_parent_child(NULL);
                // update root pointer
                if (node == this->_root)
                    this->_root = NULL;
                _free(node);
            }
            else if (node->right) // case 2: right child only
            {
                // update parent's child pointer
                node->set_parent_child(node->right);
                node->right->parent = node->parent;
                // update root pointer
                if (this->_root == node)
                    this->_root = node->right;
                _free(node);
            }
            else if (node->left) // case 3: left child only
            {
                // update parent's child pointer
                node->set_parent_child(node->left);
                node->left->parent = node->parent;
                // update root pointer
                if (this->_root == node)
                    this->_root = node->left;
                _free(node);
            }
            else // case 4: two children
            {
                node_pointer successor = this->successor(node);
                node_pointer new_node = _copy(successor);
                new_node->left = node->left;
                new_node->right = node->right;
                new_node->parent = node->parent;
                // update parent's child pointer
                node->set_parent_child(new_node);
                _free(node);
                // update root pointer
                if (this->_root == node)
                    this->_root = new_node;
                _erase(successor, successor->data);
            }
        }
        
    protected:

        iterator _iterator(node_pointer node)
        {
            return iterator(this->_root, node);
        }

        iterator _find(node_pointer node, const value_type& val)
        {
            if (!node)
                return _iterator(NULL);
            if (_cmp(val, node->data))
                return _find(node->left, val);
            if (_cmp(node->data, val))
                return _find(node->right, val);
            return _iterator(node);
        }
        
        node_pointer _copy(node_pointer node)
        {
            if (!node)
                return NULL;
            node_pointer new_node = _alloc.allocate(1);
            _alloc.construct(new_node, node->data);
            new_node->left = _copy(node->left);
            new_node->right = _copy(node->right);
            return new_node;
        }

        node_pointer _create_node(const value_type& val)
        {
            node_pointer node = _alloc.allocate(1);
            _alloc.construct(node, val);
            return node;
        }

        void _free(node_pointer& node)
        {
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
            node = NULL;
        }

        void _clear(node_pointer& node)
        {
            if (!node)
                return ;
            _clear(node->left);
            _clear(node->right);
            _free(node);
        }

        virtual void _erase(node_pointer node, const value_type& val)
        {
            if (!node)
                return ;
            if (_cmp(val, node->data))
                _erase(node->left, val);
            else if (_cmp(node->data, val))
                _erase(node->right, val);
            // there is an equality and we are going to erase this node
            else
                this->erase(node);
        }

        allocator_type _alloc;
        value_compare _cmp;
    };
}

#endif
