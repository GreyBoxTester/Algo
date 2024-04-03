#include <map>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

class DSU
{
private:
    struct Node
    {
        i64 p = 0, sz = 1;
    };
public:
    DSU(DSU&& other) noexcept = default;
    DSU& operator=(DSU&& other) noexcept = default;

    i64 find(i64 v)
    {
        Node& nd = get(v);
        return nd.p == v ? v : (nd.p = find(nd.p));
    }

    bool join(i64 a, i64 b)
    {
        a = find(a); b = find(b);
        if (a == b) { return false; }
        Node* na = &get(a);
        Node* nb = &get(b);
        if (na->sz > nb->sz) { std::swap(na, nb); std::swap(a, b); }
        na->p = b;
        nb->sz += na->sz;
        return true;
    }

    i64 merge(DSU& other)
    {
        i64 cnt = 0;
        for (auto& [v, nd] : other.tr)
        {
            cnt += join(v, other.find(v));
        }
        return cnt;
    }
private:
    Node& get(i64 v)
    {
        auto it = tr.find(v);
        if (it != tr.end()) { return it->second; }
        auto& nd = tr[v];
        nd.p = v;
        return nd;
    }
private:
    std::map<i64, Node> tr;
};