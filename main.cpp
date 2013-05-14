/* 
 * File:   main.cpp
 * Author: radovankrejci
 *
 * Created on 10. květen 2013, 10:44
 */

#include <iostream>

#include "node.h"

int 
main(int argc, char * argv[]) {

    auto t1 = random(3);
    auto t2 = random(3);

    t1->print(std::cout) << std::endl;
    t2->print(std::cout) << std::endl;

    //t1.random_subtree().first->print(std::cout) << std::endl;

    tree::subtree_iterator i1 = t1.random_subtree();
    tree::subtree_iterator i2 = t2.random_subtree();

    swap(i1, i2);

    t1->print(std::cout) << std::endl;
    t2->print(std::cout) << std::endl;

    
    return 0;
}

