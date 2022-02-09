/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeValue.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 20:04:04 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/09 00:58:45 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODEVALUE_HPP
# define NODEVALUE_HPP

# include "tree/NodeBase.hpp"

namespace ft
{
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
} // namespace ft

#endif
