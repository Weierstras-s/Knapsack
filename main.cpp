#include "generator/test.h"
#include "solver/transferPath.h"

#include "utils/rand.h"

#include <iostream>
#include <chrono>

using std::cin;
using std::cout;

int main() {
    uint64_t seed = std::chrono::steady_clock::now().time_since_epoch().count();
    Random::Seed(seed);
    cout << "[seed: " << seed << "]\n\n";

    int num = 0;
    double rate = 1;
    for (int i = 1; i <= 1000000; ++i) {
        TestGen gen;
        auto inst = gen.Generate();
//        inst.Write(cout);

        TransferPathSolver sol;
        sol.Solve(inst);

        int res = inst.Validate();
        if (res == -1) exit(0);

        rate = std::min(rate, 1 - res * 1.0 / inst.NItem());
        num = std::max(num, res);
        if (rate < 0.7) {
            inst.Write(cout);
            return 0;
        }
        //if (i % 100 == 0) {
        cout << inst.NItem() << ' ' << res << "\n";
        //}
    }

    return 0;
}
