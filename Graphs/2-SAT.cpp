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
#include <cctype>

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
    i64 col = -1;
};

std::vector<Node> nodes;
i64 col = 0;
void dfs(i64 i)
{
    if (nodes[i].col != -1) { return; }
    nodes[i].col = col;
    for (i64 next : nodes[i].next) { dfs(next); }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 n, m; std::cin >> n >> m;
    nodes.resize(n * 2);
    for (i64 i = 0; i < m; i++)
    {
        i64 a, b, x; std::cin >> a >> b >> x; a--; b--;
        a *= 2; b *= 2;
        a ^= i64(!x);
        nodes[a].next.push_back(b);
        nodes[b].next.push_back(a);
        a ^= 1; b ^= 1;
        nodes[a].next.push_back(b);
        nodes[b].next.push_back(a);
    }

    for (i64 i = 0; i < n * 2; i++)
    {
        if (nodes[i].col == -1) { dfs(i); col++; }
    }

    for (i64 i = 0; i < n * 2; i += 2)
    {
        if (nodes[i].col == nodes[i + 1].col) { std::cout << "Impossible"; return 0; }
    }

    std::vector<i64> ans;
    for (i64 i = 0; i < n * 2; i += 2)
    {
        if (nodes[i].col > nodes[i + 1].col) { ans.push_back(i / 2); }
    }
    std::cout << ans.size() << '\n';
    for (i64 i : ans) { std::cout << (i + 1) << ' '; }
}
