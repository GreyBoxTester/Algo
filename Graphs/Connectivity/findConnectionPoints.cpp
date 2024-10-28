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

struct Node
{
    std::vector<i64> next;
    i64 d = -1, md = -1;
    bool v = false;
};

std::vector<Node> nodes;
std::vector<i64> points;
void dfs(i64 i, i64 p)
{
    nodes[i].d = nodes[i].md = (p == -1 ? 0 : nodes[p].d + 1);
    nodes[i].v = true;
    i64 cnt = 0;
    for (auto next : nodes[i].next)
    {
        if (p == next) { continue; }
        if (nodes[next].v)
        {
            nodes[i].md = std::min(nodes[i].md, nodes[next].d);
        }
        else
        {
            dfs(next, i);
            nodes[i].md = std::min(nodes[i].md, nodes[next].md);
            if (p != -1 && nodes[i].d <= nodes[next].md)
            {
                points.push_back(i);
            }
            cnt++;
        }
    }
    if (p == -1 && cnt > 1) { points.push_back(i); }
}

int main()
{
#ifdef ONLINE_JUDGE
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
#endif

    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);

    i64 n, m; std::cin >> n >> m;
    nodes.resize(n);
    while (m--)
    {
        i64 a, b; std::cin >> a >> b; a--; b--;
        nodes[a].next.push_back(b);
        nodes[b].next.push_back(a);
    }

    for (i64 i = 0; i < n; i++)
    {
        if (!nodes[i].v) { dfs(i, -1); }
    }

    rn::sort(points);
    points.erase(std::unique(points.begin(), points.end()), points.end());
    std::cout << points.size() << '\n';
    for (auto& ai : points) { std::cout << (ai + 1) << '\n'; }
}
