#include <vector>
#include <bit>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

class SegTree
{
public:
    using ValueType = i64;
public:
    SegTree(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1, defVal)
    {}

    SegTree(const std::vector<ValueType>& v)
        : len(std::bit_ceil(v.size())), tr(len * 2 - 1, defVal)
    {
        build(0, 0, len, v);
    }

    inline void set(size_t i, ValueType val) { set(i, val, 0, 0, len); }
    inline ValueType get(size_t l, size_t r) { return get(l, r, 0, 0, len); }

private:
    void build(size_t x, size_t l, size_t r, const std::vector<ValueType>& v)
    {
        if (r - l == 1) { tr[x] = (l < v.size() ? v[l] : defVal); return; }
        size_t m = (l + r) / 2;
        build(x * 2 + 1, l, m, v);
        build(x * 2 + 2, m, r, v);
        tr[x] = op(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    void set(size_t i, ValueType val, size_t x, size_t l, size_t r)
    {
        if (r - l == 1) { tr[x] = val; return; }
        size_t m = (l + r) / 2;
        if (i < m) { set(i, val, x * 2 + 1, l, m); }
        else { set(i, val, x * 2 + 2, m, r); }
        tr[x] = op(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    ValueType get(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        if (l <= lx && rx <= r) { return tr[x]; }
        if (l >= rx || lx >= r) { return defVal; }
        size_t m = (lx + rx) / 2;
        return op(get(l, r, x * 2 + 1, lx, m), get(l, r, x * 2 + 2, m, rx));
    }

private:
    inline static ValueType op(ValueType a, ValueType b) { return a + b; }
    static constexpr ValueType defVal = 0;

private:
    size_t len;
    std::vector<ValueType> tr;
};

//==============
class SegTreeSum
{
public:
    using ValueType = int64_t;
public:
    SegTreeSum(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1, defVal)
    {}

    inline void set(size_t i, ValueType val) { set(i, val, 0, 0, len); }
    inline ValueType get(size_t l, size_t r) { return get(l, r, 0, 0, len); }
    inline size_t findNthZero(size_t n) { return findNthZero(n, 0, 0, len); }

private:
    void set(size_t i, ValueType val, size_t x, size_t l, size_t r)
    {
        if (r - l == 1) { tr[x] = val; return; }
        size_t m = (l + r) / 2;
        if (i < m) { set(i, val, x * 2 + 1, l, m); }
        else { set(i, val, x * 2 + 2, m, r); }
        tr[x] = op(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    ValueType get(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        if (l <= lx && rx <= r) { return tr[x]; }
        if (l >= rx || lx >= r) { return defVal; }
        size_t m = (lx + rx) / 2;
        return op(get(l, r, x * 2 + 1, lx, m), get(l, r, x * 2 + 2, m, rx));
    }

    size_t findNthZero(size_t n, size_t x, size_t lx, size_t rx)
    {
        if (rx - lx == 1) { return lx; }
        size_t m = (lx + rx) / 2;
        size_t lc = (m - lx) - tr[x * 2 + 1];
        if (lc >= n) { return findNthZero(n, x * 2 + 1, lx, m); }
        else { return findNthZero(n - lc, x * 2 + 2, m, rx); }
    }

private:
    inline static ValueType op(ValueType a, ValueType b) { return a + b; }
    static constexpr ValueType defVal = 0;

private:
    size_t len;
    std::vector<ValueType> tr;
};

class SegTreeMin
{
public:
    using ValueType = int64_t;
public:
    SegTreeMin(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1, defVal)
    {}

    inline void set(size_t i, ValueType val) { set(i, val, 0, 0, len); }
    inline ValueType get(size_t l, size_t r) { return get(l, r, 0, 0, len); }

private:
    void set(size_t i, ValueType val, size_t x, size_t l, size_t r)
    {
        if (r - l == 1) { tr[x] = val; return; }
        size_t m = (l + r) / 2;
        if (i < m) { set(i, val, x * 2 + 1, l, m); }
        else { set(i, val, x * 2 + 2, m, r); }
        tr[x] = op(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    ValueType get(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        if (l <= lx && rx <= r) { return tr[x]; }
        if (l >= rx || lx >= r) { return defVal; }
        size_t m = (lx + rx) / 2;
        return op(get(l, r, x * 2 + 1, lx, m), get(l, r, x * 2 + 2, m, rx));
    }

private:
    inline static ValueType op(ValueType a, ValueType b) { return std::min(a, b); }
    static constexpr ValueType defVal = std::numeric_limits<ValueType>::max();

private:
    size_t len;
    std::vector<ValueType> tr;
};


//SegTree with Mex(l, r)
class SegTreeMex
{
public:
    using ValueType = size_t;
public:
    SegTreeMex(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1, defVal)
    {
        for (size_t i = 0; i < len; i++) { rem(i); }
    }

    void add(size_t i) { set(i, defVal, 0, 0, len); }
    void rem(size_t i) { set(i, i, 0, 0, len); }
    size_t get(size_t l, size_t r) { return get(l, r, 0, 0, len); }

private:
    void set(size_t i, ValueType val, size_t x, size_t l, size_t r)
    {
        if (r - l == 1) { tr[x] = val; return; }
        size_t m = (l + r) / 2;
        if (i < m) { set(i, val, x * 2 + 1, l, m); }
        else { set(i, val, x * 2 + 2, m, r); }
        tr[x] = op(tr[x * 2 + 1], tr[x * 2 + 2]);
    }

    ValueType get(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        if (l <= lx && rx <= r) { return tr[x]; }
        if (l >= rx || lx >= r) { return defVal; }
        size_t m = (lx + rx) / 2;
        return op(get(l, r, x * 2 + 1, lx, m), get(l, r, x * 2 + 2, m, rx));
    }

private:
    inline static ValueType op(ValueType a, ValueType b) { return std::min(a, b); }
    static constexpr ValueType defVal = std::numeric_limits<ValueType>::max();

private:
    size_t len;
    std::vector<ValueType> tr;
};


///SegTree set min on range
class SegTreeMinRange
{
public:
    using ValueType = int64_t;
    struct Node
    {
        ValueType val = defVal;
        bool lazy = false;
    };
public:
    SegTreeMinRange(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1)
    {}

    void set(size_t l, size_t r, ValueType v) { set(l, r, v, 0, 0, len); }
    ValueType get(size_t l, size_t r) { return get(l, r, 0, 0, len); }
private:
    void set(size_t l, size_t r, ValueType v, size_t x, size_t lx, size_t rx)
    {
        if (l >= rx || lx >= r) { return; }
        if (l <= lx && rx <= r)
        {
            updateMin(x, v);
            tr[x].lazy = true;
            return;
        }

        push(x);
        size_t m = (lx + rx) / 2;
        set(l, r, v, x * 2 + 1, lx, m);
        set(l, r, v, x * 2 + 2, m, rx);
        tr[x].val = op(tr[x * 2 + 1].val, tr[x * 2 + 2].val);
    }

    ValueType get(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        if (l <= lx && rx <= r) { return tr[x].val; }
        if (l >= rx || lx >= r) { return defVal; }

        push(x);
        size_t m = (lx + rx) / 2;
        return op(get(l, r, x * 2 + 1, lx, m), get(l, r, x * 2 + 2, m, rx));
    }

    void push(size_t x)
    {
        if (x * 2 + 1 >= tr.size() || !tr[x].lazy) { return; }
        tr[x].lazy = false;
        updateMin(x * 2 + 1, tr[x].val);
        tr[x * 2 + 1].lazy = true;
        updateMin(x * 2 + 2, tr[x].val);
        tr[x * 2 + 2].lazy = true;
    }

    void updateMin(size_t x, ValueType v)
    {
        if (tr[x].val == defVal) { tr[x].val = v; }
        else { tr[x].val = std::max(tr[x].val, v); }
    }

private:
    static const ValueType op(ValueType a, ValueType b) { return std::min(a, b); }
public:
    static constexpr ValueType defVal = std::numeric_limits<ValueType>::max();
private:
    size_t len;
    std::vector<Node> tr;
};

