#pragma once

#include "base.h"

class TransferPathSolver : public Solver<DiscItem> {
    // Indices of items having been assigned.
    std::set<int> bag;

    void Insert(DiscInstance &inst, DiscItem &newItem);

public:
    void Solve(DiscInstance &inst) override;
};

