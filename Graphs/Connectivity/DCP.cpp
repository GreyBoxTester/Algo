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
#include <bit>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

struct DSUWithUndo
{
    struct Node { i64 p = 0, sz = 1; };
    void init(i64 n)
    {
        tr.resize(n);
        op.clear();
        cnt = n;
        for (i64 i = 0; i < n; i++) { tr[i].p = i; }
    }
    i64 find(i64 v)
    {
        for (; tr[v].p != v; v = tr[v].p);
        return v;
    }
    bool join(i64 a, i64 b)
    {
        a = find(a); b = find(b);
        if (a == b) { return false; }
        if (tr[a].sz < tr[b].sz) { std::swap(a, b); }
        tr[b].p = a; tr[a].sz += tr[b].sz;
        op.push_back({ a, b });
        cnt--;
        return true;
    }
    void undo()
    {
        auto [a, b] = op.back(); op.pop_back();
        tr[b].p = b; tr[a].sz -= tr[b].sz;
        cnt++;
    }
    std::vector<Node> tr;
    i64 cnt;
    std::vector<std::pair<i64, i64>> op;
};

struct Query
{
    char t;
    i64 u, v;
};

std::vector<Query> queries;
i64 len = 0;
std::vector<std::vector<std::pair<i64, i64>>> tr;
DSUWithUndo dsu;
std::vector<i64> ans;

void add(i64 l, i64 r, std::pair<i64, i64> p, i64 x = 0, i64 lx = 0, i64 rx = len)
{
    if (r <= lx || rx <= l) { return; }
    if (l <= lx && rx <= r) { tr[x].push_back(p); return; }
    i64 m = (lx + rx) / 2;
    add(l, r, p, x * 2 + 1, lx, m);
    add(l, r, p, x * 2 + 2, m, rx);
}

void calc(i64 x = 0, i64 lx = 0, i64 rx = len)
{
    i64 opc = dsu.op.size();
    for (auto [u, v] : tr[x]) { dsu.join(u, v); }

    if (rx - lx == 1)
    {
        if (lx < queries.size() && queries[lx].t == '?') { ans.push_back(dsu.cnt); }
    }
    else
    {
        i64 m = (lx + rx) / 2;
        calc(x * 2 + 1, lx, m);
        calc(x * 2 + 2, m, rx);
    }

    while (dsu.op.size() > opc) { dsu.undo(); }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 n, q; std::cin >> n >> q;

    len = std::bit_ceil<size_t>(q);
    tr.resize(len * 2 - 1);
    dsu.init(n);
    queries.resize(q);

    std::map<std::pair<i64, i64>, i64> mpb;
    for (i64 i = 0; i < q; i++)
    {
        auto& [t, u, v] = queries[i];
        std::cin >> t;
        if (t == '?') { continue; }

        std::cin >> u >> v; u--; v--;
        if (u > v) { std::swap(u, v); }
        if (t == '+') { mpb[{u, v}] = i; }
        else { add(mpb[{ u, v }], i + 1, { u, v }); mpb[{u, v}] = -1; }
    }

    for (auto [p, i] : mpb)
    {
        if (i == -1) { continue; }
        add(i, q, p);
    }

    calc();

    for (i64 c : ans) { std::cout << c << ' '; }
}
