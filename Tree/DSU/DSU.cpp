#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

struct DSU
{
    struct Node { i64 p = 0, sz = 1; };
    DSU(i64 n) : tr(n) { for (i64 i = 0; i < n; i++) { tr[i].p = i; } }
    i64 find(i64 v) { return v == tr[v].p ? v : tr[v].p = find(tr[v].p); }
    bool join(i64 a, i64 b)
    {
        a = find(a); b = find(b);
        if (a == b) { return false; }
        if (tr[a].sz < tr[b].sz) { std::swap(a, b); }
        tr[b].p = a; tr[a].sz += tr[b].sz;
        return true;
    }
    bool hang(i64 c, i64 p)
    {
        c = find(c); p = find(p);
        if (c == p) { return false; }
        tr[c].p = p; tr[p].sz += tr[c].sz;
        return true;
    }
    std::vector<Node> tr;
};


struct DSURangeJoin
{
    DSURangeJoin(u64 n) : dsu(n), next(n + 1) {}
    i64 find(i64 v) { return dsu.find(v); }
    bool join(i64 a, i64 b) { return dsu.join(a, b); }
    //O(a(n)) ammortized
    void joinRange(i64 a, i64 b)
    {
        a = next.find(a);
        while (a < b)
        {
            dsu.join(a, b);
            next.hang(a, a + 1);
            a = next.find(a);
        }
    }
    DSU dsu;
    DSU next;
};
