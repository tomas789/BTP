/* 
 * File:   genetic_operators.h
 * Author: tomas789
 *
 * Created on May 11, 2013, 3:43 PM
 */

#ifndef GENETIC_OPERATORS_H
#define	GENETIC_OPERATORS_H

#include "node.h"

#include <vector>

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
        if (!v[i].second->is_terminal()) {
            v.emplace_back(i, side::left, v[i].second->left_->get());
            v.emplace_back(i, side::right, v[i].second->right_->get());
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
            new_subtree = random_tree(0);
        } else {
            new_subtree = random_tree(1);
            new_subtree->left_ = std::move(std::get<2>(selected_node)->left_);
            new_subtree->right_ = std::move(std::get<2>(selected_node)->right_);
        }
        
        switch(std::get<1>(selected_node)) {
            case side::root:
                return new_subtree;
                break;
            case side::left:
                auto prodecessor = v[std::get<0>(selected_node)];
                std::get<2>(predecessor)->left_ = std::unique_ptr(new_subtree);
                break;
            case side::right:
                auto prodecessor = v[std::get<0>(selected_node)];
                std::get<2>(predecessor)->right_ = std::unique_ptr(new_subtree);
                break;
        }
        
        return n;
    }
    
    static node * mutation_subtree(node * n) {
        auto v = make_flat(n);
        auto point = stochastic::get_max(v.size() - 1);
        auto selected_node = v[point];
        
        node * new_subtree = random_tree(
                run_config::genetic_operators::subtree_default_depth);
        std::unique_ptr<node> t(new_subtree);
        
        if (stochastic::get_bool()) 
            std::get<2>(selected_node)->left_ = std::move(t);
        else
            std::get<2>(selected_node)->right_ = std::move(t);
        
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

#endif	/* GENETIC_OPERATORS_H */

