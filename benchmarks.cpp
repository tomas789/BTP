//
//  benchmarks.cpp
//  BTP
//
//  Created by Tomas Krejci on 5/14/13.
//  Copyright (c) 2013 Tomas Krejci. All rights reserved.
//

#include "benchmarks.h"
#include "node.h"

#include <chrono>
#include <vector>

namespace benchmarks {
    void random_tree(std::ostream & out) {
        out << "size,minimum,average,maximum" << std::endl;

        random(0);

        for (auto size = 0; size < 10; ++size) {
            std::vector<decltype(std::chrono::time_point<std::chrono::high_resolution_clock>() - std::chrono::time_point<std::chrono::high_resolution_clock>())> measurements;
            for (auto repeat = 0; repeat < 20; ++repeat) {
                auto start = std::chrono::high_resolution_clock::now();

                // BEGIN TEST
                random(size);
                // END TEST

                auto end = std::chrono::high_resolution_clock::now();
                measurements.push_back(end - start);
            }

            decltype(measurements)::value_type min, max, avg;
            min = measurements[0];
            std::for_each(measurements.begin(), measurements.end(), [&](const decltype(measurements)::value_type & i) {
                min = std::min(min, i);
                max = std::max(max, i);
                avg += i;
            });
            avg /= measurements.size();

            std::cout << size << "," << min.count() << "," << avg.count() << "," << max.count() << std::endl;
        }
    }
}