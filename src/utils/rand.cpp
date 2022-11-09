#include "rand.h"


namespace Random {
    std::mt19937_64 &GetEngine() {
        static std::mt19937_64 rnd; // NOLINT(cert-msc51-cpp)
        return rnd;
    }

    void Seed(uint64_t seed) {
        GetEngine().seed(seed);
    }

    int Next(int l, int r) {
        return std::uniform_int_distribution<int>(l, r)(GetEngine());
    }
    long long Next(long long l, long long r) {
        return std::uniform_int_distribution<long long>(l, r)(GetEngine());
    }
    double Next(double l, double r) {
        return std::uniform_real_distribution<double>(l, r)(GetEngine());
    }

    int Choose(const std::vector<double> &p) {
        double sum = std::accumulate(p.begin(), p.end(), 0.0);
        int ret = 0;
        double x = sum * Next(0.0, 1.0);
        while (x > 0 && ret < p.size()) {
            x -= p[ret], ++ret;
        }
        return ret - 1;
    }
}
