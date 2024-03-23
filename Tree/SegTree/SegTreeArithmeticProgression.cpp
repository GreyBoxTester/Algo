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
#include <deque>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

std::pair<i64, i64>& operator +=(std::pair<i64, i64>& p1, const std::pair<i64, i64> p2)
{
    p1.first += p2.first;
    p1.second += p2.second;
    return p1;
}

i64 sumAP(std::pair<i64, i64> p, i64 i1, i64 i2)
{
    return (2 * p.first + (i1 + i2 - 1) * p.second) * (i2 - i1) / 2;
}

class SegTreeAP
{
public:
    struct Node
    {
        i64 sum = 0;
        std::pair<i64, i64> add = { 0, 0 };
    };
public:
    SegTreeAP(size_t n)
        : len(std::bit_ceil(n)), tr(n * 2 - 1)
    {}

    void add(size_t l, size_t r, std::pair<i64, i64> p) { add(l, r, p, 0, 0, len); }
    i64 sum(size_t l, size_t r) { return sum(l, r, 0, 0, len); }

private:
    void add(size_t l, size_t r, std::pair<i64, i64> p, size_t x, size_t lx, size_t rx)
    {
        push(l, x, lx, rx);
        if (l <= lx && rx <= r)
        {
            tr[x].sum += sumAP(p, lx - l, rx - l);
            tr[x].add += { p.first + p.second * (lx - l), p.second };
            return;
        }
        if (rx <= l || r <= lx) { return; }
        size_t m = (lx + rx) / 2;
        add(l, r, p, x * 2 + 1, lx, m);
        add(l, r, p, x * 2 + 2, m, rx);
        tr[x].sum = tr[x * 2 + 1].sum + tr[x * 2 + 2].sum;
    }

    i64 sum(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        push(l, x, lx, rx);
        if (l <= lx && rx <= r) { return tr[x].sum; }
        if (rx <= l || r <= lx) { return 0; }
        size_t m = (lx + rx) / 2;
        return sum(l, r, x * 2 + 1, lx, m) + sum(l, r, x * 2 + 2, m, rx);
    }

    void push(size_t l, size_t x, size_t lx, size_t rx)
    {
        if (x >= tr.size()) { return; }
        if (rx - lx > 1)
        {
            size_t m = (lx + rx) / 2;
            tr[x * 2 + 1].sum += sumAP(tr[x].add, 0, m - lx);
            tr[x * 2 + 1].add += tr[x].add;

            tr[x * 2 + 2].sum += sumAP(tr[x].add, m - lx, rx - lx);
            tr[x * 2 + 2].add.first += tr[x].add.first + tr[x].add.second * (m - lx);
            tr[x * 2 + 2].add.second += tr[x].add.second;
        }
        tr[x].add = { 0, 0 };
    }
private:
    size_t len = 0;
    std::vector<Node> tr;
};

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 n, q; std::cin >> n >> q;
    SegTreeAP tr(n);
    while (q--)
    {
        i64 t; std::cin >> t;
        i64 l, r; std::cin >> l >> r;
        if (t == 1)
        {
            i64 a, d; std::cin >> a >> d;
            tr.add(l, r, { a, d });
        }
        else
        {
            std::cout << tr.sum(l, r) << '\n';
        }
    }
}
