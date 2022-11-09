#pragma once

#include "adt/instance.h"

template<class TItem>
class Solver {
public:
    virtual void Solve(Instance<TItem> &inst) = 0;
};
