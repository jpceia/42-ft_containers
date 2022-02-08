/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:48:03 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/08 04:15:53 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "tree/RedBlackTree.hpp"

typedef ft::NodeBase* node_pointer;

/**
 * @brief Checks the third rule of the red-black tree.
 * 
 * There are no two adjacent red nodes
 * (A red node cannot have a red parent or red child).
 * 
 * @param node 
 * @return true 
 * @return false 
 */
bool    rbtree_check_third_rule(node_pointer node)
{
    if (!node || !node->parent) // empty tree or nil node
        return (true);
    if (node->color == RED && node->parent->color == RED)
        return (false);
    return (rbtree_check_third_rule(node->left) && rbtree_check_third_rule(node->right));
}


/**
 * @brief Checks the fourth rule of the red-black tree.
 * 
 * Every path from a node (including root) to any of its descendants NULL nodes
 * has the same number of black nodes.
 * 
 * @param node 
 * @return int 
 */
int rbtree_check_fourth_rule(node_pointer node)
{
    // checks if the black height of the left subtree is equal to the black height of the right subtree
    if (!node || !node->parent) // empty tree or nil node
        return (true);
    if (node->left->black_height() != node->right->black_height())
        return (false);
    return (rbtree_check_fourth_rule(node->left) && rbtree_check_fourth_rule(node->right));
}


/**
 * @brief Checks if the children of a node have the correct parent (the node).
 * 
 * @param node 
 * @return int 
 */
int rbtree_check_valid_parents(node_pointer node)
{
    if (!node || !node->parent) // empty tree or nil node
        return (true);
    if (!(!node->left->parent || node->left->parent == node))
        return (false);
    if (!(!node->right->parent || node->right->parent == node))
        return (false);
    return (rbtree_check_valid_parents(node->left) && rbtree_check_valid_parents(node->right));
}

/**
 * @brief Checks if a red-black tree is valid.
 * 
 * @param root 
 * @return int 
 */
int rbtree_check(node_pointer root)
{
    if (!root) // empty tree or nil node
        return (false);
    if (root->color != BLACK)
    {
        std::cerr << "Root is not black" << std::endl;
        return (false);
    }
    if (!rbtree_check_third_rule(root))
    {
        std::cerr << "Third rule violated" << std::endl;
        return (false);
    }
    if (!rbtree_check_fourth_rule(root))
    {
        std::cerr << "Fourth rule violated" << std::endl;
        return (false);
    }
    if (!rbtree_check_valid_parents(root))
    {
        std::cerr << "Parents are not valid" << std::endl;
        return (false);
    }
    return (true);
}


int main()
{
    ft::RedBlackTree<char> tree;

    tree.insert('a');
    tree.insert('t');
    tree.insert('e');
    tree.insert('v');
    tree.insert('b');
    rbtree_check(tree.root());
    tree.insert('i');
    tree.insert('s');
    tree.insert('l');
    tree.insert('z');
    tree.insert('u');
    rbtree_check(tree.root());
    tree.insert('w');
    tree.insert('q');
    tree.insert('c');
    tree.insert('x');
    tree.insert('j');
    rbtree_check(tree.root());
    tree.insert('p');
    tree.insert('n');
    tree.insert('y');
    tree.insert('k');
    tree.insert('m');
    rbtree_check(tree.root());

    ft::RedBlackTree<char>::iterator it = tree.begin();
    for(; it != tree.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';

    tree.erase('y');
    tree.erase('m');
    tree.erase('j');
    tree.erase('k');
    tree.erase('n');
    rbtree_check(tree.root());
    tree.erase('e');
    tree.erase('u');
    tree.erase('s');
    tree.erase('b');
    tree.erase('l');
    rbtree_check(tree.root());
    tree.erase('i');
    tree.erase('a');
    tree.erase('q');
    tree.erase('w');
    tree.erase('p');
    rbtree_check(tree.root());
    tree.erase('x');
    tree.erase('c');
    tree.erase('t');
    tree.erase('v');
    tree.erase('z');
    rbtree_check(tree.root());

    it = tree.begin();
    for(; it != tree.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';

    tree.insert('a');
    tree.insert('b');
    tree.insert('c');
    tree.insert('d');
    tree.insert('e');
    tree.insert('f');
    rbtree_check(tree.root());
    
    it = tree.begin();
    for(; it != tree.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';
    
    tree.erase('c');
    tree.erase('d');

    tree.insert('z');

    tree.erase('a');
    
    tree.insert('g');

    tree.erase('b');

    tree.insert('h');

    rbtree_check(tree.root());
    
    it = tree.begin();
    for(; it != tree.end(); ++it)
        std::cout << *it << ' ';
    std::cout << '\n';

    return 0;
}
