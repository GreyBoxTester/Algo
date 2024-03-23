#include <vector>
#include <set>
#include <bit>

using i64 = int64_t;

class SegTreeCntNum
{
public:
    SegTreeCntNum(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1), arr(len, defVal)
    {
        build(0, 0, len);
    }

    inline void set(size_t i, i64 val) { set(i, val, 0, 0, len); }
    inline i64 get(size_t l, size_t r, i64 val) { return get(l, r, val, 0, 0, len); }

private:
    void build(size_t x, size_t lx, size_t rx)
    {
        if (rx - lx == 1) { tr[x].insert(defVal); return; }
        size_t m = (lx + rx) / 2;
        build(x * 2 + 1, lx, m);
        build(x * 2 + 2, m, rx);
        for (size_t i = 0; i < rx - lx; i++) { tr[x].insert(defVal); }
    }

    void set(size_t i, i64 val, size_t x, size_t l, size_t r)
    {
        tr[x].erase(tr[x].find(arr[i]));
        if (r - l == 1)
        {
            arr[i] = val;
            tr[x].insert(arr[i]);
            return;
        }
        size_t m = (l + r) / 2;
        if (i < m) { set(i, val, x * 2 + 1, l, m); }
        else { set(i, val, x * 2 + 2, m, r); }
        tr[x].insert(arr[i]);
    }

    i64 get(size_t l, size_t r, i64 val, size_t x, size_t lx, size_t rx)
    {
        if (l <= lx && rx <= r) { return tr[x].count(val); }
        if (l >= rx || lx >= r) { return 0; }
        size_t m = (lx + rx) / 2;
        return get(l, r, val, x * 2 + 1, lx, m) + get(l, r, val, x * 2 + 2, m, rx);
    }
private:
    static constexpr i64 defVal = 0;
private:
    size_t len;
    std::vector<std::multiset<i64>> tr;
    std::vector<i64> arr;
};
