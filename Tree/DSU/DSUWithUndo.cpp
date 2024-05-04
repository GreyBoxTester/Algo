#include <vector>

using i64 = int64_t;

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
