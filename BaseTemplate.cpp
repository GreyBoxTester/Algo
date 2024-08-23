#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <limits>
#include <numeric>
#include <cstdint>
#include <cmath>
#include <random>
#include <map>
#include <set>
#include <bit>
#include <queue>

namespace rn = std::ranges;
namespace rv = std::ranges::views;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

void alg()
{
    i64 n = 0; std::cin >> n;
    std::vector<i64> a(n);
    for (auto& ai : a) { std::cin >> ai; }

}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 t = 1;
    std::cin >> t;
    while (t--) { alg(); }
}