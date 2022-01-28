/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:04:50 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/28 07:46:46 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BINARYSEARCHTREE_HPP
# define BINARYSEARCHTREE_HPP

#include <memory>

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
    };

    template <typename T>
    class BSTIterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
    public:
        BSTIterator() {}
        BSTIterator(BSTNode<T>* node) : _node(node) {}
        BSTIterator(const BSTIterator& rhs) : _node(rhs._node) {}

        virtual BSTIterator& operator=(const BSTIterator& rhs)
        {
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
            if (_node->right)
            {
                _node = _node->right;
                while (_node->left)
                    _node = _node->left;
            }
            else
            {
                BSTNode<T>* parent = _node->parent;
                while (parent && _node == parent->right)
                {
                    _node = parent;
                    parent = parent->parent;
                }
                _node = parent;
            }
            return *this;
        }

        BSTIterator operator++(int)
        {
            BSTIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        BSTIterator operator--()
        {
            if (_node->left)
            {
                _node = _node->left;
                while (_node->right)
                    _node = _node->right;
            }
            else
            {
                BSTNode<T>* parent = _node->parent;
                while (parent && _node == parent->left)
                {
                    _node = parent;
                    parent = parent->parent;
                }
                _node = parent;
            }
            return *this;
        }

        BSTIterator operator--(int)
        {
            BSTIterator tmp(*this);
            --(*this);
            return tmp;
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

        BSTNode<T>* _node;
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
            _capacity(1),
            _size(0)
        {
            _root = _alloc.allocate(_capacity);
        }
        
        virtual ~BinarySearchTree()
        {
            this->clear();
            _alloc.deallocate(_root, _capacity);
        }

        pointer find(const value_type& val)
        {
            return _size ? _find(_root, val) : NULL;
        }

        const_pointer find(const value_type& val) const
        {
            return _size ? _find(_root, val) : NULL;
        }

        void insert(const value_type& val)
        {
            _insert(_root, val);
        }

        iterator begin()
        {
            if (_size == 0)
                return iterator();
            node_pointer node = _root;
            while (node->left)
                node = node->left;
            return iterator(node);
        }

        const_iterator begin() const
        {
            if (_size == 0)
                return const_iterator();
            node_pointer node = _root;
            while (node->left)
                node = node->left;
            return iterator(node);
        }

        iterator end()
        {
            if (_size == 0)
                return iterator();
            node_pointer node = _root;
            while (node->right)
                node = node->right;
            return iterator(node);
        }

        const_iterator end() const
        {
            if (_size == 0)
                return iterator();
            node_pointer node = _root;
            while (node->right)
                node = node->right;
            return iterator(node);
        }

        void reserve(size_type n)
        {
            if (n > _capacity)
            {   
                typename allocator_type::pointer new_root = _alloc.allocate(n);
                std::uninitialized_copy(_root, _root + _size, new_root);
                this->clear();
                _alloc.deallocate(_root, _capacity);
                _root = new_root;
                _capacity = n;
            }
        }
        
        void clear()
        {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(_root + i);
        }
        
    protected:
        void _reallocate()
        {
            reserve(_capacity > 0 ? 2 * _capacity : 1);
        }

        node_pointer _create_node(const value_type& val)
        {
            if (_size == _capacity)
                _reallocate();
            node_pointer ptr = _root + _size;
            std::cout << "creating node at position " << _size << std::endl;
            _alloc.construct(ptr, val);
            ++_size;
            return ptr;
        }

        pointer _find(BSTNode<T>* node, const value_type& val)
        {
            if (!node)
                return NULL;
            std::cout << "_find. current=" << node->data << " lookup=" << val << std::endl;
            if (_cmp(node->data, val))
                return _find(node->left, val);
            if (_cmp(val, node->data))
                return _find(node->right, val);
            return &node->data;
        }

        const_pointer _find(const BSTNode<T>* node, const value_type& val) const
        {
            if (!node)
                return NULL;
            if (_cmp(node->data, val))
                return _find(node->left, val);
            if (_cmp(val, node->data))
                return _find(node->right, val);
            return &node->data;
        }

        void _insert(node_pointer& node, const value_type& val)
        {
            if (_size == 0)
            {
                // create root node
                std::cout << "create root node(" << val << ")" << std::endl;
                node = _create_node(val);
            }
            else if (_cmp(node->data, val))
            {
                if (node->left)
                    _insert(node->left, val);
                else
                {
                    node->left = _create_node(val);
                    node->left->parent = node;
                }
            }
            else
            {
                if (node->right)
                    _insert(node->right, val);
                else
                {
                    node->right = _create_node(val);
                    node->right->parent = node;
                }
            }
        }

        allocator_type _alloc;
        value_compare _cmp;
        size_type _capacity;
        size_type _size;
        node_pointer _root;
    };
}

#endif