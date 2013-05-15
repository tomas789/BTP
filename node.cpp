//
//  node.cpp
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#include "node.h"

#include "stochastic.h"
#include "node_non_terminal.h"
#include "non_terminal.h"
#include "node_terminal.h"
#include "terminal.h"

tree random(unsigned depth) {
    node * n = nullptr;
    if (depth) {
        tree left = random(depth - 1);
        tree right = random(depth - 1);
        switch (stochastic::get_max(3)) {
            case 0:
                n = (node *) new non_terminal<node_non_terminal::type::addition>(std::move(left.tree_),
                                                                                 std::move(right.tree_));
                break;
            case 1:
                n = (node *) new non_terminal<node_non_terminal::type::subtraction>(std::move(left.tree_),
                                                                                    std::move(right.tree_));
                break;
            case 2:
                n = (node *) new non_terminal<node_non_terminal::type::multiplication>(std::move(left.tree_),
                                                                                       std::move(right.tree_));
                break;
            case 3:
                n = (node *) new non_terminal<node_non_terminal::type::protected_division>(std::move(left.tree_),
                                                                                           std::move(right.tree_));
                break;
            default:
                throw "should never reach this";
                break;
        }
    } else {
        if (stochastic::get_bool()) {
            n = (node *) new terminal<node_terminal::type::constant>(stochastic::get_minmax(run_config::tree::min_value,
                                                                                            run_config::tree::max_value)
                                                                     );
        } else {
            n = (node *) new terminal<node_terminal::type::variable>(stochastic::get_max(run_config::tree::num_variables - 1));
        }
    }
    
    // Return and transfer ownership
    return tree(std::unique_ptr<node>(n));
}

void swap(tree::subtree_iterator &lhs, tree::subtree_iterator &rhs)
{
    auto left = (node_non_terminal *) lhs.first.operator->();
    auto right = (node_non_terminal *) rhs.first.operator->();
    std::unique_ptr<node> tmp;
    if (lhs.second == tree::subtree::left && rhs.second == tree::subtree::left)
        std::swap(left->left_, right->left_);
    else if (lhs.second == tree::subtree::left && rhs.second == tree::subtree::right)
        std::swap(left->left_, right->right_);
    else if (lhs.second == tree::subtree::right && rhs.second == tree::subtree::left)
        std::swap(left->right_, right->left_);
    else if (lhs.second == tree::subtree::right && rhs.second == tree::subtree::right)
        std::swap(left->right_, right->right_);
}