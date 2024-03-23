#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <limits>
#include <numeric>
#include <numbers>
#include <queue>
#include <cmath>
#include <bit>
#include <set>

namespace rn = std::ranges;
namespace rv = std::ranges::views;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

template<typename T>
struct Rect2D
{
    T left, bottom, right, top;

    bool contains(const std::pair<T, T>& p) const
    {
        return p.first >= left && p.first < right && p.second >= bottom && p.second < top;
    }

    bool contains(const Rect2D& p) const
    {
        return left <= p.left && right >= p.right && bottom <= p.bottom && top >= p.top;
    }

    bool intersects(const Rect2D& p) const
    {
        return right > p.left && left < p.right && top > p.bottom && bottom < p.top;
    }

    void getQuadrants(Rect2D* arr) const
    {
        T mx = (left + right) / 2;
        T my = (bottom + top) / 2;

        arr[0].left = mx;
        arr[0].bottom = my;
        arr[0].right = right;
        arr[0].top = top;

        arr[1].left = left;
        arr[1].bottom = my;
        arr[1].right = mx;
        arr[1].top = top;

        arr[2].left = left;
        arr[2].bottom = bottom;
        arr[2].right = mx;
        arr[2].top = my;

        arr[3].left = mx;
        arr[3].bottom = bottom;
        arr[3].right = right;
        arr[3].top = my;
    }
};

template<typename T, T defVal>
class SegTree2D
{
public:
    struct Node
    {
        T min = defVal;
    };
public:
    SegTree2D(size_t sx, size_t sy)
        : sz(std::bit_ceil(std::max(sx, sy))), tr(sz* sz * 2 - 1)
    {}

    inline void set(const std::pair<size_t, size_t>& p, T val) { set(p, val, 0, { 0, 0, sz, sz }); }
    inline T get(const Rect2D<size_t>& rect) { return get(rect, 0, { 0, 0, sz, sz }).min; }

private:
    void set(const std::pair<size_t, size_t>& p, T val, size_t x, const Rect2D<size_t>& q)
    {
        if (q.right - q.left == 1) { tr[x].min = val; return; }
        Rect2D<size_t> quads[4] = {};
        q.getQuadrants(quads);
        for (size_t i = 0; i < 4; i++)
        {
            if (quads[i].contains(p)) { set(p, val, x * 4 + 1 + i, quads[i]); break; }
        }
        tr[x] = op(tr[x * 4 + 1], tr[x * 4 + 2], tr[x * 4 + 3], tr[x * 4 + 4]);
    }

    Node get(const Rect2D<size_t>& rect, size_t x, const Rect2D<size_t>& q)
    {
        if (rect.contains(q)) { return tr[x]; }
        if (!rect.intersects(q)) { return { defVal }; }
        Rect2D<size_t> quads[4] = {};
        q.getQuadrants(quads);
        return op(
            get(rect, x * 4 + 1, quads[0]),
            get(rect, x * 4 + 2, quads[1]),
            get(rect, x * 4 + 3, quads[2]),
            get(rect, x * 4 + 4, quads[3])
        );
    }

    Node op(const Node& a, const Node& b, const Node& c, const Node& d)
    {
        return { std::min<T>({ a.min, b.min, c.min, d.min }) };
    }

private:
    size_t sz;
    std::vector<Node> tr;
};


int main()
{
    i64 n = 0; std::cin >> n;
    SegTree2D<i64, std::numeric_limits<i64>::max()> tr(4, 4);
}

