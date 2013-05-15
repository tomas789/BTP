//
//  tree.h
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#ifndef BTP_tree_h
#define BTP_tree_h

class node;

#include <memory>

#include "tree_iterator.h"

class tree
{
    std::unique_ptr<node> tree_;
public:
    using iterator = tree_iterator;
    
    enum class subtree { left, right };
    using subtree_iterator = std::pair<iterator, subtree>;
    
    tree();
    tree(const tree & t);
    tree(tree && t);
    tree(std::unique_ptr<node> && tree);
    tree & operator= (const tree & t);
    tree & operator= (tree && t);
    
    /**
     * OBSOLETED
     * Access associated tree's root node
     */
    node * operator-> ();
    
    iterator this_iterator();
    
    /**
     * Returns equivalent to STL end()
     */
    iterator end();
    
    /**
     * Get iterator to random subtree
     */
    iterator random_node();
    
    subtree_iterator random_subtree();
    
    friend class node_non_terminal;
    friend tree random(unsigned depth);
    friend class tree_iterator;
};

#endif
