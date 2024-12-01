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
    bool v = false;
};

i64 s = -1, t = -1;
bool neg = false;
std::vector<Node> nodes;
std::vector<Edge> edges;

void addEdge(i64 u, i64 v, i64 cap, i64 cost)
{
    neg |= (cost < 0);
    edges.emplace_back(u, v, cap, cost);
    edges.emplace_back(v, u, 0, -cost);
    nodes[u].next.push_back(edges.size() - 2);
    nodes[v].next.push_back(edges.size() - 1);
}

void fordBellman()
{
    for (auto& node : nodes) { node.pot = std::numeric_limits<i64>::max(); }

    nodes[s].pot = 0;
    for (i64 i = 1; i < nodes.size(); i++)
    {
        for (auto& e : edges)
        {
            if (nodes[e.from].pot + e.cost >= nodes[e.to].pot || e.cap == 0) { continue; }
            nodes[e.to].pot = nodes[e.from].pot + e.cost;
        }
    }
}

bool djikstra()
{
    for (auto& node : nodes)
    {
        node.d = std::numeric_limits<i64>::max();
        node.par = -1;
        node.v = false;
    }

    nodes[s].d = 0;
    while (true)
    {
        i64 v = -1;
        for (i64 i = 0; i < nodes.size(); i++)
        {
            if (!nodes[i].v && (v == -1 || nodes[i].d < nodes[v].d)) { v = i; }
        }

        if (v == -1 || nodes[v].d == std::numeric_limits<i64>::max()) { break; }

        nodes[v].v = true;
        for (i64 ei : nodes[v].next)
        {
            auto& e = edges[ei];
            i64 w = nodes[e.from].pot + e.cost - nodes[e.to].pot;
            if (nodes[e.to].v || nodes[e.to].d <= nodes[v].d + w || e.cap == 0) { continue; }
            nodes[e.to].d = nodes[v].d + w;
            nodes[e.to].par = ei;
        }
    }

    for (auto& node : nodes)
    {
        if (node.d == std::numeric_limits<i64>::max()) { continue; }
        node.d += node.pot - nodes[s].pot;
    }
    for (auto& node : nodes)
    {
        if (node.d == std::numeric_limits<i64>::max()) { continue; }
        node.pot = node.d;
    }

    return nodes[t].d != std::numeric_limits<i64>::max();
}

std::pair<i64, i64> mcmf()
{
    if (neg) { fordBellman(); }

    i64 flow = 0;
    i64 minCost = 0;
    while (djikstra())
    {
        i64 delta = std::numeric_limits<i64>::max();
        i64 cnt = 0;
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
            minCost += e.cost * (i64)delta;
        }
        flow += delta;
    }
    return { minCost, flow };
}
