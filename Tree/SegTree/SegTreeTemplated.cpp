#include <vector>
#include <bit>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

template<typename T, typename Operation, T defVal = T(), Operation op = Operation()>
class SegTree
{
public:
    SegTree(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1, defVal)
    {}

    SegTree(const std::vector<T>& v)
        : len(std::bit_ceil(v.size())), tr(len * 2 - 1, defVal)
    {
        build(0, 0, len, v);
    }

    inline void set(size_t i, T val) { set(i, val, 0, 0, len); }
    inline T get(size_t l, size_t r) { return get(l, r, 0, 0, len); }

private:
    void build(size_t x, size_t l, size_t r, const std::vector<T>& v)
    {
        if (r - l == 1) { tr[x] = (l < v.size() ? v[l] : defVal); return; }
        size_t m = (l + r) / 2;
        build(x * 2 + 1, l, m, v);
        build(x * 2 + 2, m, r, v);
        tr[x] = op(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    void set(size_t i, T val, size_t x, size_t l, size_t r)
    {
        if (r - l == 1) { tr[x] = val; return; }
        size_t m = (l + r) / 2;
        if (i < m) { set(i, val, x * 2 + 1, l, m); }
        else { set(i, val, x * 2 + 2, m, r); }
        tr[x] = op(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    T get(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        if (l <= lx && rx <= r) { return tr[x]; }
        if (l >= rx || lx >= r) { return defVal; }
        size_t m = (lx + rx) / 2;
        return op(get(l, r, x * 2 + 1, lx, m), get(l, r, x * 2 + 2, m, rx));
    }
private:
    size_t len;
    std::vector<T> tr;
};

using SegTreeSum = SegTree<i64, i64(*)(i64, i64), 0, [](i64 a, i64 b) { return a + b; }>;
using SegTreeMin = SegTree<i64, i64(*)(i64, i64), std::numeric_limits<i64>::max(), [](i64 a, i64 b) { return std::min(a, b); }>;
using SegTreeMax = SegTree<i64, i64(*)(i64, i64), 0, [](i64 a, i64 b) { return std::max(a, b); }>;

template<typename T>
class DeltaSegTree
{
public:
    DeltaSegTree(size_t n) : deltas(n) {}
    void add(size_t l, size_t r, T delta)
    {
        deltas.set(l, deltas.get(l, l + 1) + delta);
        if (r < deltas.size()) { deltas.set(r, deltas.get(r, r + 1) - delta); }
    }

    T get(size_t i) { return deltas.get(0, i + 1); }
private:
    SegTree<T, T(*)(T, T), 0, [](T a, T b) { return a + b }> deltas;
};