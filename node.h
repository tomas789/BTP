/* 
 * File:   tree.h
 * Author: tomas789
 *
 * Created on May 9, 2013, 5:42 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <ostream>
#include <memory>

#include "compile_config.h"
#include "run_config.h"
#include "stochastic.h"
#include "valuation.h"

enum class type {
    addition, // non-terminal
    subtraction, // non-terminal
    multiplication, // non-terminal
    protected_division, // non-terminal
    constant, // terminal
    variable // terminal
};

class node 
{
    friend class genetic_operators_helper;
public:
    virtual double eval(const valuation &) const = 0;
    virtual bool is_terminal() const = 0;
    virtual bool is_const() const = 0;
    virtual std::ostream & print(std::ostream &) const = 0;
};

template <type T>
class node_type : public node 
{
    std::unique_ptr<node> left_ = nullptr;
    std::unique_ptr<node> right_ = nullptr;
    static const char op;
public:
    node_type(std::unique_ptr<node> && left, std::unique_ptr<node> && right) 
        : left_(std::move(left)), right_(std::move(right)) { };
    virtual double eval(const valuation &) const;
    virtual bool is_terminal() const { return false; };
    virtual bool is_const() const {
        return left_->is_const() && right_->is_const();
    };
    virtual std::ostream & print(std::ostream & out) const {
        return out << "(" << left_.get() << op << right_.get() << ")";
    };
};

/* eval function specialization */
template <> double node_type<type::addition>::eval(const valuation & v) const
{ return left_->eval(v) + right_->eval(v); }
template <> double node_type<type::subtraction>::eval(const valuation & v) const
{ return left_->eval(v) - right_->eval(v); }
template <> double node_type<type::multiplication>::eval(const valuation & v) const
{ return left_->eval(v) * right_->eval(v); }
template <> double node_type<type::protected_division>::eval(const valuation & v) const
{ auto d = right_->eval(v); return d == 0 ? left_->eval(v) : left_->eval(v) / d; }

/* op function specialization */
template <> const char node_type<type::addition>::op = '+';
template <> const char node_type<type::subtraction>::op = '/';
template <> const char node_type<type::multiplication>::op = '*';
template <> const char node_type<type::protected_division>::op = '/';


template <>
class node_type<type::constant> : public node
{
    const compile_config::tree::value_type val_ = 0;
public:
    node_type(compile_config::tree::value_type val) : val_(val) { };
    virtual double eval(const valuation & v) const { return val_; };
    virtual bool is_terminal() const { return true; };
    virtual bool is_const() const { return true; };
    virtual std::ostream & print(std::ostream & out) const {
        return val_ < 0 ? out << "(" << val_ << ")" : out << val_;
    }
};

template <>
class node_type<type::variable> : public node
{
    std::size_t num_ = 0;
public:
    node_type(std::size_t num) : num_(num) { };
    virtual double eval(const valuation & v) const { return v[num_]; };
    virtual bool is_terminal() const { return true; };
    virtual bool is_const() const { return false; };
    virtual std::ostream & print(std::ostream & out) const {
        return out << "x_" << num_;
    }
};

std::ostream & operator <<(std::ostream & out, node * n) {
    return n->print(out);
}

std::unique_ptr<node> random_tree(
        unsigned depth = run_config::tree::default_depth)
{
    node * result;
    
    if (depth) {
        // Generate non-terminals
        std::unique_ptr<node> left = random_tree(depth - 1);
        std::unique_ptr<node> right = random_tree(depth - 1);
        
        switch (stochastic::get_minmax(1, 4)) {
        case 1:
            result = new node_type<type::addition>(
                    std::move(left), 
                    std::move(right));
            break;
        case 2:
            result = new node_type<type::subtraction>(
                    std::move(left), 
                    std::move(right));
            break;
        case 3:
            result = new node_type<type::multiplication>(
                    std::move(left), 
                    std::move(right));
            break;
        case 4:
            result = new node_type<type::protected_division>(
                    std::move(left), 
                    std::move(right));
            break;
        }
        
    } else {
        // Generate terminals
        
        switch (stochastic::get_minmax(1, 2)) {
        case 1:
            result = new node_type<type::variable>(
                    stochastic::get_minmax(
                        decltype(run_config::tree::num_variables)(1), 
                        run_config::tree::num_variables
                    ));
            break;
        case 2:
            result = new node_type<type::constant>(stochastic::get_minmax(
                    run_config::tree::min_value, 
                    run_config::tree::max_value));
            break;
        }
    }
    
    return std::unique_ptr<node>(result);
}


#endif	/* NODE_H */

