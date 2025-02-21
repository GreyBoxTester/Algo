#include <vector>
#include <cstdint>
#include <bit>

template<typename T, typename Operation>
class PersSegTree
{
private:
    struct Node
    {
        size_t l = -1, r = -1;
        T val;
    };

public:
    PersSegTree(size_t n, T defVal = T(), Operation op = Operation())
        : sz(std::bit_ceil(n)), defVal(defVal), op(op)
    {
        roots.push_back(build(0, sz));
    }

    size_t set(size_t i, T v)
    {
        roots.push_back(set(i, v, roots.back(), 0, sz));
        return roots.size() - 1;
    }

    T get(size_t l, size_t r, i64 ver = -1) const
    {
        return get(l, r, ver == -1 ? roots.back() : roots[ver], 0, sz);
    }

    i64 currentVersion() const 
    { 
        return roots.size() - 1; 
    }

private:
    size_t build(size_t lx, size_t rx)
    {
        if (rx - lx == 1) { return create(); }
        size_t m = (lx + rx) / 2;
        size_t x = create();
        tr[x].l = build(lx, m);
        tr[x].r = build(m, rx);
        return x;
    }

    size_t set(size_t i, T v, size_t x, size_t lx, size_t rx)
    {
        x = copy(x);
        if (rx - lx == 1) { tr[x].val = v; return x; }
        size_t m = (lx + rx) / 2;
        if (i < m) { tr[x].l = set(i, v, tr[x].l, lx, m); }
        else { tr[x].r = set(i, v, tr[x].r, m, rx); }
        tr[x].val = op(tr[tr[x].l].val, tr[tr[x].r].val, m - lx);
        return x;
    }

    T get(size_t l, size_t r, size_t x, size_t lx, size_t rx) const
    {
        if (l <= lx && rx <= r) { return tr[x].val; }
        if (rx <= l || r <= lx) { return defVal; }
        size_t m = (lx + rx) / 2;
        return op(get(l, r, tr[x].l, lx, m), get(l, r, tr[x].r, m, rx), m - lx);
    }

    size_t create()
    {
        tr.emplace_back();
        tr.back().val = defVal;
        return tr.size() - 1;
    }

    size_t copy(size_t x)
    {
        tr.emplace_back(tr[x]);
        return tr.size() - 1;
    }
private:
    std::vector<Node> tr;
    std::vector<size_t> roots;
    size_t sz;
    T defVal;
    Operation op;
};
