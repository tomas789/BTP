//
//  population.h
//  BTP
//
//  Created by Tomas Krejci on 5/15/13.
//  Copyright (c) 2013 Tomas Krejci. All rights reserved.
//

#ifndef __BTP__population__
#define __BTP__population__

#include <iostream>
#include <vector>

template <class Individial>
class population : public std::vector<Individial>
{
public:
    using value_type = Individial;

    population(unsigned long size) {
        std::vector<Individial>::resize(size);
        std::generate(std::vector<Individial>::begin(), std::vector<Individial>::end(), [&] {
            return Individial::random();
        });
    }

    
};

template <class Individial>
std::ostream& operator << (std::ostream& out, const population<Individial> & p) {
    for (std::size_t i = 0; i < p.size(); ++i)
        out << i << " : " << p[i] << std::endl;
    return out;
}

#endif /* defined(__BTP__population__) */
