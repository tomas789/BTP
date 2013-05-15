//
//  node_terminal.h
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#ifndef __BTP__node_terminal__
#define __BTP__node_terminal__

#include <iostream>

#include "node.h"

class node_terminal : public node
{
public:
    enum class type {
        constant,
        variable,
    };
    
    virtual node::value_type eval(const valuation & v) const = 0;
    bool is_terminal() const;
    virtual std::ostream & print(std::ostream & out) const = 0;
    virtual std::unique_ptr<node> clone() const = 0;
};

#endif /* defined(__BTP__node_terminal__) */
