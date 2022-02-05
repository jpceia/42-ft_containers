/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySearchTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:04:50 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/04 17:56:30 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BINARYSEARCHTREE_HPP
# define BINARYSEARCHTREE_HPP

# include <memory>
# include <functional>
# include "iterator/reverse_iterator.hpp"
# include "tree/BSTIterator.hpp"
# include <map>

namespace ft
{
    template <
        typename T,
        typename Compare = std::less<T>,
        typename Alloc = std::allocator<T>
    >
    class BinarySearchTree
    {
    public:
        typedef T                                                       value_type;
        // use rebind to change the T allocator to NodeBase<T> allocator
        typedef typename Alloc::template rebind<ft::NodeValue<T> >::other    allocator_type;
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
        typedef ft::NodeBase                                            node_base;       
        typedef ft::NodeValue<T>                                        node_value;                    
        typedef node_base*                                              node_pointer;

        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------

        BinarySearchTree(
            const value_compare& cmp = value_compare(),
            const allocator_type& alloc = allocator_type()) :
            _alloc(alloc),
            _cmp(cmp)
        { 
            _root = new NodeBase();
            _nil = _root;
        }

        BinarySearchTree(const BinarySearchTree& rhs) :
            _alloc(rhs._alloc),
            _cmp(rhs._cmp)
        {
            this->_root = _copy(rhs._root, NULL);
        }

        virtual BinarySearchTree& operator=(const BinarySearchTree& rhs)
        {
            if (this != &rhs)
            {
                _clear(this->_root);
                if (!rhs.empty())
                    this->_root = _copy(rhs._root, NULL);
            }
            return *this;
        }
        
        virtual ~BinarySearchTree()
        {
            this->clear();
            delete _nil;
        }

        // ---------------------------------------------------------------------
        // Iterators
        // ---------------------------------------------------------------------

        iterator begin()
        {
            return this->minimum();
        }

        const_iterator begin() const
        {
            return this->minimum();
        }

        iterator end()
        {
            return _nil;
        }

        const_iterator end() const
        {
            return _nil;
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

        // ---------------------------------------------------------------------
        // Capacity
        // ---------------------------------------------------------------------

        bool empty() const
        {
            return _root == _nil;
        }

        size_t size() const
        {
            return _root == _nil ? 0 : _root->size();
        }
        
        node_pointer minimum() const
        {
            return _root == _nil ? NULL : _root->minimum();
        }

        node_pointer maximum() const
        {
            return _root == _nil ? NULL : _root->maximum();
        }

        iterator find(const value_type& val) const
        {
            return _find(this->_root, val);
        }

        virtual iterator insert(const value_type& val)
        {
            return insert(this->_root, NULL, val);
        }

        virtual iterator insert(node_pointer& node, node_pointer parent, const value_type& val)
        {
            if (node == _nil)
            {
                node = _create_value_node(val);
                node->parent = parent;
                return node;
            }
            if (_cmp(val, node_value::getData(node)))
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

        void erase(node_pointer& node)
        {
            if (node->left == _nil && node->right == _nil) // case 1: leaf node
            {
                node->set_parent_child(_nil);
                if (node == this->_root)
                    this->_root = _nil;
            }
            else if (node->right != _nil) // case 2: right child only
            {
                node->set_parent_child(node->right);
                node->right->parent = node->parent;
                if (this->_root == node)
                    this->_root = node->right;
            }
            else if (node->left != _nil) // case 3: left child only
            {
                node->set_parent_child(node->left);
                node->left->parent = node->parent;
                if (this->_root == node)
                    this->_root = node->left;
            }
            else // case 4: two children
            {
                node_pointer successor = node->successor();
                node_pointer new_node = _create_value_node(node_value::getData(node),
                    node->parent, node->left, node->right);
                node->set_parent_child(new_node);
                if (this->_root == node)
                    this->_root = new_node;
                erase(successor);
            }
            _free(node);
        }

        // swap method
        void swap(BinarySearchTree& rhs)
        {
            std::swap(this->_root, rhs._root);
            std::swap(this->_nil, rhs._nil);
            std::swap(this->_cmp, rhs._cmp);
            std::swap(this->_alloc, rhs._alloc);
        }
        
    protected:

        iterator _find(node_pointer node, const value_type& val) const
        {
            if (node == _nil)
                return _nil;
            const value_type& data = node_value::getData(node);
            if (_cmp(val, data))
                return _find(node->left, val);
            if (_cmp(data, val))
                return _find(node->right, val);
            return node;
        }
        
        node_pointer _copy(node_pointer node, node_pointer parent)
        {
            if (node->parent == NULL && parent != NULL) // is nil node
                return _nil;
            node_value* new_node = _alloc.allocate(1);
            value_type data = node_value::getData(node);
            _alloc.construct(new_node, data);
            new_node->parent = parent;
            new_node->left = _copy(node->left, new_node);
            new_node->right = _copy(node->right, new_node);
            return new_node;
        }

        node_pointer _create_value_node(
            const value_type& val = value_type(),
            const node_pointer& parent = NULL,
            const node_pointer& left = NULL,
            const node_pointer& right = NULL
        )
        {
            node_value *node = _alloc.allocate(1);
            _alloc.construct(node, val);
            node->parent = parent;
            node->left = left ? left : _nil;
            node->right = right ? right : _nil;
            return node;
        }

        void _free(node_pointer& node)
        {
            if (node == _nil)
                return ;
            node_value* ptr = static_cast<ft::NodeValue<T>*>(node);
            _alloc.destroy(ptr);
            _alloc.deallocate(ptr, 1);
            node = _nil;
        }

        void _clear(node_pointer& node)
        {
            if (node == _nil)
                return ;
            _clear(node->left);
            _clear(node->right);
            _free(node);
        }

        virtual void _erase(node_pointer node, const value_type& val)
        {
            if (node == _nil)
                return ;
            const value_type& data = node_value::getData(node);
            if (_cmp(val, data))
                _erase(node->left, val);
            else if (_cmp(data, val))
                _erase(node->right, val);
            // there is an equality and we are going to erase this node
            else
                this->erase(node);
        }

        node_pointer _root;
        node_pointer _nil;
        allocator_type _alloc;
        value_compare _cmp;
    };

    // swap method
    template <typename T, typename Compare, typename Alloc>
    void swap(BinarySearchTree<T, Compare, Alloc>& lhs, BinarySearchTree<T, Compare, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif
