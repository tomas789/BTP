//
//  tree.cpp
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#include "tree.h"

#include "node.h"
#include "stochastic.h"

tree::tree() : tree_(nullptr)
{ }

tree::tree(const tree & t) {
    *this = t;
}

tree::tree(tree && t) {
    *this = std::move(t);
}

tree::tree(std::unique_ptr<node> && tree) : tree_(std::move(tree))
{ }

tree & tree::operator= (const tree & t) {
    tree_ = std::move(t.tree_->clone());
    return *this;
}

tree & tree::operator= (tree && t) {
    tree_ = std::move(t.tree_);
    return *this;
}

node * tree::operator-> () const {
    return tree_.get();
}

tree::iterator tree::this_iterator() {
    return iterator(tree_.get());
}

tree::iterator tree::end() {
    return iterator();
}

tree::iterator tree::random_node() {
    std::vector<tree::iterator> v;
    dfs(*this, [&](tree::iterator & t) { v.push_back(t); });
    if (0 == v.size()) return tree::iterator();
    else return v[stochastic::get_max(v.size() - 1)];
}

tree::subtree_iterator tree::random_subtree() {
    std::vector<tree::subtree_iterator> v;
    dfs(*this, [&](tree::iterator & t) {
        if (! t->is_terminal()) {
            v.push_back(std::make_pair(t, tree::subtree::left));
            v.push_back(std::make_pair(t, tree::subtree::right));
        }
    });
    if (!v.size()) return std::make_pair(tree::iterator(), tree::subtree::left);
    else return v[stochastic::get_max(v.size() - 1)];
}

tree tree::random(std::size_t depth) {
    return tree(std::move(::random(depth)));
}

std::ostream & operator << (std::ostream & out, const tree & t) {
    return t->print(out);
}
