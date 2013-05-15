//
//  terminal.h
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#ifndef __BTP__terminal__
#define __BTP__terminal__

#include <iostream>

#include "node_terminal.h"

template <node_terminal::type Type>
class terminal : public node_terminal
{ /* should never be instantiated */ };

template <>
class terminal<node_terminal::type::constant> : public node_terminal
{
    node::value_type val_;
public:
    terminal<node_terminal::type::constant>(node::value_type val);
    virtual node::value_type eval(const valuation & v) const;
    virtual std::ostream & print(std::ostream & out) const;
    virtual std::unique_ptr<node> clone() const;
};

template <>
class terminal<node_terminal::type::variable> : public node_terminal
{
    unsigned num_;
public:
    terminal<node_terminal::type::variable>(unsigned num);
    virtual node::value_type eval(const valuation & v) const;
    virtual std::ostream & print(std::ostream & out) const;
    virtual std::unique_ptr<node> clone() const;
};

#endif /* defined(__BTP__terminal__) */
