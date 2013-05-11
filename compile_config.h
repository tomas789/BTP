/* 
 * File:   compile_config.h
 * Author: radovankrejci
 *
 * Created on 10. květen 2013, 11:20
 */

#ifndef COMPILE_CONFIG_H
#define	COMPILE_CONFIG_H

#include <random>

namespace compile_config
{
    
    namespace stochastic 
    {
        using engine = std::mt19937;
    }
    
    namespace tree
    {
        using value_type = double;
    }
    
}

#endif	/* COMPILE_CONFIG_H */

