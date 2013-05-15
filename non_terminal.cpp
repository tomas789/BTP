//
//  non_terminal.cpp
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#include "non_terminal.h"

template <node_non_terminal::type Type>
non_terminal<Type>::non_terminal(std::unique_ptr<node> && left, std::unique_ptr<node> && right) {
    node_non_terminal::left_ = std::move(left);
    node_non_terminal::right_ = std::move(right);
}

template <>
node::value_type non_terminal<node_non_terminal::type::addition>::eval(const valuation& v) const {
    return node_non_terminal::left_->eval(v) + node_non_terminal::right_->eval(v);
}

template <>
node::value_type non_terminal<node_non_terminal::type::subtraction>::eval(const valuation& v) const {
    return node_non_terminal::left_->eval(v) - node_non_terminal::right_->eval(v);
}

template <>
node::value_type non_terminal<node_non_terminal::type::multiplication>::eval(const valuation& v) const {
    return node_non_terminal::left_->eval(v) * node_non_terminal::right_->eval(v);
}

template <>
node::value_type non_terminal<node_non_terminal::type::protected_division>::eval(const valuation& v) const {
    auto t = node_non_terminal::right_->eval(v);
    t = t == 0 ? 1 : t;
    return node_non_terminal::left_->eval(v) / t;
}

template <>
std::string non_terminal<node_non_terminal::type::addition>::operator_str() const {
    return "+";
}

template <>
std::string non_terminal<node_non_terminal::type::subtraction>::operator_str() const {
    return "-";
}

template <>
std::string non_terminal<node_non_terminal::type::multiplication>::operator_str() const {
    return "*";
}

template <>
std::string non_terminal<node_non_terminal::type::protected_division>::operator_str() const {
    return "/";
}

template <>
std::unique_ptr<node> non_terminal<node_non_terminal::type::addition>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::addition>(std::move(node_non_terminal::left_->clone()),
                                                                 std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}

template <>
std::unique_ptr<node> non_terminal<node_non_terminal::type::subtraction>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::subtraction>(std::move(node_non_terminal::left_->clone()),
                                                                    std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}

template <>
std::unique_ptr<node> non_terminal<node_non_terminal::type::multiplication>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::multiplication>(std::move(node_non_terminal::left_->clone()),
                                                                       std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}

template <>
std::unique_ptr<node> non_terminal<node_non_terminal::type::protected_division>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::protected_division>(std::move(node_non_terminal::left_->clone()),
                                                                           std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}