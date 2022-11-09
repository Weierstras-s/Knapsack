#pragma once

#include <random>

namespace Random {
    std::mt19937_64 &GetEngine();

    void Seed(uint64_t seed);

    int Next(int l, int r);
    long long Next(long long l, long long r);
    double Next(double l, double r);

    int Choose(const std::vector<double> &p);
}
