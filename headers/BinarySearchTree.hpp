/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:04:50 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/30 12:12:31 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BINARYSEARCHTREE_HPP
# define BINARYSEARCHTREE_HPP

#include <memory>
#include "..iterator/reverse_iterator.hpp"

namespace ft
{
    template <typename T>
    struct BSTNode
    {
        T data;
        BSTNode* left;
        BSTNode* right;
        BSTNode* parent;

        BSTNode(const T& data) :
            data(data),
            left(NULL),
            right(NULL),
            parent(NULL)
        {}

        BSTNode(const T& data, BSTNode* parent) :
            data(data),
            left(NULL),
            right(NULL),
            parent(parent)
        {}

        BSTNode(const BSTNode& rhs) :
            data(rhs.data),
            left(rhs.left),
            right(rhs.right),
            parent(rhs.parent)
        {}

        BSTNode& operator=(const BSTNode& rhs)
        {
            if (this != &rhs)
            {
                data = rhs.data;
                left = rhs.left;
                right = rhs.right;
                parent = rhs.parent;
            }
            return *this;
        }

        virtual ~BSTNode()
        {}

        BSTNode* minimum()
        {
            BSTNode* node = this;

            while (node->left)
                node = node->left;
            return node;
        }
    
        const BSTNode* minimum() const
        {
            const BSTNode* node = this;

            while (node->left)
                node = node->left;
            return node;
        }

        BSTNode* maximum()
        {
            BSTNode* node = this;

            while (node->right)
                node = node->right;
            return node;
        }

        const BSTNode* maximum() const
        {
            const BSTNode* node = this;

            while (node->right)
                node = node->right;
            return node;
        }

        BSTNode* successor()
        {
            if (this->right)
                return this->right->minimum();
            BSTNode* node = this;
            // checks if the node is the maximum
            if (!node->parent || node != node->parent->right)
                return NULL;
            // goes up until the node is the left child of its parent
            while (node->parent && node == node->parent->right)
                node = parent->parent;
            return node->parent;
        }

        const BSTNode* successor() const
        {
            if (this->right)
                return this->right->minimum();
            BSTNode* node = this;
            // checks if the node is the maximum
            if (!node->parent || node != node->parent->right)
                return NULL;
            // goes up until the node is the left child of its parent
            while (node->parent && node == node->parent->right)
                node = parent->parent;
            return node->parent;
        }

        BSTNode* predecessor()
        {
            if (this->left)
                return this->left->maximum();

            BSTNode* node = this;
            // checks if the node is the minimum
            if (!node->parent || node != node->parent->left)
                return NULL;
            // goes up until the node is the right child of its parent
            while (node->parent && node == node->parent->left)
                node = node->parent;
            return node->parent;
        }

        const BSTNode* predecessor() const
        {
            if (this->left)
                return this->left->maximum();

            BSTNode* node = this;
            // checks if the node is the minimum
            if (!node->parent || node != node->parent->left)
                return NULL;
            // goes up until the node is the right child of its parent
            while (node->parent && node == node->parent->left)
                node = node->parent;
            return node->parent;
        }
    };

    template <typename T, bool is_const>
    class BSTIterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        typedef BSTNode<T>* node_pointer;
        
        BSTIterator() {}
        BSTIterator(const node_pointer& root, const node_pointer& node) :
            _root(root),
            _node(node)
        {}
        
        BSTIterator(const BSTIterator& rhs) :
            _root(rhs._root),
            _node(rhs._node)
        {}

        virtual BSTIterator& operator=(const BSTIterator& rhs)
        {
            _root = rhs._root;
            _node = rhs._node;
            return *this;
        }

        virtual ~BSTIterator() {}

        T& operator*() const
        {
            return _node->data;
        }

        const T* operator->() const
        {
            return &_node->data;
        }

        BSTIterator& operator++()
        {
            // successor
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
            // predecessor of NULL is the maximum
            _node = _node ? _node->predecessor() : _root->maximum();
            return *this;
        }

        BSTIterator operator--(int)
        {
            BSTIterator it(*this);
            --(*this);
            return it;
        }

        // getters
        node_pointer getRoot() const
        {
            return _root;
        }

        node_pointer getNode() const
        {
            return _node;
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
        node_pointer _node;
        node_pointer _root;
    };

