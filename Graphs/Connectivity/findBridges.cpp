#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <limits>
#include <numeric>
#include <cstdint>
#include <cmath>
#include <random>
#include <map>
#include <bit>
#include <deque>

namespace rn = std::ranges;
namespace rv = std::ranges::views;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

struct Edge
{
    i64 a, b;
    i64 next(i64 u)
    {
        if (u == a) { return b; }
        return a;
    }
};

struct Node
{
    std::vector<i64> edges;
    i64 d = -1, md = -1;
};

std::vector<Edge> edges;
std::vector<Node> nodes;

i64 dfs(i64 i, i64 pe, i64 d)
{
    if (nodes[i].md != -1) { return nodes[i].d; }
    nodes[i].d = d;
    nodes[i].md = d;
    for (auto e : nodes[i].edges)
    {
        if (e == pe) { continue; }
        nodes[i].md = std::min(nodes[i].md, dfs(edges[e].next(i), e, d + 1));
    }
    return nodes[i].md;
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);

    i64 n, m; std::cin >> n >> m;
    nodes.resize(n);
    edges.resize(m);
    i64 ind = 0;
    for (auto& e : edges)
    {
        std::cin >> e.a >> e.b; e.a--; e.b--;
        nodes[e.a].edges.push_back(ind);
        nodes[e.b].edges.push_back(ind);
        ind++;
    }

    for (i64 i = 0; i < n; i++)
    {
        dfs(i, -1, 0);
    }

    std::vector<i64> ans;
    for (i64 i = 0; i < m; i++)
    {
        auto [a, b] = edges[i];
        if (nodes[a].d > nodes[b].d) { std::swap(a, b); }
        if (nodes[a].d < nodes[b].md) { ans.push_back(i + 1); }
    }

    std::cout << ans.size() << '\n';
    for (auto& ai : ans) { std::cout << ai << ' '; }
}
