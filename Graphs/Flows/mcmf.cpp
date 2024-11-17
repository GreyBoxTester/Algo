#include <cstdint>
#include <vector>
#include <queue>

using i64 = int64_t;

struct Edge
{
    i64 from = -1, to = -1, cap = 0, cost = 0;
};

struct Node
{
    std::vector<i64> next;
    i64 pot = 0, d = 0, par = -1;
};

i64 s = -1, t = -1;
std::vector<Node> nodes;
std::vector<Edge> edges;

void addEdge(i64 u, i64 v, i64 cap, i64 cost)
{
    edges.emplace_back(u, v, cap, cost);
    edges.emplace_back(v, u, 0, -cost);
    nodes[u].next.push_back(edges.size() - 2);
    nodes[v].next.push_back(edges.size() - 1);
}

bool djikstra()
{
    for (auto& node : nodes)
    {
        node.d = std::numeric_limits<i64>::max();
        node.par = -1;
    }

    std::priority_queue<std::pair<i64, i64>, std::vector<std::pair<i64, i64>>, std::greater<std::pair<i64, i64>>> q;
    q.push({ 0, s });
    nodes[s].d = 0;
    while (!q.empty())
    {
        auto [d, c] = q.top();
        q.pop();
        if (nodes[c].d != d) { continue; }
        for (auto ei : nodes[c].next)
        {
            auto& e = edges[ei];
            i64 w = nodes[e.from].pot + e.cost - nodes[e.to].pot;
            if (nodes[e.to].d <= nodes[c].d + w || e.cap == 0) { continue; }
            nodes[e.to].d = nodes[c].d + w;
            nodes[e.to].par = ei;
            q.push({ nodes[c].d + w, e.to });
        }
    }

    for (auto& node : nodes)
    {
        if (node.d == std::numeric_limits<i64>::max()) { continue; }
        node.d -= node.pot - nodes[s].pot;
    }
    for (auto& node : nodes)
    {
        if (node.d == std::numeric_limits<i64>::max()) { continue; }
        node.pot = node.d;
    }

    return nodes[t].d != std::numeric_limits<i64>::max();
}

std::pair<i64, i64> mcmf(i64 goal = std::numeric_limits<i64>::max())
{
    i64 flow = 0, minCost = 0;
    while (flow < goal && djikstra())
    {
        i64 delta = goal - flow;
        for (i64 v = t; v != s; v = edges[nodes[v].par].from)
        {
            delta = std::min(delta, edges[nodes[v].par].cap);
        }
        for (i64 v = t; v != s; v = edges[nodes[v].par].from)
        {
            auto& e = edges[nodes[v].par];
            auto& re = edges[nodes[v].par ^ 1];
            e.cap -= delta;
            re.cap += delta;
            minCost += e.cost * delta;
        }
        flow += delta;
    }
    return { flow, minCost };
}
