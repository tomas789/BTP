#include "valuation.h"

valuation::valuation() {
    tick_ = run_config::tree::num_variables;
}

void valuation::step() {
    ++tick_;
}

compile_config::tree::value_type valuation::operator [](std::size_t i) const {
    return tick_ - run_config::tree::num_variables + i;
}