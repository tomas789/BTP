//
//  tree_iterator.h
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#ifndef BTP_tree_iterator_h
#define BTP_tree_iterator_h

class tree;
class node;

/**
 * Iterator into the tree.
 * tree_iterator::tree_iterator() is equivalent to end()
 */
class tree_iterator
{
    node * node_;
public:
    tree_iterator();
    tree_iterator(const tree & t);
    tree_iterator(node * node);
    
    /**
     * Get left subtree
     * Throws std::out_of_range when called on end()
     */
    tree_iterator left();
    
    /**
     * Get right subtree
     * Throws std::out_of_range when called on end()
     */
    tree_iterator right();
    bool operator!= (const tree_iterator & t);
    node * operator-> ();
    tree operator* ();
};

#endif
