/* 
 * File:   valuation.h
 * Author: tomas789
 *
 * Created on May 11, 2013, 3:05 PM
 */

#ifndef VALUATION_H
#define	VALUATION_H

#include "compile_config.h"
#include "run_config.h"

class valuation 
{
    std::size_t tick_;
public:
    valuation();
    void step();
    compile_config::tree::value_type operator [](std::size_t i) const;
};

#endif	/* VALUATION_H */

