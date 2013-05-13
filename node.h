/* 
 * File:   tree.h
 * Author: tomas789
 *
 * Created on May 9, 2013, 5:42 PM
 */

#ifndef NODE_H
#define	NODE_H

#include "compile_config.h"
#include "valuation.h"
#include "stochastic.h"

#include <memory>
#include <stdexcept>


class node 
{
public:
    using value_type = compile_config::tree::value_type;
    
    virtual value_type eval(const valuation & v) const = 0;
    virtual bool is_terminal() const = 0;
    virtual std::ostream & print(std::ostream & out) const = 0;
    virtual std::unique_ptr<node> clone() const = 0;
};

class tree;

class tree_iterator 
{
    tree * tree_;
    node * node_;
public:
    tree_iterator() : tree_(nullptr), node_(nullptr) { }
    tree_iterator(const tree & t);
    tree_iterator & left();
    tree_iterator & right();
    bool operator!= (const tree_iterator & t);
    node * operator-> ();
    tree operator* ();
};

class tree
{
    std::unique_ptr<node> tree_;
public:
    using iterator = tree_iterator;
    
    tree() : tree_(nullptr) { };
    tree(const tree & t) { *this = t; };
    tree(tree && t) { *this = std::move(t); }
    tree(std::unique_ptr<node> && tree) : tree_(std::move(tree)) { }
    tree(unsigned depth) { }
    tree & operator= (const tree & t) { tree_ = std::move(t.tree_->clone()); }
    tree & operator= (tree && t) { tree_ = std::move(t.tree_); }
    node * operator-> () { return tree_.get(); }
    
    iterator this_iterator() { return iterator(*this); }
    iterator end() { return iterator(); }
    
    friend class node_non_terminal;
    friend tree random(unsigned depth);
    friend class tree_iterator;
};

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
    
    node_non_terminal() { };
    node_non_terminal(tree && left, tree && right) 
        : left_(std::move(left.tree_)), right_(std::move(right.tree_)) { }
    
    virtual node::value_type eval(const valuation & v) const = 0;
    bool is_terminal() const { return false; }
    virtual std::string operator_str() const = 0;
    std::ostream & print(std::ostream & out) const {
        return right_->print(left_->print(out << "(") << ")" << operator_str() << "(") << ")";
    };
    virtual std::unique_ptr<node> clone() const = 0;
    
    friend class tree_iterator;
};

class node_terminal : public node
{
public:
    enum class type {
        constant,
        variable,
    };
    
    virtual node::value_type eval(const valuation & v) const = 0;
    bool is_terminal() const { return true; }
    virtual std::ostream & print(std::ostream & out) const = 0;
    virtual std::unique_ptr<node> clone() const = 0;
};

template <node_non_terminal::type Type>
class non_terminal : public node_non_terminal
{
public:
    non_terminal(std::unique_ptr<node> && left, std::unique_ptr<node> && right) {
        node_non_terminal::left_ = std::move(left);
        node_non_terminal::right_ = std::move(right);
    }
    virtual node::value_type eval(const valuation & v) const;
    virtual std::string operator_str() const;
    virtual std::unique_ptr<node> clone() const;
};

template <> node::value_type non_terminal<node_non_terminal::type::addition>::eval(const valuation& v) const 
{ return node_non_terminal::left_->eval(v) + node_non_terminal::right_->eval(v); }
template <> node::value_type non_terminal<node_non_terminal::type::subtraction>::eval(const valuation& v) const 
{ return node_non_terminal::left_->eval(v) - node_non_terminal::right_->eval(v); }
template <> node::value_type non_terminal<node_non_terminal::type::multiplication>::eval(const valuation& v) const 
{ return node_non_terminal::left_->eval(v) * node_non_terminal::right_->eval(v); }
template <> node::value_type non_terminal<node_non_terminal::type::protected_division>::eval(const valuation& v) const 
{ auto t = node_non_terminal::right_->eval(v); t = t == 0 ? 1 : t; return node_non_terminal::left_->eval(v) / t; }

template <> std::string non_terminal<node_non_terminal::type::addition>::operator_str() const           { return "+"; }
template <> std::string non_terminal<node_non_terminal::type::subtraction>::operator_str() const        { return "-"; }
template <> std::string non_terminal<node_non_terminal::type::multiplication>::operator_str() const     { return "*"; }
template <> std::string non_terminal<node_non_terminal::type::protected_division>::operator_str() const { return "/"; }

