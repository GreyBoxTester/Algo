#include <iostream>
#include <vector>
#include <algorithm>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

struct Node
{
    std::vector<i64> next;
    std::vector<i64> tnext;
    i64 col = -1;
    bool v = false;
};

std::vector<Node> nodes;

std::vector<i64> ord;
void topsort(i64 i)
{
    nodes[i].v = true;
    for (i64 next : nodes[i].next)
    {
        if (!nodes[next].v) { topsort(next); }
    }
    ord.push_back(i);
}

i64 col = 0;
void tdfs(i64 i)
{
    nodes[i].col = col;
    for (i64 next : nodes[i].tnext)
    {
        if (nodes[next].col == -1) { tdfs(next); }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 n; std::cin >> n;
    nodes.resize(n);
    for (i64 i = 0; i < n; i++)
    {
        i64 a, b; std::cin >> a >> b; a--; b--;
        nodes[a].next.push_back(b);
        nodes[b].tnext.push_back(a);
    }

    for (i64 i = 0; i < n; i++)
    {
        if (!nodes[i].v) { topsort(i); }
    }
    std::reverse(ord.begin(), ord.end());

    for (i64 i : ord)
    {
        if (nodes[i].col == -1) { tdfs(i); col++; }
    }

}
