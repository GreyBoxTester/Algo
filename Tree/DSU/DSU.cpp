#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

class DSU
{
private:
    struct Node
    {
        i64 p, sz = 1;
    };
public:
    DSU(i64 n)
        : tr(n)
    {
        for (i64 i = 0; i < n; i++) { tr[i].p = i; }
    }

    i64 find(i64 v)
    {
        return tr[v].p == v ? v : (tr[v].p = find(tr[v].p));
    }

    bool join(i64 a, i64 b)
    {
        a = find(a); b = find(b);
        if (a == b) { return false; }
        if (tr[a].sz > tr[b].sz) { std::swap(a, b); }
        tr[a].p = b;
        tr[b].sz += tr[a].sz;
        return true;
    }

    void hang(i64 c, i64 p)
    {
        c = find(c); p = find(p);
        if (c == p) { return; }
        tr[c].p = p;
        tr[p].sz += tr[c].sz;
    }

    i64 size(i64 v)
    {
        return tr[find(v)].sz;
    }
private:
    std::vector<Node> tr;
};


class DSUSegJoin
{
public:
    DSUSegJoin(u64 n)
        : dsu(n), next(n + 1)
    {}

    i64 find(i64 v) { return dsu.find(v); }
    bool join(i64 a, i64 b) { return dsu.join(a, b); }

    //O(a(n)) ammortized
    void joinSeg(i64 a, i64 b)
    {
        a = next.find(a);
        while (a < b)
        {
            dsu.join(a, b);
            next.hang(a, a + 1);
            a = next.find(a);
        }
    }

public:
    DSU dsu;
    DSU next;
};