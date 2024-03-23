#include <vector>
#include <bit>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

class ImplicitSegTree
{
public:
    using ValueType = i64;
    struct Node
    {
        i64 l = -1, r = -1;
        ValueType sum = 0;
        ValueType lazySetVal = 0;
        bool lazySet = false;
    };

public:
    ImplicitSegTree(size_t n)
        : len(std::bit_ceil(n)), tr(1)
    {}

    inline void set(size_t l, size_t r, ValueType val) { set(l, r, val, 0, 0, len); }
    inline ValueType get(size_t l, size_t r) { return get(l, r, 0, 0, len); }

private:

    void set(size_t l, size_t r, ValueType val, size_t x, size_t lx, size_t rx)
    {
        pushChildren(x, lx, rx);
        pushSet(x, lx, rx);

        if (l <= lx && rx <= r) { tr[x].lazySet = true; tr[x].lazySetVal = val; return; }
        if (l >= rx || lx >= r) { return; }

        size_t m = (lx + rx) / 2;
        set(l, r, val, tr[x].l, lx, m);
        set(l, r, val, tr[x].r, m, rx);

        pushSet(tr[x].l, lx, m);
        pushSet(tr[x].r, m, rx);

        upd(x);
    }

    ValueType get(size_t l, size_t r, size_t x, size_t lx, size_t rx)
    {
        if (l >= rx || lx >= r) { return defVal; }

        pushChildren(x, lx, rx);
        pushSet(x, lx, rx);
        if (l <= lx && rx <= r) { return tr[x].sum; }
        size_t m = (lx + rx) / 2;
        return get(l, r, tr[x].l, lx, m) + get(l, r, tr[x].r, m, rx);
    }


    void pushChildren(size_t x, size_t lx, size_t rx)
    {
        if (rx - lx == 1 || tr[x].l != -1) { return; }
        tr[x].l = tr.size();
        tr.emplace_back();
        tr[x].r = tr.size();
        tr.emplace_back();
    }

    void pushSet(size_t x, size_t lx, size_t rx)
    {
        if (x >= tr.size() || !tr[x].lazySet) { return; }
        tr[x].sum = (rx - lx) * tr[x].lazySetVal;
        if (rx - lx > 1)
        {
            tr[tr[x].l].lazySetVal = tr[x].lazySetVal;
            tr[tr[x].l].lazySet = true;
            tr[tr[x].r].lazySetVal = tr[x].lazySetVal;
            tr[tr[x].r].lazySet = true;
        }
        tr[x].lazySet = false;
    }

private:
    void upd(size_t x)
    {
        if (tr[x].l == -1) { tr[x].sum = defVal; return; }
        tr[x].sum = tr[tr[x].l].sum + tr[tr[x].r].sum;
    }
    static constexpr ValueType defVal = 0;

private:
    size_t len;
    std::vector<Node> tr;
};
