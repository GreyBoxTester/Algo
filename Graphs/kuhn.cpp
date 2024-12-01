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
#include <set>
#include <bit>
#include <queue>

namespace rn = std::ranges;
namespace rv = std::ranges::views;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

struct Node
{
    std::vector<i64> next;
    bool v = false;
};

std::vector<Node> nodes;
std::vector<i64> rtol;

bool dfs(i64 v)
{
    if (nodes[v].v) { return false; }
    nodes[v].v = true;
    for (i64 next : nodes[v].next)
    {
        if (rtol[next] == -1 || dfs(rtol[next]))
        {
            rtol[next] = v;
            return true;
        }
    }
    return false;
}

i64 kuhn()
{
    for (i64 v = 0; v < nodes.size(); v++)
    {
        for (auto& node : nodes) { node.v = false; }
        dfs(v);
    }
    return rtol.size() - std::count(rtol.begin(), rtol.end(), -1);
}

void alg()
{
    i64 n, m, k; std::cin >> n >> m >> k;
    nodes.resize(n);
    rtol.assign(m, -1);
    while (k--)
    {
        i64 a, b; std::cin >> a >> b; a--; b--;
        nodes[a].next.push_back(b);
    }

    std::cout << kuhn() << '\n';
    for (i64 i = 0; i < m; i++)
    {
        if (rtol[i] == -1) { continue; }
        std::cout << (rtol[i] + 1) << ' ' << (i + 1) << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 t = 1;
    //std::cin >> t;
    while (t--) { alg(); }
}
