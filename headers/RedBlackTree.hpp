/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:58:59 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/27 13:15:27 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

#include <memory>

namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class RBTNode
    {
    public:
        typedef T                                   value_type;
        typedef Alloc                               allocator_type;
        typedef typename Alloc::reference           reference;
        typedef typename Alloc::const_reference     const_reference;
        typedef typename Alloc::size_type           size_type;
        typedef typename Alloc::difference_type     difference_type;
        typedef typename Alloc::pointer             pointer;
        typedef typename Alloc::const_pointer       const_pointer;

        RBTNode()
            : _color(false)
        {}

        RBTNode(const value_type& val)
            : _val(val), _color(false)
        {}

        RBTNode(const value_type& val, bool color)
            : _val(val), _color(color)
        {}

        ~RBTNode() {
        }

        reference getData()
        {
            return _data;
        }

        const_reference getData() const
        {
            return _data;
        }

        void setData(const value_type& val)
        {
            _data = val;
        }

        bool getColor() const
        {
            return _color;
        }

        void setColor(bool color)
        {
            _color = color;
        }

        pointer getLeft()
        {
            return _left;
        }

        pointer getRight()
        {
            return _right;
        }

        pointer getParent()
        {
            return _parent;
        }

        pointer getGrandParent()
        {
            return _parent ? _parent->_parent : NULL;
        }

        void setLeft(pointer left)
        {
            _left = left;
        }

        void setRight(pointer right)
        {
            _right = right;
        }

        void setParent(pointer parent)
        {
            _parent = parent;
        }

        bool isLeftChild() const
        {
            return _parent ? _parent->_left == this : false;
        }
        
        bool isRightChild() const
        {
            return _parent ? _parent->_right == this : false;
        }
        
    private:
        RBTNode* _parent;
        RBTNode* _left;
        RBTNode* _right;
        bool _color;
        value_type _data;
    };
    
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
        typedef T                                   value_type;
        typedef Compare                             value_compare;
        typedef Allocator                           allocator_type;
        typedef typename Alloc::reference           reference;
        typedef typename Alloc::const_reference     const_reference;
        typedef typename Alloc::size_type           size_type;
        typedef typename Alloc::difference_type     difference_type;
        typedef typename Alloc::pointer             pointer;
        typedef typename Alloc::const_pointer       const_pointer;

        // ---------------------------------------------------------------------
        // Constructors
        // ---------------------------------------------------------------------
        explicit RedBlackTree(
            const value_compare& comp = value_compare(),
            const allocator_type& alloc = allocator_type()) :
            _comp(comp),
            _alloc(alloc),
            _root(NULL)
        {}

        RedBlackTree(const RedBlackTree& other) :
            _comp(other._comp),
            _alloc(other._alloc),
            _root(other._root)
        {}

        virtual ~RedBlackTree()
        {
            // _root->destroy(_alloc);
            delete _root;
        }

        RedBlackTree& operator=(const RedBlackTree& other)
        {
            if (this != &other)
            {
                // delete old stuff to avoid leaks
                _comp = other._comp;
                _alloc = other._alloc;
                _root = other._root;
            }
            return *this;
        }

        // ---------------------------------------------------------------------
        RBTNode *root() const
        {
            return _root;
        }

        RBTNode *find(const value_type& val) const;

        void erase(const value_type& val);

        reference insert(const value_type& val);
        
        
    private:
        RBTNode<T, Alloc>* _root;
    };
    
} // namespace ft

#endif
