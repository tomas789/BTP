#include "run_config.h"

unsigned run_config::tree::num_variables = 3;
compile_config::tree::value_type run_config::tree::min_value = -10;
compile_config::tree::value_type run_config::tree::max_value = 10;
unsigned run_config::tree::default_depth = 3;
unsigned run_config::genetic_operators::subtree_default_depth = 8;