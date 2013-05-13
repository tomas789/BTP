/* 
 * File:   genetic_operators.h
 * Author: tomas789
 *
 * Created on May 11, 2013, 3:43 PM
 */

#ifndef GENETIC_OPERATORS_H
#define	GENETIC_OPERATORS_H

#if 0

#include "node.h"

#include <vector>
#include <tuple>

/**
 * Helper for genentic operators. Every operator should access node's private
 * properties and function only through this class which is friend of node 
 * class.
 */
class genetic_operators_helper
{
public:
    enum class side { left, right, root };
    using node_container = std::vector<std::tuple<std::size_t, side, node *>>;
    
private:
    static void make_flat_helper(std::size_t i, node_container & v) {
        if (!std::get<2>(v[i])->is_terminal()) {
            v.emplace_back(i, side::left, std::get<2>(v[i])->left_subtree().get());
            v.emplace_back(i, side::right, std::get<2>(v[i])->right_subtree().get());
            auto size = v.size();
            make_flat_helper(size - 2, v);
            make_flat_helper(size - 1, v);
        }
    }
    
public:
    static node_container make_flat(node * n) {
        node_container v;
        v.emplace_back(0, side::root, n);
        make_flat_helper(0, v);
        return std::move(v);
    }
    
    static node * mutation_single_point(node * n) {
        auto v = make_flat(n);
        auto point = stochastic::get_max(v.size() - 1);
        auto selected_node = v[point];

        node * new_subtree = nullptr;

        if (std::get<2>(selected_node)->is_terminal()) {
            new_subtree = random_tree(0).get();
        } else {
            new_subtree = random_tree(1).get();
            new_subtree->left_subtree() = std::get<2>(selected_node)->left_subtree();
            new_subtree->right_subtree() = std::get<2>(selected_node)->right_subtree();
        }

        auto predecessor = v[std::get<0>(selected_node)];
        switch(std::get<1>(selected_node)) {
            case side::root:
                return new_subtree;
                break;
            case side::left:
                std::get<2>(predecessor)->left_subtree() = std::unique_ptr<node>(new_subtree);
                break;
            case side::right:
                std::get<2>(predecessor)->right_subtree() = std::unique_ptr<node>(new_subtree);
                break;
        }

        return n;
    }
    
    static node * mutation_subtree(node * n) {
        auto v = make_flat(n);
        auto point = stochastic::get_max(v.size() - 1);
        auto selected_node = v[point];

        auto new_subtree = random_tree(
                run_config::genetic_operators::subtree_default_depth);

        if (stochastic::get_bool()) 
            std::get<2>(selected_node)->left_subtree() = std::move(new_subtree);
        else
            std::get<2>(selected_node)->right_subtree() = std::move(new_subtree);

        return n;
    }
};

/**
 * Replace single node with random node preserving node's terminality
 * 
 * @param n
 * @return 
 */
std::unique_ptr<node> mutation_single_point(std::unique_ptr<node> && n) {
    node * t = genetic_operators_helper::mutation_single_point(n.get());
    return std::unique_ptr<node>(t);
}
/**
 * Replace rendom selected node with random subtree avoiding headless chicken.
 * 
 * @param n
 * @return 
 */
std::unique_ptr<node> mutation_subtree(std::unique_ptr<node> && n) {
    node * t = genetic_operators_helper::mutation_subtree(n.get());
    return std::unique_ptr<node>(t);
}

#endif

#endif	/* GENETIC_OPERATORS_H */

