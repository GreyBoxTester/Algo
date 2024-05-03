#include <queue>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

struct Node
{
    std::vector<std::pair<i64, i64>> next;
    i64 d = std::numeric_limits<i64>::max();
    i64 p = -1;
    bool v = false;
};

std::vector<Node> nodes;

void djikstra(i64 s)
{
    std::priority_queue<std::pair<i64, i64>, std::vector<std::pair<i64, i64>>, std::greater<std::pair<i64, i64>>> q;
    q.push({ 0, s });
    nodes[s].d = 0;
    while (!q.empty())
    {
        auto [d, c] = q.top();
        q.pop();
        if (nodes[c].v) { continue; }
        nodes[c].v = true;
        for (auto [next, w] : nodes[c].next)
        {
            if (nodes[next].d <= nodes[c].d + w) { continue; }
            nodes[next].d = nodes[c].d + w;
            nodes[next].p = c;
            q.push({ nodes[c].d + w, next });
        }
    }
}

