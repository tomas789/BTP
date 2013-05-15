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
#include "valuation.h"
#include "stochastic.h"

int 
main(int argc, char * argv[]) {

    valuation v;

    std::vector<tree> t(20);
    std::generate(t.begin(), t.end(), []() { return random(3); });

    std::cout << " ### GENERATED ###" << std::endl;
    std::for_each(t.begin(), t.end(), [&](tree & tmp) {
        std::cout << tmp->eval(v) << " : ";
        tmp->print(std::cout) << std::endl;
    });

    //t1.random_subtree().first->print(std::cout) << std::endl;

    for (int i = 0; i < 100; ++i) {
        tree::subtree_iterator i1 = t[stochastic::get_max(t.size() - 1)].random_subtree();
        tree::subtree_iterator i2 = t[stochastic::get_max(t.size() - 1)].random_subtree();
        swap(i1, i2);
    }

    std::cout << std::endl << " ### CROSSED ###" << std::endl;
    std::for_each(t.begin(), t.end(), [&](tree & tmp) {
        std::cout << tmp->eval(v) << " : ";
        tmp->print(std::cout) << std::endl;
    });

    
    return 0;
}

