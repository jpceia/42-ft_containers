/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BSTNode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:59:47 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/02 12:20:11 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSTNODE_HPP
# define BSTNODE_HPP

namespace ft
{    
    template <typename T>
    struct BSTNode
    {
        T data;
        BSTNode* parent;
        BSTNode* left;
        BSTNode* right;

        BSTNode(
            const T& data,
            BSTNode* parent = NULL,
            BSTNode* left = NULL,
            BSTNode* right = NULL) :
            data(data),
            parent(parent),
            left(left),
            right(right)
        {}

        BSTNode(const BSTNode& rhs) :
            data(rhs.data),
            parent(rhs.parent),
            left(rhs.left),
            right(rhs.right)
        {}

        /*
        virtual BSTNode& operator=(const BSTNode& rhs)
        {
            if (this != &rhs)
            {
                data = rhs.data;
                parent = rhs.parent;
                left = rhs.left;
                right = rhs.right;
            }
            return *this;
        }
        */
        
        virtual ~BSTNode()
        {}
    

        BSTNode* minimum()
        {
            BSTNode* node = this;

            while (node->left)
                node = node->left;
            return node;
        }

        /*
        const BSTNode* minimum() const
        {
            return const_cast<BSTNode*>(this->minimum());
        }
        */

        BSTNode* maximum()
        {
            BSTNode* node = this;

            while (node->right)
                node = node->right;
            return node;
        }

        /*
        const BSTNode* maximum() const
        {
            return const_cast<BSTNode*>(this->maximum());
        }
        */

        size_t size() const {
            size_t size = 1;
            if (this->left)
                size += this->left->size();
            if (this->right)
                size += this->right->size();
            return size;
        }
    };
}

#endif