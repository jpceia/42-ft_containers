/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:16:26 by jceia             #+#    #+#             */
/*   Updated: 2022/02/04 12:33:36 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# define RED false
# define BLACK true

namespace ft
{
    struct NodeBase
    {
        NodeBase *parent;
        NodeBase *left;
        NodeBase *right;
        bool color;

        NodeBase()
            : parent(NULL), left(NULL), right(NULL), color(RED)
        {}

        virtual ~NodeBase() {}

        NodeBase *minimum()
        {
            NodeBase *node = this;

            while (node->left->parent)
                node = node->left;
            return node;
        }

        /*
        const NodeBase* minimum() const
        {
            return const_cast<NodeBase*>(this->minimum());
        }
        */

        NodeBase *maximum()
        {
            NodeBase *node = this;

            while (node->right->parent)
                node = node->right;
            return node;
        }

        /*
        const NodeBase* maximum() const
        {
            return const_cast<NodeBase*>(this->maximum());
        }
        */

        size_t size() const
        {
            size_t size = 1;
            if (this->left->parent)
                size += this->left->size();
            if (this->right->parent)
                size += this->right->size();
            return size;
        }

        size_t height() const
        {
            if (!this->parent)
                return 1;
            return std::max(this->left->height(), this->right->height()) + 1;
        }

        size_t black_height() const
        {
            if (!this->parent)
                return 1;
            size_t bheight = this->color == BLACK ? 1 : 0;
            bheight = std::max(bheight, this->left->black_height());
            bheight = std::max(bheight, this->right->black_height());
            return bheight;
        }

        void set_parent_child(NodeBase *node)
        {
            if (this->parent->parent)
            {
                if (this->parent->left == this)
                    this->parent->left = node;
                else
                    this->parent->right = node;
            }
        }


        void update_left(NodeBase *node)
        {
            this->left = node;
            if (node->parent)
                node->parent = this;
        }

        void update_right(NodeBase *node)
        {
            this->right = node;
            if (node->parent)
                node->parent = this;
        }

        NodeBase *successor()
        {
            NodeBase* node = this;

            if (node->right->parent)
                return node->right->minimum();
            // goes up until the node is the left child of its parent
            while (node->parent->parent && node == node->parent->right)
                node = node->parent;
            return node->parent;
        }

        NodeBase *predecessor()
        {
            NodeBase* node = this;

            if (node->left->parent)
                return node->left->maximum();
            // goes up until the node is the right child of its parent
            while (node->parent->parent && node == node->parent->left)
                node = node->parent;
            return node->parent;
        }
    };

    template <typename T>
    class NodeValue : public NodeBase
    {
    public:
        NodeValue(
            const T &data,
            NodeBase *parent = NULL, 
            NodeBase *left = NULL,
            NodeBase *right = NULL) :
            data(data)
        {
            this->parent = parent;
            this->left = left;
            this->right = right;
            this->color = RED;
        }

        NodeValue(const NodeValue<T> &rhs) :
            data(rhs.data)
        {
            this->parent = rhs.parent;
            this->left = rhs.left;
            this->right = rhs.right;
        }

        virtual ~NodeValue()
        {
        }

        static T getData(NodeBase *node)
        {
            return static_cast<NodeValue<T>*>(node)->data;
        }

        T data;
    };
}

#endif