    template <
        typename T,
        typename Alloc = std::allocator<BSTNode<T> >,
        typename Compare = std::less<T>
    >
    class BinarySearchTree
    {
    public:
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef value_type*                                 pointer;
        typedef const value_type*                           const_pointer;
        typedef Compare                                     value_compare;
        typedef BSTIterator<T>                              iterator;
        typedef const iterator                              const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        typedef typename iterator::difference_type          difference_type;
        typedef typename allocator_type::size_type          size_type;
        typedef BSTNode<T>                                  node_type;
        typedef node_type*                                  node_pointer;
        typedef const node_type*                            const_node_pointer;

        BinarySearchTree(
            const allocator_type& alloc = allocator_type(),
            const value_compare& cmp = value_compare()) :
            _alloc(alloc),
            _cmp(cmp),
            _root(NULL)
        {
        }

        BinarySearchTree(const BinarySearchTree& rhs) :
            _alloc(rhs._alloc),
            _cmp(rhs._cmp)
        {
            _root = _copy(rhs._root);
        }

        BinarySearchTree& operator=(const BinarySearchTree& rhs)
        {
            if (this != &rhs)
            {
                _clear(_root);
                _root = _copy(rhs._root);
            }
            return *this;
        }
        
        virtual ~BinarySearchTree()
        {
            this->clear();
        }

        iterator begin()
        {
            return _iterator(_root ? _root->minimum() : NULL);
        }

        const_iterator begin() const
        {
            return _iterator(_root ? _root->minimum() : NULL);
        }

        iterator end()
        {
            return _iterator(NULL);
        }

        const_iterator end() const
        {
            return _iterator(NULL);
        }

        iterator find(const value_type& val)
        {
            return _find(_root, val);
        }

        const_iterator find(const value_type& val) const
        {
            return _find(_root, val);
        }

        iterator insert(const value_type& val)
        {
            return _insert(_root, NULL, val);
        }

        void clear()
        {
            _clear(_root);
        }

        void erase(const value_type& val)
        {
            _erase(_root, val);
        }

        void erase(const node_pointer& node)
        {
            if (!node->left && !node->right) // case 1: leaf node
            {
                if (node->parent->left == node) // node is left child
                    node->parent->left = NULL;
                else                            // node is right child
                    node->parent->right = NULL;
                _free(node);
            }
            else if (node->right) // case 2: right child only
            {
                if (node->parent->left == node) // node is left child
                    node->parent->left = node->right;
                else                            // node is right child
                    node->parent->right = node->right;
                node->right->parent = node->parent;
                _free(node);
            }
            else if (node->left) // case 3: left child only
            {
                if (node->parent->left == node)
                    node->parent->left = node->left;
                else
                    node->parent->right = node->left;
                node->left->parent = node->parent;
                _free(node);
            }
            else // case 4: two children
            {
                node_pointer successor = node->successor();
                node->data = successor->data;
                _erase(successor, successor->data);
            }
        }
        
    protected:

        iterator _iterator(node_pointer node)
        {
            return iterator(node, _root);
        }

        const_iterator _iterator(node_pointer node) const
        {
            return const_iterator(node, _root);
        }

        iterator _find(node_pointer node, const value_type& val)
        {
            if (!node)
                return _iterator(NULL);
            if (_cmp(node->data, val))
                return _find(node->left, val);
            if (_cmp(val, node->data))
                return _find(node->right, val);
            return _iterator(node);
        }

        const_iterator _find(const_node_pointer node, const value_type& val) const
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

        node_pointer _insert(node_pointer& node, node_pointer parent, const value_type& val)
        {
            if (!node)
            {
                node = _create_node(val);
                node->parent = parent;
                return _iterator(node);
            }
            if (_cmp(val, node->data))
                return _insert(node->left, node, val);
            return _insert(node->right, node, val);
        }

        void _free(node_pointer node)
        {
            _alloc.destroy(node);
            _alloc.deallocate(node, 1);
        }

        void _clear(node_pointer node)
        {
            if (!node)
                return ;
            _clear(node->left);
            _clear(node->right);
            _free(node);
        }

        void _erase(node_pointer node, const value_type& val)
        {
            if (!node)
                return ;
            if (_cmp(val, node->data))
                _erase(node->left, val);
            else if (_cmp(node->data, val))
                _erase(node->right, val);
            // there is an equality and we are going to erase this node
            else
                erase(node);
        }

        allocator_type _alloc;
        value_compare _cmp;
        node_pointer _root;
    };
}

#endif
