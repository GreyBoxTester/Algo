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

struct Node1
{
    i64 p = 0, sz = 1, rp = -1, col = 0;
};

struct Node2
{
    i64 p = 0;
};

std::vector<Node1> tr1;
std::vector<Node2> tr2;
i64 bcnt = 0;

void init(i64 n)
{
    tr1.resize(n);
    for (i64 i = 0; i < n; i++) { tr1[i].p = i; }
    tr2.resize(n);
    for (i64 i = 0; i < n; i++) { tr2[i].p = i; }
}

i64 find1(i64 v) { return tr1[v].p == v ? v : tr1[v].p = find1(tr1[v].p); }
i64 find2(i64 v)
{
    if (v == -1) { return -1; }
    return tr2[v].p == v ? v : tr2[v].p = find2(tr2[v].p);
}

void reroot(i64 v)
{
    v = find2(v);
    i64 r = v;
    i64 c = -1;
    while (v != -1)
    {
        i64 p = find2(tr1[v].rp);
        tr1[v].rp = c;
        tr1[v].p = r;
        c = v;
        v = p;
    }

    tr1[r].sz = tr1[c].sz;
}

i64 col = 0;
i64 lca(i64 u, i64 v)
{
    col++;
    u = find2(u);
    v = find2(v);
    tr1[u].col = col;
    while (u != -1)
    {
        tr1[u].col = col;
        u = find2(tr1[u].rp);
    }

    while (tr1[v].col != col) { v = find2(tr1[v].rp); }
    return v;
}

void merge(i64 u, i64 v)
{
    i64 r = lca(u, v);
    u = find2(u);
    v = find2(v);
    while (u != r)
    {
        i64 nu = find2(tr1[u].rp);
        tr2[u].p = r;
        u = nu;
        bcnt--;
    }
    while (v != r)
    {
        i64 nv = find2(tr1[v].rp);
        tr2[v].p = r;
        v = nv;
        bcnt--;
    }
}

void addEdge(i64 u, i64 v)
{
    u = find2(u);
    v = find2(v);
    if (u == v) { return; }

    i64 cu1 = find1(u);
    i64 cv1 = find1(v);
    if (cu1 == cv1) { merge(u, v); }
    else
    {
        bcnt++;
        if (tr1[cu1].sz > tr1[cv1].sz) { std::swap(u, v); std::swap(cu1, cv1); }
        reroot(u);
        tr1[u].p = tr1[u].rp = v;
        tr1[cv1].sz += tr1[u].sz;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 n, q; std::cin >> n >> q;
    init(n);
    while (q--)
    {
        i64 u, v; std::cin >> u >> v; u--; v--;
        addEdge(u, v);
        std::cout << bcnt << '\n';
    }
}
