#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

struct Line
{
    i64 k = 0.0, b = 0.0;

    i64 intersection(const Line& other) const
    {
        return (other.b - b) / (k - other.k);
    }

    i64 evaluate(i64 x) const
    {
        return k * x + b;
    }
};

class LowerEnvelope
{
private:
public:
    LowerEnvelope() {}

    //only add in line.k decreasing order
    void add(const Line& line)
    {
        while (!lines.empty())
        {
            auto& [curr, point] = lines.back();
            if (curr.intersection(line) <= point) { lines.pop_back(); }
            else { break; }
        }
        lines.push_back({ line, lines.empty() ? std::numeric_limits<i64>::min() : line.intersection(lines.back().first) });
    }

    i64 query(i64 x)
    {
        auto it = std::upper_bound(lines.begin(), lines.end(), x, [](i64 x, const std::pair<Line, i64>& l) { return l.second > x; });
        --it;
        return it->first.evaluate(x);
    }

private:
    std::vector<std::pair<Line, i64>> lines;
};
