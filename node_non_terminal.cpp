//
//  node_non_terminal.cpp
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#include "node_non_terminal.h"

node_non_terminal::node_non_terminal() {
}

node_non_terminal::node_non_terminal(tree && left, tree && right)
    : left_(std::move(left.tree_)), right_(std::move(right.tree_))
{ }

bool node_non_terminal::is_terminal() const {
    return false;
}

std::ostream & node_non_terminal::print(std::ostream & out) const {
    return right_->print(left_->print(out << "(") << ")" << operator_str() << "(") << ")";
};