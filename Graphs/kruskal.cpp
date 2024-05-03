#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <cstdint>
#include <cmath>
#include <random>
#include <map>
#include <set>
#include <queue>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

struct Edge
{
    i64 a, b, w;
};

class DSU
{
private:
    struct Node
    {
        i64 p, sz = 1;
    };
public:
    DSU(i64 n) : tr(n) { for (i64 i = 0; i < n; i++) { tr[i].p = i; } }

    i64 find(i64 v) { return tr[v].p == v ? v : (tr[v].p = find(tr[v].p)); }

    bool join(i64 a, i64 b)
    {
        a = find(a); b = find(b);
        if (a == b) { return false; }
        if (tr[a].sz > tr[b].sz) { std::swap(a, b); }
        tr[a].p = b;
        tr[b].sz += tr[a].sz;
        return true;
    }
private:
    std::vector<Node> tr;
};

std::vector<Edge> kruskal(i64 n, const std::vector<Edge>& edges)
{
    std::vector<Edge> ans;
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    DSU dsu(n);
    for (auto& e : edges)
    {
        if (!dsu.join(e.a, e.b)) { continue; }
        ans.push_back(e);
    }
    return ans;
}
