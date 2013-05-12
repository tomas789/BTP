/* 
 * File:   main.cpp
 * Author: radovankrejci
 *
 * Created on 10. květen 2013, 10:44
 */

#include <iostream>
#include <vector>
#include <algorithm>

#include "node.h"
#include "genetic_operators.h"

int 
main(int argc, char * argv[]) {

    valuation v;
    
    std::vector<std::unique_ptr<node>> p(1);
    std::generate(p.begin(), p.end(), std::bind(random_tree, 3));
    
    auto t = std::move(p[0]);
    t->print(std::cout) << std::endl;
    auto t2 = mutation_single_point(std::move(t));
    t2->print(std::cout) << std::endl;
    
    return 0;
}

