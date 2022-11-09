#pragma once

#include "interval.h"

#include <iostream>
#include <vector>
#include <set>

class Item {
public:
    int id = -1;
    int length = 0;

    /// Assigned position. -1 if not assigned.
    int assigned = -1;

    Item() = default;
    explicit Item(int length) : length(length) {}

    /// @return Returns true if assigned.
    bool IsAssigned() const { return assigned != -1; }

    /// @return Returns true if not assigned or the assignment is valid.
    virtual bool Validate() const = 0;

    virtual void Read(std::istream &is) = 0;
    virtual void Write(std::ostream &os) const = 0;
};

/// Item with discrete available positions.
class DiscItem : public Item {
public:
    std::set<int> pos;

    DiscItem() = default;
    explicit DiscItem(int length) : Item(length) {}
    DiscItem(int length, std::set<int> &pos)
            : Item(length), pos(pos) {}

    std::vector<int> GetPos() const {
        std::vector<int> ret;
        for (auto x: pos) ret.emplace_back(x);
        return ret;
    }
    std::vector<Interval> GetIntervals() const {
        std::vector<Interval> ret;
        for (auto x: pos) ret.emplace_back(x, x + length);
        return ret;
    }

    bool Validate() const override {
        return pos.count(assigned);
    }
    void Read(std::istream &is) override {
        int cnt;
        is >> length >> cnt;
        for (int j = 0, x; j < cnt; ++j) is >> x, pos.insert(x);
    }
    void Write(std::ostream &os) const override {
        os << length << " " << pos.size();
        for (auto &x: pos) os << " " << x;
    }
};

/// Item with continuous available positions.
/// [x, x + length) where x in [left, right)
class ContItem : public Item {
public:
    Interval pos;

    ContItem() : Item() {};
    explicit ContItem(int length) : Item(length) {}
    ContItem(int length, const Interval &pos)
            : Item(length), pos(pos) {}
    ContItem(int length, int left, int right)
            : Item(length), pos(left, right) {}

    bool Validate() const override {
        return pos.IsContain(assigned);
    }
    void Read(std::istream &is) override {
        int left, right;
        is >> length >> left >> right;
        pos.Set(left, right);
    }
    void Write(std::ostream &os) const override {
        os << length << " " << pos.Left() << " " << pos.Right();
    }
};
