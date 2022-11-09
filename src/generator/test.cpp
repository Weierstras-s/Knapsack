#include "test.h"

#include "utils/rand.h"

#include <list>

std::vector<DiscItem> TestGen::Split() const {
    int len = (int)pLen.size();
    std::vector<double> p(len + 1);
    for (int i = 0; i < len; ++i) {
        p[i + 1] = p[i] + pLen[i] * (1 << i);
    }
    for (int i = 0; i < len; ++i) p[i] /= p[i + 1];

    std::function<std::list<int>(int)> dfs = [&](int n) {
        std::list<int> ret;
        double pSplit = n >= len ? 1 : p[n];
        if (Random::Next(0.0, 1.0) < pSplit) {
            ret = dfs(n - 1);
            auto r = dfs(n - 1);
            ret.insert(ret.end(), r.begin(), r.end());
        } else {
            ret.push_back(1 << n);
        }
        return ret;
    };

    auto split = dfs(lgLen);
    std::vector<DiscItem> ret;
    int pos = 0;
    for (auto l: split) {
        ret.emplace_back(l);
        ret.back().pos.emplace(pos);
        pos += l;
    }
    return ret;
}

std::vector<DiscItem> TestGen::GenItems() const {
    std::vector<DiscItem> ret = Split();
    for (auto &item: ret) {
        int len = std::__lg(item.length);
        for (int num = cLen[len] - 1; num > 0; --num) {
            int x = Random::Next(0, (1 << (lgLen - len)) - 1);
            item.pos.insert(x << len);
        }
    }
    return ret;
}

DiscInstance TestGen::Generate() const {
    DiscInstance ret;
    ret.length = 1 << lgLen;
    ret.items = GenItems();
    return ret;
}
