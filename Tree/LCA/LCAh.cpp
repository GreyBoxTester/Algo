#include <vector>
#include <bit>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

u64 log2ceil(u64 n)
{
    return std::countr_zero(std::bit_ceil(n));
}
u64 log2floor(u64 n)
{
    return std::countr_zero(std::bit_floor(n));
}

struct Node
{
    std::vector<i64> up;
    std::vector<i64> next;
    i64 h = 0;
};

std::vector<Node> nodes;
void init(i64 v, i64 p, i64 h)
{
    nodes[v].up.assign(std::max<size_t>(log2ceil(nodes.size()), 1), v);
    nodes[v].up[0] = p;
    nodes[v].h = h;
    for (i64 i = 1; i < nodes[v].up.size(); i++)
    {
        nodes[v].up[i] = nodes[nodes[v].up[i - 1]].up[i - 1];
    }

    for (i64 next : nodes[v].next)
    {
        if (next == p) { continue; }
        init(next, v, h + 1);
    }
}
i64 lca(i64 a, i64 b)
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
