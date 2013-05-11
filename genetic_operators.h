/* 
 * File:   genetic_operators.h
 * Author: tomas789
 *
 * Created on May 11, 2013, 3:43 PM
 */

#ifndef GENETIC_OPERATORS_H
#define	GENETIC_OPERATORS_H

#include "node.h"

#include <vector>

class genetic_operators_helper
{
    void linearize_tree_helper(std::size_t i, std::vector<node*> v) {
        if (!v[i]->is_terminal()) {
            v.push_back(v[i]->left_->get());
            v.push_back(v[i]->right_->get());
            linearize_tree_helper(v.size() - 1, v);
            linearize_tree_helper(v.size(), v);
        }
    }

    inline std::vector<node *> linearize_tree(node * n) {
        std::vector<node*>res(1, n);
        linearize_tree_helper(res.size(), res);
        return res;
    }
};

#endif	/* GENETIC_OPERATORS_H */

