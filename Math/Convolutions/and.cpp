#include <vector>
#include <cstdint>

using i64 = int64_t;

void sumOverSupersets(std::vector<i64>& a, bool inv) 
{
    for (size_t bit = 1; bit < a.size(); bit <<= 1)
    {
        for (size_t mask = 0; mask < a.size(); mask++) 
        {
            if ((mask & bit) == 0) { a[mask] += inv ? -a[mask ^ bit] : a[mask ^ bit]; }
        }
    }
}

std::vector<i64> andConvolution(std::vector<i64> a, std::vector<i64> b) 
{
    size_t n = std::max(std::bit_ceil(a.size()), std::bit_ceil(b.size()));
    a.resize(n, 0);
    b.resize(n, 0);
    sumOverSupersets(a, false);
    sumOverSupersets(b, false);
    for (size_t i = 0; i < a.size(); i++) { a[i] *= b[i]; }
    sumOverSupersets(a, true);
    return a;
}
