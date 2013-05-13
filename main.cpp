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
    
    std::vector<tree> p(1);
    for (auto & t : p) t = random(0);
    tree::iterator it = p[0].this_iterator();
    it.right();
    it->print(std::cout) << std::endl;
    
    std::cout << p[0]->eval(valuation()) << std::endl;
    
    p[0]->print(std::cout ) << std::endl;
    
    //p[0]->print(std::cout);
    
    return 0;
}

