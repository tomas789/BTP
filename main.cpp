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

int 
main(int argc, char * argv[]) {

    valuation v;
    
    std::vector<std::unique_ptr<node>> p(5);
    std::generate(p.begin(), p.end(), std::bind(random_tree, 20));
        
    std::cout << " ### Evaluation ###" << std::endl;
    for (auto & t : p) std::cout << t->eval(v) << std::endl;
    
    return 0;
}

