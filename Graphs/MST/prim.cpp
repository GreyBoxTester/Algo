#include <vector>
#include <cstdint>

using i64 = int64_t;
using u64 = uint64_t;

struct Node
{
    std::vector<std::pair<i64, i64>> next;
    i64 minw = std::numeric_limits<i64>::max();
    i64 minp = -1;
    bool v = false;
};

std::vector<Node> nodes;

void prim()
{
    for (i64 i = 0; i < nodes.size(); i++)
    {
        i64 cv = -1;
        for (i64 j = 0; j < nodes.size(); j++)
        {
            if (nodes[j].v) { continue; }
            if (cv == -1 || nodes[j].minw < nodes[cv].minw) { cv = j; }
        }

        nodes[cv].v = true;

        for (auto& [next, w] : nodes[cv].next)
        {
            if (nodes[next].v) { continue; }
            if (w < nodes[next].minw)
            {
                nodes[next].minw = w;
                nodes[next].minp = cv;
            }
        }
    }
}
