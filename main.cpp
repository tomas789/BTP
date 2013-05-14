/* 
 * File:   main.cpp
 * Author: radovankrejci
 *
 * Created on 10. květen 2013, 10:44
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "node.h"
#include "genetic_operators.h"
#include "valuation.h"

int 
main(int argc, char * argv[]) {

    valuation v;
    tree t = random(8);
    auto rt = t.random_node();
    t->print(std::cout) << std::endl;
    rt->print(std::cout) << std::endl;
    std::cout << t->eval(v) << std::endl;
    //std::cout << stochastic::get_max(0) << std::endl;
    
    //dfs(*rt, [&](tree t) {
    //    t->print(std::cout) << std::endl;
    //});
    
    //rt->print(std::cout) << std::endl;
    //std::cout << t->eval(v) << std::endl;
    
    return 0;
}

