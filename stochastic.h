/* 
 * File:   random.h
 * Author: tomas789
 *
 * Created on May 9, 2013, 6:54 PM
 */

#ifndef RANDOM_H
#define	RANDOM_H

#include "compile_config.h"
#include "run_config.h"

#include <random>
#include <chrono>

/**
 * Encapsulates random number generating functions
 */
namespace stochastic
{
    
    /**
     * Random number engine
     * 
     * TODO : Implement this as functor
     */
    compile_config::stochastic::engine engine(
        std::chrono::system_clock::now().time_since_epoch().count());
    
    /**
     * Generate (pseudo-)random number in range [min, max]
     * 
     * Floating point version
     * 
     * @param min
     * @param max
     * @return 
     */
    template<class T>
    typename std::enable_if<
            std::is_floating_point<T>::value, 
            T
        >::type get_minmax(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(stochastic::engine);
    }

    /**
     * Generate (pseudo-)random number in range [min, max]
     * 
     * Discrete version
     * 
     * @param min
     * @param max
     * @return 
     */
    template<class T>
    typename std::enable_if<
            std::is_integral<T>::value, 
            T
        >::type get_minmax(T min, T max) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(stochastic::engine);
    }
    
    /**
     * Generate (pseudo-)random number of type T in range [0, max]
     * 
     * @param max
     * @return 
     */
    template <class T>
    T get_max(T max) {
        return get_minmax(T(), max);
    }
    
    /**
     * Generate (pseudo-)random boolean 
     * @return 
     */
    bool get_bool() {
        return get_minmax(0, 1);
    }
}


#endif	/* RANDOM_H */

