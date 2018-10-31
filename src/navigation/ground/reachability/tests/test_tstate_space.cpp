#include <iostream>

#include "reachability/details/tstate_space.hpp"

using namespace librav;

int main()
{
    TStateSpace tspace(0, 50, 0, 20);
    tspace.DiscretizeSpace(5, 2);

    auto cell = tspace.GetStateCell(4, 1);
    cell->PrintInfo();

    auto samples = cell->GetUniformSamples(4, 4);
    for (auto &smp : samples)
        std::cout << smp << std::endl;
    std::cout << "sample size: " << samples.size() << std::endl;

    return 0;
}