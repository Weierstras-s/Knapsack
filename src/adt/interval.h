#pragma once

#include <algorithm>

// [left, right)
class Interval {
    int left = 0;
    int right = 0;

public:
    Interval() = default;
    Interval(int l, int r) { Set(l, r); }

    void Set(int l, int r) {
        if (l > r) l = r;
        left = l, right = r;
    }
    int Left() const { return left; }
    int Right() const { return right; }
    int Length() const { return right - left; }
    bool Empty() const { return left >= right; }
    std::pair<int, int> ToPair() const { return {left, right}; }

    Interval Intersect(const Interval &other) const {
        int l = std::max(left, other.left);
        int r = std::min(right, other.right);
        return {l, r};
    }
    bool IsIntersect(const Interval &other) const {
        return !Intersect(other).Empty();
    }
    bool IsContain(const Interval &other) const {
        return left <= other.left && other.right <= right;
    }
    bool IsContain(int x) const {
        return left <= x && x <= right;
    }

    Interval operator+(const Interval &other) const {
        return {left + other.left, right + other.right};
    }
    bool operator<(const Interval &other) const {
        return ToPair() < other.ToPair();
    }
};
