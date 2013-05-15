//
//  non_terminal.h
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#ifndef __BTP__non_terminal__
#define __BTP__non_terminal__

#include <iostream>

#include "node.h"
#include "node_non_terminal.h"

template <node_non_terminal::type Type>
class non_terminal : public node_non_terminal
{
public:
    non_terminal(std::unique_ptr<node> && left, std::unique_ptr<node> && right);
    virtual node::value_type eval(const valuation & v) const;
    virtual std::string operator_str() const;
    virtual std::unique_ptr<node> clone() const;
};

#endif /* defined(__BTP__non_terminal__) */
