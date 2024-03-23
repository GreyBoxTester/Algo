#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

template<typename T>
class FenwikTree
{
public:
    FenwikTree(i64 n, T val = T())
        : tr(n + 1)
    {
        for (i64 i = 1; i < tr.size(); i++)
        {
            tr[i] = val * (i & -i);
        }
    }

    void upd(i64 i, T val)
    {
        for (; i < tr.size(); i += (i & -i)) { tr[i] += val; }
    }

    T get(i64 r)
    {
        T sum = 0;
        for (; r > 0; r -= (r & -r)) { sum += tr[r]; }
        return sum;
    }

    void set(i64 i, T val)
    {
        upd(i, val - get(i, i));
    }

    T get(i64 l, i64 r)
    {
        return get(r) - get(l - 1);
    }

private:
    std::vector<T> tr;
};
