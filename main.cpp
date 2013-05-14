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
#include <chrono>

#include "benchmarks.h"

int 
main(int argc, char * argv[]) {

    benchmarks::random_tree(std::cout);
    
    return 0;
}

