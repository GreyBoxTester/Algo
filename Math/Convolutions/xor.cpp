#include <vector>
#include <cstdint>

using i64 = int64_t;

void hadamardTransform(std::vector<i64>& a) 
{
    for (size_t bit = 1; bit < a.size(); bit <<= 1) 
    {
        for (size_t mask = 0; mask < a.size(); mask++)
        {
            if ((mask & bit) == 0)
            {
                i64 u = a[mask], v = a[mask ^ bit];
                a[mask] = u + v;
                a[mask ^ bit] = u - v;
            }
        }
    }
}

void invHadamardTransform(std::vector<i64>& a) 
{
    for (size_t bit = 1; bit < a.size(); bit <<= 1) 
    {
        for (size_t mask = 0; mask < a.size(); mask++)
        {
            if ((mask & bit) == 0)
            {
                i64 x = a[mask], y = a[mask ^ bit];
                a[mask] = (x + y) / 2;
                a[mask ^ bit] = (x - y) / 2;
            }
        }
    }
}

std::vector<i64> xorConvolution(std::vector<i64> a, std::vector<i64> b)
{
    size_t n = std::max(std::bit_ceil(a.size()), std::bit_ceil(b.size()));
    a.resize(n, 0);
    b.resize(n, 0);
    hadamardTransform(a);
    hadamardTransform(b);
    for (size_t i = 0; i < a.size(); i++) { a[i] *= b[i]; }
    invHadamardTransform(a);
    return a;
}
