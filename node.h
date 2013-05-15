/* 
 * File:   tree.h
 * Author: tomas789
 *
 * Created on May 9, 2013, 5:42 PM
 */

#ifndef NODE_H
#define	NODE_H

#include "compile_config.h"
#include "valuation.h"
#include "tree.h"

#include <memory>
#include <stdexcept>
#include <utility>

/**
 * Abstract class holding program tree structure.
 *
 * Every time you have pointer to this class, you do not own it. If you
 * have unique_ptr<node>, you own it.
 */
class node 
{
public:
    using value_type = compile_config::tree::value_type;
    
    /**
     * Evaluate this tree using supplied valuation
     */
    virtual value_type eval(const valuation & v) const = 0;
    
    /**
     * True if this is a leaf in tree false otherwise
     */
    virtual bool is_terminal() const = 0;
    
    /**
     * Print tree to stream.
     * Tree is printed as flat structure
     */
    virtual std::ostream & print(std::ostream & out) const = 0;
    
    /**
     * Make a copy of this tree
     */
    virtual std::unique_ptr<node> clone() const = 0;
};

/**
 * DFS Algorithm on subtree
 * Applies f to every node in DFS order
 */
template <class UnaryFunction>
UnaryFunction dfs(tree::iterator it, UnaryFunction f)  {
    if (it != tree::iterator()) {
        f(it);
        if (! it->is_terminal()) {
            dfs(it.left(), f);
            dfs(it.right(), f);
        }
    }
    return f;
}

/**
 * Generate random tree with supplied depth and every leaf at the same level.
 * 0 for just one terminal node
 */
tree random(unsigned depth);

void swap(tree::subtree_iterator &lhs, tree::subtree_iterator &rhs);


#endif	/* NODE_H */

