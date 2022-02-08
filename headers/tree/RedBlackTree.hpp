/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BinarySeaTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:04:50 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/08 00:16:57 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <memory>
# include <functional>
# include "iterator/reverse_iterator.hpp"
# include "tree/BTIterator.hpp"
# include <map>

namespace ft
{
    template <
        typename T,
        typename Compare = std::less<T>,
        typename Alloc = std::allocator<T>
    >
    class RedBlackTree
    {
    public:
        // ---------------------------------------------------------------------
        // Member types
        // ---------------------------------------------------------------------
        
        typedef T                                                           value_type;
        // use rebind to change the T allocator to NodeBase<T> allocator
        typedef typename Alloc::template rebind<ft::NodeValue<T> >::other   allocator_type;
        typedef value_type&                                                 reference;
        typedef const value_type&                                           const_reference;
        typedef value_type*                                                 pointer;
        typedef const value_type*                                           const_pointer;
        typedef Compare                                                     value_compare;
        typedef ft::BTIterator<T>                                           iterator;
        typedef ft::BTIterator<const T>                                     const_iterator;
        typedef ft::reverse_iterator<iterator>                              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;
        typedef typename iterator::difference_type                          difference_type;
        typedef typename allocator_type::size_type                          size_type;
        typedef ft::NodeBase                                                node_base;       
        typedef ft::NodeValue<T>                                            node_value;                    
        typedef node_base*                                                  node_pointer;

        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------

        RedBlackTree(
            const value_compare& cmp = value_compare(),
            const allocator_type& alloc = allocator_type()) :
            _alloc(alloc),
            _cmp(cmp),
            _root(NULL),
            _nil(new NodeBase())
        {
            _nil->color = BLACK;
        }

        RedBlackTree(const RedBlackTree& rhs) :
            _alloc(rhs._alloc),
            _cmp(rhs._cmp),
            _nil(new NodeBase())
        {
            _nil->color = BLACK;
            _updateRoot(_copy(rhs._root));
        }

        virtual RedBlackTree& operator=(const RedBlackTree& rhs)
        {
            if (this != &rhs)
            {
                this->clear();
                _updateRoot(_copy(rhs._root));
            }
            return *this;
        }
        
        virtual ~RedBlackTree()
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
            return !_root;
        }

        size_type size() const
        {
            return _root ? _root->size() : 0;
        }

        size_type max_size() const
        {
            return _alloc.max_size();
        }

        // ---------------------------------------------------------------------
        // Modifiers
        // ---------------------------------------------------------------------

        virtual iterator insert(const value_type& val)
        {
            node_pointer node = _insert(this->_root, _nil, val);
            _insert_fixup(node);
            return node;
        }

        void erase(const value_type& val)
        {
            _erase(this->_root, val);
        }

        void erase(const_iterator position)
        {
            _erase(position._node);
        }

        // swap method
        void swap(RedBlackTree& rhs)
        {
            std::swap(this->_root, rhs._root);
            std::swap(this->_nil, rhs._nil);
            std::swap(this->_cmp, rhs._cmp);
            std::swap(this->_alloc, rhs._alloc);
        }

        void clear()
        {
            _clear(this->_root);
        }

        // ---------------------------------------------------------------------
        // Observers
        // ---------------------------------------------------------------------
        
        value_compare value_comp() const
        {
            return _cmp;
        }

        // ---------------------------------------------------------------------
        // Operations
        // ---------------------------------------------------------------------

        iterator find(const value_type& val) const
        {
            return _find(this->_root, val);
        }

        iterator find(const_iterator hint, const value_type& val) const
        {
            if (hint != this->end() && _cmp(*hint, val)) // check if the hint is valid
            {
                iterator max = hint._node->maximum();
                if (_cmp(val, *max)) // check if the value is under the hint._node subtree
                    return _find(hint._node->right, val); // find in the right subtree
                return this->find(++max, val); // find in the upper subtree
            }
            return this->find(val);
        }

        // ---------------------------------------------------------------------
        // Allocator
        // ---------------------------------------------------------------------

        allocator_type get_allocator() const
        {
            return _alloc;
        }

        // ---------------------------------------------------------------------
        // Tree operations
        // ---------------------------------------------------------------------

        size_type height() const
        {
            return _root ? _root->height() : 0;
        }
        
        node_pointer minimum() const
        {
            return _root ? _root->minimum() : _nil;
        }

        node_pointer maximum() const
        {
            return _root ? _root->maximum() : _nil;
        }

    protected:

        // ---------------------------------------------------------------------
        // Protected methods
        // ---------------------------------------------------------------------

        void _updateRoot(node_pointer node)
        {
            this->_root = node;
            this->_nil->left = node;
        }

        node_pointer _insert(node_pointer& node, node_pointer parent, const value_type& val)
        {
            if (node == NULL) // empty tree
            {
                node = _create_value_node(val, parent);
                parent->left = node;
                return node;
            }
            if (!node->parent) // nil node
            {
                node = _create_value_node(val, parent);
                return node;
            }
            if (_cmp(val, node_value::getData(node)))
                return _insert(node->left, node, val);
            return _insert(node->right, node, val);
        }

