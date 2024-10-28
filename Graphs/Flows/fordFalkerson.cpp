#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <limits>
#include <numeric>
#include <numbers>
#include <cmath>
#include <queue>

namespace rn = std::ranges;
namespace rv = std::ranges::views;

using i64 = int64_t;
using u64 = uint64_t;   

struct Node
{
    std::vector<i64> edges;
    i64 v = 0;
};

struct Edge
{
    i64 next;
    i64 cap;
    i64 f;
};

std::vector<Edge> edges;
std::vector<Node> nodes;
i64 iter = 1;
i64 end;

i64 dfs(i64 i, i64 f)
{
    if (i == end) return f;

    nodes[i].v = iter;
    for (auto ei : nodes[i].edges)
    {
        auto& e = edges[ei];
        if (nodes[e.next].v != iter && e.f < e.cap)
        {
            i64 delta = dfs(e.next, std::min(f, e.cap - e.f));
            if (delta > 0) {
                e.f += delta;
                edges[ei ^ 1].f -= delta;
                return delta;
            }
        }
    }
    return 0;
}

i64 ff(i64 s, i64 e)
{
    end = e;
    for (auto& e : edges) { e.f = 0; }

    i64 ans = 0;
    i64 x = 0;
    while (x = dfs(s, std::numeric_limits<i64>::max()))
    {
        ans += x;
        iter++;
    }
    iter++;
    return ans;
}