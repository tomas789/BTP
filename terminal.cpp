//
//  terminal.cpp
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#include "terminal.h"

terminal<node_terminal::type::constant>::terminal(node::value_type val)
    : val_(val) {
}

node::value_type terminal<node_terminal::type::constant>::eval(const valuation & v) const {
    return val_;
}

std::ostream & terminal<node_terminal::type::constant>::print(std::ostream & out) const {
    return out << val_;
}

std::unique_ptr<node> terminal<node_terminal::type::constant>::clone() const {
    auto p = new terminal<node_terminal::type::constant>(val_);
    return std::unique_ptr<node>((node *) p);
}

terminal<node_terminal::type::variable>::terminal(unsigned num)
    : num_(num) {
}

node::value_type terminal<node_terminal::type::variable>::eval(const valuation & v) const {
    return v[num_];
}

std::ostream & terminal<node_terminal::type::variable>::print(std::ostream & out) const {
    return out << "x_" << num_;
}

std::unique_ptr<node> terminal<node_terminal::type::variable>::clone() const {
    auto p = new terminal<node_terminal::type::variable>(num_);
    return std::unique_ptr<node>((node *) p);
}