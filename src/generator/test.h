#pragma once

#include "base.h"

class TestGen : public Generator<DiscItem> {
    std::vector<DiscItem> Split() const;
    std::vector<DiscItem> GenItems() const;

public:

    int lgLen = 10; // 1024
    const int C = 8;

    /// Expected proportion for items of length 2^i.
    std::vector<double> pLen{1, 1, 1, 1, 1, 1};

    /// Maximum number of choices for items of length 2^i.
    std::vector<int> cLen{C, C, C, C, C, C};

    DiscInstance Generate() const override;
};
