#include "transferPath.h"

#include <numeric>
#include <queue>
#include <cassert>
#include <map>


void TransferPathSolver::Insert(DiscInstance &inst, DiscItem &newItem) {
    int nItem = inst.NItem();
    bag.insert(newItem.id);

    // Replacement strategy. Higher => more likely to be removed
    std::vector<int> replacePrior(nItem);
    // The position an item can be placed at. -1 if not exists
    std::vector<int> validPos(nItem, -1);
    // The index of the item a position is occupied by
    std::vector<int> color(inst.length, -1);

    // Initialize 'replacePrior' and 'validPos'
    for (auto id: bag) {
        auto &item = inst.items[id];
        if (item.assigned == -1) continue;
        for (int i = 0; i < item.length; ++i) {
            color[i + item.assigned] = id;
        }
    }
    std::vector<int> extendDist(inst.length + 1);
    for (int i = inst.length; i >= 0; --i) {
        if (color[i] != -1) extendDist[i] = 0;
        else extendDist[i] = extendDist[i + 1] + 1;
    }
    for (auto id: bag) {
        auto &item = inst.items[id];
        replacePrior[id] = item.length; // remove longer items
        for (auto x: item.pos) {
            if (extendDist[x] < item.length) continue;
            replacePrior[id] = INT32_MAX;
            validPos[id] = x;
            break;
        }
    }

    // Build transfer graph
    std::vector<std::vector<int>> G(nItem);
    for (auto i: bag) {
        for (auto j: bag) {
            if (i == j) continue;
            // i -> j
            if (inst.items[i].length > inst.items[j].length) continue;
            for (auto x: inst.items[i].pos) {
                if (color[x] != j) continue;
                G[i].push_back(j);
                break;
            }
        }
    }

    // BFS
    std::vector<int> pre(nItem, -1), vis(nItem);
    std::queue<int> q;
    q.push(newItem.id), vis[newItem.id] = 1;
    int final = -1, maxPrior = -1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (replacePrior[u] > maxPrior) {
            final = u, maxPrior = replacePrior[u];
        }
        for (auto v: G[u]) {
            if (vis[v]) continue;
            vis[v] = 1, pre[v] = u;
            q.push(v);
        }
    }

    // Find transfer path
    for (int nxt = -1, u = final; u != -1; nxt = u, u = pre[u]) {
        if (nxt == -1) {
            inst.items[u].assigned = validPos[u];
            if (validPos[u] == -1) bag.erase(u);
        } else {
            for (auto x: inst.items[u].pos) {
                if (color[x] != nxt) continue;
                inst.items[u].assigned = x;
                break;
            }
        }
    }
}

void TransferPathSolver::Solve(DiscInstance &inst) {
    int nItem = inst.NItem();
    std::vector<int> order(nItem);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int l, int r) {
        return inst.items[l].length > inst.items[r].length;
    });

    for (auto id: order) {
        auto &item = inst.items[id];
        item.id = id;
        Insert(inst, item);
    }
}