        void _erase(node_pointer& node)
        {
            node_pointer successor;

            if (!node) // empty tree
                return ;
            else if (!node->left->parent && !node->right->parent) // case 1: leaf node
            {
                successor = _nil;
                node->set_parent_child(_nil);
                if (node == this->_root)
                    _updateRoot(NULL);
            }
            else if (!node->left->parent) // case 2: right child only
            {
                successor = node->right;
                node->set_parent_child(successor);
                successor->parent = node->parent;
                if (this->_root == node)
                    _updateRoot(successor);
            }
            else if (!node->right->parent) // case 3: left child only
            {
                successor = node->left;
                node->set_parent_child(successor);
                successor->parent = node->parent;
                if (this->_root == node)
                    _updateRoot(successor);
            }
            else // case 4: two children
            {
                successor = node->right->minimum();
                node->set_parent_child(successor);
                std::swap(node->color, successor->color);
                if (successor == node->right)
                {
                    /*
                     * Connected nodes
                     *
                     *       |
                     *      node
                     *    /     \
                     *        successor
                     *        /     \
                     */
                    node->right = successor->right;
                    successor->parent = node->parent;
                    successor->update_right(node);
                    node->parent = successor;

                    // swap left
                    node_pointer tmp = node->left;
                    node->update_left(successor->left);
                    successor->update_left(tmp);
                }
                else
                {
                    /*
                     * Disconnected nodes
                     *
                     *       |
                     *      node
                     *    /     \
                     * 
                     * 
                     *         |
                     *      successor
                     *      /     \
                     *
                     */
                    successor->set_parent_child(node);
                    std::swap(node->parent, successor->parent);

                    // swap left
                    node_pointer tmp = node->left;
                    node->update_left(successor->left);
                    successor->update_left(tmp);

                    // swap right
                    tmp = node->right;
                    node->update_right(successor->right);
                    successor->update_right(tmp);
                }
                if (this->_root == node)
                    _updateRoot(successor);
                _erase(node);
                return ;
            }
            bool prev_color = node->color;
            _free(node);
            if (prev_color == BLACK)
                _erase_fixup(successor);
        }

        void _erase(node_pointer node, const value_type& val)
        {
            if (!node || !node->parent) // empty tree or nil node
                return ;
            const value_type& data = node_value::getData(node);
            if (_cmp(val, data))
                _erase(node->left, val);
            else if (_cmp(data, val))
                _erase(node->right, val);
            // there is an equality and we are going to erase this node
            else
                _erase(node);
        }

        iterator _find(node_pointer node, const value_type& val) const
        {
            if (!node || !node->parent) // empty tree or nil node
                return _nil;
            const value_type& data = node_value::getData(node);
            if (_cmp(val, data))
                return _find(node->left, val);
            if (_cmp(data, val))
                return _find(node->right, val);
            return node;
        }
        
        node_pointer _copy(node_pointer node, node_pointer parent = NULL)
        {
            if (!node) // empty tree
                return NULL;
            if (!node->parent) // is nil node
                return _nil;
            return _create_value_node(
                node_value::getData(node),
                parent,
                _copy(node->left, node),
                _copy(node->right, node)
            );
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
            node->parent = parent ? parent : _nil;
            node->left = left ? left : _nil;
            node->right = right ? right : _nil;
            return node;
        }

        void _clear(node_pointer& node)
        {
            if (!node || !node->parent) // empty tree or nil node
                return ;
            _clear(node->left);
            _clear(node->right);
            _free(node);
        }

        void _free(node_pointer& node)
        {
            if (!node || !node->parent) // empty tree or nil node
                return ;
            node_value* ptr = static_cast<ft::NodeValue<T>*>(node);
            _alloc.destroy(ptr);
            _alloc.deallocate(ptr, 1);
            node = _nil;
        }

        static bool _node_is_black(node_pointer node)
        {
            return !node || node->color == BLACK;
        }

        static bool _node_is_red(node_pointer node)
        {
            return node && node->color == RED;
        }

        // ---------------------------------------------------------------------
        // Rotations
        // ---------------------------------------------------------------------

        /**
         * @brief Right Rotate
         * 
         *
         * Converts a tree with the format
         *        y                    x
         *       / \                  / \
         *      x   C     into       A   y
         *     / \                      / \
         *    A   B                    B   C
         * 
         * The operations we need to perform are:
         *  - x right child is y (instead of B)
         *  - y left child is B (instead of x)
         *  - change B parent to y (instead of x)
         *  - swap x and y parents
         * 
         * updates root if necessary
         *
         * @param node 
         */
        node_pointer _right_rotate(node_pointer y)
        {
            node_pointer x = y->left;
            node_pointer b = x->right;
            node_pointer parent = y->parent;

            x->right = y;
            y->left = b;
            if (b->parent) // b is not nil
                b->parent = y;
            y->parent = x;
            x->parent = parent;
            if (!parent->parent) // parent is nil
                _updateRoot(x);
            else if (parent->left == y)
                parent->left = x;
            else
                parent->right = x;
            return x;
        }
        
