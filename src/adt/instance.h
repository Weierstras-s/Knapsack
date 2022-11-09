#pragma once

#include "item.h"

#include <map>

template<class TItem>
class Instance {
public:
    int length = 0;
    std::vector<TItem> items;

    /// @return Number of items in total.
    int NItem() const { return (int)items.size(); }

    /// @return Number of items not assigned, -1 if not valid.
    int Validate() const {
        int ret = 0;
        std::map<int, int> cnt;
        for (auto &item: items) {
            if (!item.IsAssigned()) {
                ++ret;
                continue;
            }
            if (!item.Validate()) return item.Write(std::cout), std::cout << "\n" << item.assigned << "\n", -1;
            ++cnt[item.assigned];
            --cnt[item.assigned + item.length];
        }
        int sum = 0;
        for (auto[pos, x]: cnt) {
            sum += x;
            if (sum > 1) return -1;
        }
        return ret;
    }

    void Read(std::istream &is) {
        int cnt;
        is >> cnt >> length, items.resize(cnt);
        for (auto &x: items) x.Read(is);
    }
    void Write(std::ostream &os) const {
        os << length << " " << items.size() << "\n";
        for (auto &x: items) x.Write(os), os << "\n";
    }
};

typedef Instance<DiscItem> DiscInstance;
typedef Instance<ContItem> ContInstance;
