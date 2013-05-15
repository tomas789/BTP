//
//  tree_iterator.cpp
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#include "tree_iterator.h"

#include "node.h"
#include "node_non_terminal.h"

#include <stdexcept>

tree_iterator::tree_iterator()
    : node_(nullptr) {
}

tree_iterator::tree_iterator(const tree & t) {
    node_ = t.tree_.get();
}

tree_iterator::tree_iterator(node * node)
    : node_(node) {
};

tree_iterator tree_iterator::left() {
    if (node_ == nullptr)
        throw std::out_of_range("calling left() on end()");
    else if (node_->is_terminal()) {
        return tree_iterator(nullptr);
    } else {
        node_non_terminal * n = (node_non_terminal *) node_;
        return tree_iterator((node *) (n->left_.get()));
    }
}

tree_iterator tree_iterator::right() {
    if (node_ == nullptr)
        throw std::out_of_range("calling right() on end()");
    else if (node_->is_terminal()) {
        return tree_iterator(nullptr);
    } else {
        node_non_terminal * n = (node_non_terminal *) node_;
        return tree_iterator((node *) n->right_.get());
    }
}

bool tree_iterator::operator!= (const tree_iterator & t) {
    return node_ != t.node_;
}

node * tree_iterator::operator-> () {
    return node_;
}

tree tree_iterator::operator* () {
    return tree(std::move(node_->clone()));
}