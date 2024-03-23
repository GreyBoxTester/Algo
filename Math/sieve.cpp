#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;

std::vector<i64> mind;
std::vector<i64> primes;

void calc(i64 n)
{
    mind.resize(n + 1);
    for (i64 k = 2; k <= n; k++)
    {
        if (mind[k] == 0) {
            mind[k] = k;
            primes.push_back(k);
        }
        for (i64 x : primes) {
            if (x > mind[k] || x * k > n) { break; }
            mind[k * x] = x;
        }
    }
}