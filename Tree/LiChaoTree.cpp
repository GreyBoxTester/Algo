#include <vector>
#include <cmath>
#include <cstdint>

using i64 = int64_t;
using u64 = uint64_t;

struct Line
{
    i64 k = 0, b = 0;
 
    i64 evaluate(i64 x) const
    {
        return k * x + b;
    }
};
 
class LiChaoTree
{
private:
    struct Node
    {
        Line line = { (i64)0, std::numeric_limits<i64>::max() };
        i64 l = -1, r = -1;
    };
public:
    LiChaoTree(i64 lx, i64 rx)
        : tlx(lx), trx(lx + (i64)std::bit_ceil<u64>(rx - lx))
    {}
 
    inline void add(Line line) { add(line, -(i64)tr.empty(), tlx, trx); }
    inline i64 get(i64 x) { return get(x, -(i64)tr.empty(), tlx, trx); }
    void clear() { tr.clear(); }
 
private:
    i64 add(Line line, i64 x, i64 lx, i64 rx)
    {
        if (x == -1) { x = node(); tr[x].line = line; return x; }
        i64 m = (lx + rx) / 2;
        bool cmpMid = tr[x].line.evaluate(m) < line.evaluate(m);
        bool cmpLeft = tr[x].line.evaluate(lx) < line.evaluate(lx);
        if (!cmpMid) { std::swap(tr[x].line, line); }
        if (rx - lx == 1) { return x; }
        if (cmpLeft != cmpMid) { tr[x].l = add(line, tr[x].l, lx, m); }
        else { tr[x].r = add(line, tr[x].r, m, rx); }
        return x;
    }
 
    i64 get(i64 val, i64 x, i64 lx, i64 rx)
    {
        if (x == -1) { return std::numeric_limits<i64>::max(); }
        i64 m = (lx + rx) / 2;
        i64 y = tr[x].line.evaluate(val);
        if (rx - lx == 1) { return y; }
        if (val < m) { return std::min(y, get(val, tr[x].l, lx, m)); } 
        else { return std::min(y, get(val, tr[x].r, m, rx)); }
    }
 
    i64 node()
    {
        tr.emplace_back();
        return tr.size() - 1;
    }
private:
    i64 tlx, trx; 
    std::vector<Node> tr;
};