        /**
         * @brief Left Rotate
         * 
         * Converts a tree with the format
         *        x                    y
         *       / \                  / \
         *      A   y     into       x   C
         *         / \              / \
         *        B   C            A   B
         * 
         * The operations we need to perform are:
         *  - x right child is B (instead of y)
         *  - y left child is x (instead of A)
         *  - change B parent to x (instead of y)
         *  - swap x and y parents
         * 
         * updates root if necessary
         * 
         * @param x 
         * @return node_pointer 
         */
        node_pointer _left_rotate(node_pointer x)
        {
            node_pointer y = x->right;
            node_pointer b = y->left;
            node_pointer parent = x->parent;

            y->left = x;
            x->right = b;
            if (b->parent) // b is not nil
                b->parent = x;
            x->parent = y;
            y->parent = parent;
            if (!parent->parent) // parent is nil
                _updateRoot(y);
            else if (parent->left == x)
                parent->left = y;
            else
                parent->right = y;
            return y;
        }

        // ---------------------------------------------------------------------
        // Fixups
        // ---------------------------------------------------------------------

        void _insert_left_parent_fixup(node_pointer node)
        {
            node_pointer uncle = node->parent->parent->right;
            if (uncle->color == RED) // change the colors
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                _insert_fixup(node->parent->parent); // apply the fixup to the grandparent
            }
            else // uncle is black
            {
                if (node == node->parent->right) // case 1: node is right child
                {
                    node = node->parent;
                    _left_rotate(node);
                }
                _right_rotate(node->parent->parent);
                node->parent->color = BLACK;
                node->parent->right->color = RED; // old grandparent is now red
            }
        }

        void _insert_right_parent_fixup(node_pointer node)
        {
            node_pointer uncle = node->parent->parent->left;
            if (uncle->color == RED) // change the colors
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                _insert_fixup(node->parent->parent); // apply the fixup to the grandparent
            }
            else // uncle is black
            {
                if (node == node->parent->left) // case 1: node is left child
                {
                    node = node->parent;
                    _right_rotate(node);
                }
                _left_rotate(node->parent->parent);
                node->parent->color = BLACK;
                node->parent->left->color = RED; // old grandparent is now red
            }
        }

        void _insert_fixup(node_pointer node)
        {
            if (!node->parent) // nil node
                return ;
            if (node == this->_root)
            {
                node->color = BLACK;
                return ;
            }
            if (node->parent->color == BLACK)
                return ;
            // parent is red
            if (node->parent->parent->left == node->parent) // parent is left child
                _insert_left_parent_fixup(node);
            else // parent is right child
                _insert_right_parent_fixup(node);
        }

        void _erase_left_fixup(node_pointer& node)
        {
            node_pointer sibling = node->parent->right;
            
            if (sibling->color == RED) // case 1: sibling is red
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                _left_rotate(node->parent);
                sibling = node->parent->right;
            }
            if (_node_is_black(sibling->left) && _node_is_black(sibling->right)) // case 2: sibling is black and both children are black
            {
                sibling->color = RED;
                node = node->parent;
                _erase_fixup(node);
            }
            else // case 3: sibling is black and at least one child is red
            {
                if (_node_is_black(sibling->right)) // case 3.1: sibling is black and left child is red
                {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    _right_rotate(sibling);
                    sibling = node->parent->right;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                _left_rotate(node->parent);
                node = this->_root;
            }
        }

        void _erase_right_fixup(node_pointer& node)
        {
            node_pointer sibling = node->parent->left;

            if (sibling->color == RED) // case 1: sibling is red
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                _right_rotate(node->parent);
                sibling = node->parent->left;
            }
            if (_node_is_black(sibling->right) && _node_is_black(sibling->left)) // case 2: sibling is black and both children are black
            {
                sibling->color = RED;
                node = node->parent;
                _erase_fixup(node);
            }
            else // case 3: sibling is black and at least one child is red
            {
                if (_node_is_black(sibling->left)) // case 3.1: sibling is black and right child is red
                {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    _left_rotate(sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                _right_rotate(node->parent);
                node = this->_root;
            }
        }

        void _erase_fixup(node_pointer& node)
        {
            if (node != _root && node != _nil && node->color == BLACK)
            {
                if (node == node->parent->left)
                    _erase_left_fixup(node);
                else
                    _erase_right_fixup(node);
            }
            node->color = BLACK;
        }
    
        // ---------------------------------------------------------------------
        // Protected data members
        // ---------------------------------------------------------------------

        allocator_type _alloc;
        value_compare _cmp;
        node_pointer _root;
        node_pointer _nil;
    };

    // swap method
    template <typename T, typename Compare, typename Alloc>
    void swap(RedBlackTree<T, Compare, Alloc>& lhs, RedBlackTree<T, Compare, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif
