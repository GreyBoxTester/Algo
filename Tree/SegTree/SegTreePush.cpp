#include <vector>
#include <bit>

template<typename T>
class SegTreePush
{
public:
    struct Node
    {
        T sum = 0;
        T add = 0;
    };
public:
    SegTreePush(size_t n)
        : len(std::bit_ceil(n)), tr(len * 2 - 1)
    {}

    SegTreePush(const std::vector<T>& v)
        : len(std::bit_ceil(v.size())), tr(len * 2 - 1)
    {
        build(0, 0, len, v);
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
        if (l >= rx || lx >= r) { return 0; }
        size_t m = (lx + rx) / 2;
        return sum(l, r, x * 2 + 1, lx, m) + sum(l, r, x * 2 + 2, m, rx);
    }

private:
    void push(size_t x, size_t lx, size_t rx)
    {
        if (rx - lx == 1) { return; }
        tr[x * 2 + 1].add += tr[x].add;
        tr[x * 2 + 2].add += tr[x].add;
        tr[x * 2 + 1].sum += tr[x].add * ((rx - lx) / 2);
        tr[x * 2 + 2].sum += tr[x].add * ((rx - lx) / 2);
        tr[x].add = 0;
    }
private:
    size_t len;
    std::vector<Node> tr;
};
