# Knapsack
## Transfer Path
```
Insert(item):
    // replacePrior[n]: 被替换的优先级
    // validPos[n]: 物品能放置的位置之一，不存在为 -1
    遍历已经放置的物品 (u, v):
        如果 u 的长度 <= v 的长度,
        并且 u 的可选位置与 v 当前位置重叠:
            G.AddEdge(u, v)
    path = G 从 item 开始的一条路径,
           最大化终点的 replacePrior 值
    遍历 u ∈ path:
        如果 u 是路径终点:
            u.assigned = validPos[u]
        否则假设 u 在路径上的下一个点是 v:
            u.assigned = u.pos 中与 v 重叠的位置
```