template <> std::unique_ptr<node> non_terminal<node_non_terminal::type::addition>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::addition>(
        std::move(node_non_terminal::left_->clone()), std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}
template <> std::unique_ptr<node> non_terminal<node_non_terminal::type::subtraction>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::subtraction>(
        std::move(node_non_terminal::left_->clone()), std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}
template <> std::unique_ptr<node> non_terminal<node_non_terminal::type::multiplication>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::multiplication>(
        std::move(node_non_terminal::left_->clone()), std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}
template <> std::unique_ptr<node> non_terminal<node_non_terminal::type::protected_division>::clone() const {
    auto p = new non_terminal<node_non_terminal::type::protected_division>(
        std::move(node_non_terminal::left_->clone()), std::move(node_non_terminal::right_->clone()));
    return std::unique_ptr<node>((node *) p);
}

template <node_terminal::type Type>
class terminal : public node_terminal
{ /* should never be instantiated */ };

template <>
class terminal<node_terminal::type::constant> : public node_terminal
{
    node::value_type val_;
public:
    terminal<node_terminal::type::constant>(node::value_type val) : val_(val) { };
    virtual node::value_type eval(const valuation & v) const { return val_; };
    virtual std::ostream & print(std::ostream & out) const { return out << val_; };
    virtual std::unique_ptr<node> clone() const {
        auto p = new terminal<node_terminal::type::constant>(val_);
        return std::unique_ptr<node>((node *) p);
    };
};

template <>
class terminal<node_terminal::type::variable> : public node_terminal
{
    unsigned num_;
public:
    terminal<node_terminal::type::variable>(unsigned num) : num_(num) { };
    virtual node::value_type eval(const valuation & v) const { return v[num_]; }
    virtual std::ostream & print(std::ostream & out) const { return out << "x_" << num_; }
    virtual std::unique_ptr<node> clone() const {
        auto p = new terminal<node_terminal::type::variable>(num_);
        return std::unique_ptr<node>((node *) p);
    }
};

tree random(unsigned depth) {
    node * n = nullptr;
    if (depth) {
        tree left = random(depth - 1);
        tree right = random(depth - 1);
        switch (stochastic::get_max(3)) {
            case 0:
                n = (node *) new non_terminal<node_non_terminal::type::addition>(
                        std::move(left.tree_), std::move(right.tree_));
                break;
            case 1:
                n = (node *) new non_terminal<node_non_terminal::type::subtraction>(
                        std::move(left.tree_), std::move(right.tree_));
                break;
            case 2:
                n = (node *) new non_terminal<node_non_terminal::type::multiplication>(
                        std::move(left.tree_), std::move(right.tree_));
                break;
            case 3:
                n = (node *) new non_terminal<node_non_terminal::type::protected_division>(
                        std::move(left.tree_), std::move(right.tree_));
                break;
            default:
                throw "should never reach this";
                break;
        }
    } else {
        if (stochastic::get_bool()) {
            n = (node *) new terminal<node_terminal::type::constant>(
                    stochastic::get_minmax(
                            run_config::tree::min_value, 
                            run_config::tree::max_value)
                    );
        } else {
            n = (node *) new terminal<node_terminal::type::variable>(
                    stochastic::get_max(run_config::tree::num_variables - 1));
        }
    }
    
    // Return and transfer ownership
    return tree(std::unique_ptr<node>(n));
}

tree_iterator::tree_iterator(const tree & t) {
    tree_ = const_cast<tree *>(&t);
    node_ = t.tree_.get();
}

tree_iterator & tree_iterator::left() {
    if (node_ == nullptr && tree_ == nullptr)
        throw std::out_of_range("calling left() on end()");
    else if (node_->is_terminal()) {
        tree_ = nullptr;
        node_ = nullptr;
    } else {
        node_non_terminal * n = (node_non_terminal *) node_;
        node_ = (node *) (n->left_.get());
    }
}

tree_iterator & tree_iterator::right() {
    if (node_ == nullptr && tree_ == nullptr)
        throw std::out_of_range("calling right() on end()");
    else if (node_->is_terminal()) {
        tree_ = nullptr;
        node_ = nullptr;
    } else {
        node_non_terminal * n = (node_non_terminal *) node_;
        node_ = (node *) n->right_.get();
    }
}

bool tree_iterator::operator!= (const tree_iterator & t) {
    return tree_ != t.tree_ || node_ != t.node_;
}

node * tree_iterator::operator-> () { 
    return node_; 
}

tree tree_iterator::operator* () { 
    return tree(std::move(node_->clone())); 
}

#endif	/* NODE_H */

