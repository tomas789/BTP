//
//  node_non_terminal.h
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#ifndef __BTP__node_non_terminal__
#define __BTP__node_non_terminal__

class tree;

#include <iostream>
#include <memory>

#include "tree.h"
#include "node.h"

class node_non_terminal : public node
{
protected:
    std::unique_ptr<node> left_;
    std::unique_ptr<node> right_;
public:
    enum class type {
        addition,
        subtraction,
        multiplication,
        protected_division
    };
    
    node_non_terminal();
    node_non_terminal(tree && left, tree && right);
    
    virtual node::value_type eval(const valuation & v) const = 0;
    bool is_terminal() const;
    virtual std::string operator_str() const = 0;
    std::ostream & print(std::ostream & out) const;
    virtual std::unique_ptr<node> clone() const = 0;
    
    friend class tree_iterator;
    friend void swap( tree::subtree_iterator& a, tree::subtree_iterator& b );
};

#endif /* defined(__BTP__node_non_terminal__) */
