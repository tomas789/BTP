//
//  stochastic.cpp
//  BTP
//
//  Created by Tomáš Krejčí on 5/15/13.
//  Copyright (c) 2013 Tomáš Krejčí. All rights reserved.
//

#include "stochastic.h"

namespace stochastic {
    
    bool get_bool() {
        return get_minmax(0, 1);
    }
    
}
