#include <vector>
#include <queue>
#include <cstdint>

using i64 = int64_t;

struct Edge
{
    i64 next = -1, f = 0, cap = 0;
};

struct Node
{
    std::vector<i64> next;
    i64 d = -1;
    i64 p = 0;
    bool bl = false;
};

std::vector<Edge> edges;
std::vector<Node> nodes;
i64 s, t;

void addEdge(i64 u, i64 v, i64 cap)
{
    edges.push_back({ v, 0, cap });
    edges.push_back({ u, 0, 0 });
    nodes[u].next.push_back(edges.size() - 2);
    nodes[v].next.push_back(edges.size() - 1);
}

bool bfs()
{
    std::queue<std::pair<i64, i64>> q;
    q.push({ s, 0 });
    while (!q.empty())
    {
        auto [v, d] = q.front(); q.pop();
        if (nodes[v].d != -1) { continue; }
        nodes[v].d = d;
        for (auto next : nodes[v].next)
        {
            if (edges[next].f == edges[next].cap) { continue; }
            q.push({ edges[next].next, d + 1 });
        }
    }

    return nodes[t].d != -1;
}

i64 dfs(i64 v, i64 fl)
{
    if (v == t || fl == 0) { return fl; }
    for (i64& i = nodes[v].p; i < nodes[v].next.size(); i++)
    {
        i64 ei = nodes[v].next[i];
        auto& e = edges[ei];
        if (nodes[e.next].d != nodes[v].d + 1) { continue; }

        i64 nf = dfs(e.next, std::min(fl, e.cap - e.f));
        if (!nf) { continue; }
        e.f += nf;
        edges[ei ^ 1].f -= nf;
        return nf;
    }
    return 0;
}

i64 dinic()
{
    for (auto& e : edges) { e.f = 0; }

    i64 f = 0;
    while (true)
    {
        for (auto& nd : nodes) { nd.d = -1; nd.p = 0; }
        if (!bfs()) { break; }
        i64 fl;
        while (fl = dfs(s, std::numeric_limits<i64>::max()))
        {
            f += fl;
        }
    }

    return f;
}
