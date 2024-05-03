#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <limits>
#include <numeric>
#include <cstdint>
#include <cmath>
#include <random>
#include <map>
#include <set>
#include <bit>
#include <queue>

namespace rn = std::ranges;
namespace rv = std::ranges::views;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

template<typename T>
class SegTree
{
public:
    struct Node
    {
        T sum = 0;
        T add = 0;
    };
public:
    void init(size_t n)
    {
        len = std::bit_ceil(n);
        tr.assign(len * 2 - 1, {});
    }

    void add(size_t l, size_t r, T val) { add(l, r, val, 0, 0, len); }
    T sum(size_t l, size_t r) { return sum(l, r, 0, 0, len); }

private:
    void build(size_t x, size_t l, size_t r, const std::vector<T>& v)
    {
        if (r - l == 1) { tr[x].sum = (l >= v.size() ? 0 : v[l]); return; }
        size_t m = (l + r) / 2;
        build(x * 2 + 1, l, m, v);
        build(x * 2 + 2, m, r, v);
        tr[x].sum = tr[x * 2 + 1].sum + tr[x * 2 + 2].sum;
    }

    void add(size_t l, size_t r, T val, size_t x, size_t lx, size_t rx)
    {
        push(x, lx, rx);
        if (l <= lx && rx <= r) { tr[x].sum += val * (rx - lx); tr[x].add += val; return; }
        if (l >= rx || lx >= r) { return; }
        size_t m = (lx + rx) / 2;
        add(l, r, val, x * 2 + 1, lx, m);
        add(l, r, val, x * 2 + 2, m, rx);
        tr[x].sum = tr[x * 2 + 1].sum + tr[x * 2 + 2].sum;
    }

    T sum(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        push(x, lx, rx);
        if (l <= lx && rx <= r) { return tr[x].sum; }
        if (rx <= l || r <= lx) { return 0; }
        size_t m = (lx + rx) / 2;
        return sum(l, r, x * 2 + 1, lx, m) + sum(l, r, x * 2 + 2, m, rx);
    }

private:
    void push(size_t x, size_t lx, size_t rx)
    {
        if (rx - lx > 1)
        {
            tr[x * 2 + 1].sum += tr[x].add * (rx - lx) / 2;
            tr[x * 2 + 1].add += tr[x].add;
            tr[x * 2 + 2].sum += tr[x].add * (rx - lx) / 2;
            tr[x * 2 + 2].add += tr[x].add;
        }
        tr[x].add = 0;
    }
private:
    size_t len;
    std::vector<Node> tr;
};

struct Node
{
    std::vector<i64> next;
    i64 head = 0, tin = 0, tout = 0, sz = 0, p = 0;
};

std::vector<Node> nodes;
SegTree<int> tree;

void sdfs(i64 i, i64 p)
{
    nodes[i].p = p;
    if (nodes[i].next.size() > 1 && nodes[i].next[0] == p) { std::swap(nodes[i].next[0], nodes[i].next[1]); }

    for (i64& next : nodes[i].next)
    {
        if (next == p) { continue; }
        sdfs(next, i);
        nodes[i].sz += nodes[next].sz;
        if (nodes[nodes[i].next[0]].sz < nodes[next].sz) { std::swap(nodes[i].next[0], next); }
    }
    nodes[i].sz++;
}

i64 tim = 0;
void hld(i64 i, i64 p, i64 head)
{
    nodes[i].tin = tim++;
    nodes[i].head = head;
    if (nodes[i].next.size() == 0 || (nodes[i].next.size() == 1 && p != -1)) { nodes[i].tout = tim; return; }

    hld(nodes[i].next[0], i, head);
    for (i64 j = 1; j < nodes[i].next.size(); j++)
    {
        i64 next = nodes[i].next[j];
        if (next == p) { continue; }
        hld(next, i, next);
    }
    nodes[i].tout = tim;
}

bool ancestor(i64 a, i64 b)
{
    return nodes[a].tin <= nodes[b].tin && nodes[b].tout <= nodes[a].tout;
}

void add(i64 a, i64 b, i64 val)
{
    while (!ancestor(nodes[a].head, b))
    {
        tree.add(nodes[nodes[a].head].tin, nodes[a].tin + 1, val);
        a = nodes[nodes[a].head].p;
    }

    while (!ancestor(nodes[b].head, a))
    {
        tree.add(nodes[nodes[b].head].tin, nodes[b].tin + 1, val);
        b = nodes[nodes[b].head].p;
    }

    if (!ancestor(a, b)) { std::swap(a, b); }
    tree.add(nodes[a].tin, nodes[b].tin + 1, val);
}

i64 sum(i64 a, i64 b)
{
    i64 ans = 0;
    while (!ancestor(nodes[a].head, b))
    {
        ans += tree.sum(nodes[nodes[a].head].tin, nodes[a].tin + 1);
        a = nodes[nodes[a].head].p;
    }

    while (!ancestor(nodes[b].head, a))
    {
        ans += tree.sum(nodes[nodes[b].head].tin, nodes[b].tin + 1);
        b = nodes[nodes[b].head].p;
    }

    if (!ancestor(a, b)) { std::swap(a, b); }
    ans += tree.sum(nodes[a].tin, nodes[b].tin + 1);
    return ans;
}
