#include <vector>
#include <bit>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

u64 log2ceil(u64 n)
{
    return std::countr_zero(std::bit_ceil(n));
}
u64 log2floor(u64 n)
{
    return std::countr_zero(std::bit_floor(n));
}

class DynamicLCA
{
public:
    struct Node
    {
        u64 h = 0;
        std::vector<u64> up;
    };
public:
    DynamicLCA(u64 n)
        : nodes(n)
    {
        for (i64 i = 0; i < n; i++) { nodes[i].up.assign(log2ceil(n), i); }
    }

    void add(u64 a, u64 b)
    {
        nodes[b].h = nodes[a].h + 1;
        nodes[b].up[0] = a;
        for (i64 p = 1; p < nodes[b].up.size(); p++)
        {
            nodes[b].up[p] = nodes[nodes[b].up[p - 1]].up[p - 1];
        }
    }

    u64 get(u64 a, u64 b)
    {
        if (nodes[a].h < nodes[b].h) { std::swap(a, b); }
        while (nodes[a].h - nodes[b].h > 0)
        {
            u64 d = nodes[a].h - nodes[b].h;
            a = nodes[a].up[log2floor(d)];
        }
        if (a == b) { return a; }
        for (i64 p = nodes[a].up.size() - 1; p >= 0; p--)
        {
            if (nodes[a].up[p] != nodes[b].up[p]) { a = nodes[a].up[p]; b = nodes[b].up[p]; }
        }
        return nodes[a].up[0];
    }

private:
    std::vector<Node> nodes;
};