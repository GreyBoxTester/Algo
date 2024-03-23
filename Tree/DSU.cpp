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
        : nodes(n)
    {
        for (i64 i = 0; i < n; i++) { nodes[i].p = i; }
    }

    i64 find(i64 v)
    {
        return (nodes[v].p == v) ? v : (nodes[v].p = find(nodes[v].p));
    }

    void join(i64 a, i64 b)
    {
        i64 pa = find(a);
        i64 pb = find(b);
        if (nodes[pa].sz > nodes[pb].sz) { std::swap(pa, pb); }
        nodes[pa].p = pb;
        nodes[pb].sz = std::max(nodes[pb].sz, nodes[pa].sz + 1);
    }

private:
    std::vector<Node> nodes;
};
