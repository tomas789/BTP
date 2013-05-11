/* 
 * File:   run_config.h
 * Author: radovankrejci
 *
 * Created on 10. květen 2013, 11:38
 */

#ifndef RUN_CONFIG_H
#define	RUN_CONFIG_H

#include "compile_config.h"

struct run_config 
{   
    struct tree 
    {
        static unsigned num_variables;
        static compile_config::tree::value_type min_value;
        static compile_config::tree::value_type max_value;
        static unsigned default_depth;
    };
    
    struct genetic_operators
    {
        static unsigned subtree_default_depth;
    };
};

#endif	/* RUN_CONFIG_H */

