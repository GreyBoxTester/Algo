#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <limits>
#include <numeric>
#include <numbers>
#include <cmath>
#include <complex>

namespace rn = std::ranges;
namespace rv = std::ranges::views;

using i64 = int64_t;
using u64 = uint64_t;

template<typename T>
std::vector<std::complex<double>> fft(const std::vector<T>& a, bool inv)
{
    if (a.size() == 1) { return { a[0] }; }
    std::vector<std::complex<double>> a0(a.size() / 2), a1(a.size() / 2);
    for (i64 i = 0; i < a.size() / 2; i++)
    {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }
    auto y0 = fft(a0, inv);
    auto y1 = fft(a1, inv);
    double ang = 2.0 * std::numbers::pi / a.size();
    if (inv) { ang = -ang; }
    std::complex<double> wn = { std::cos(ang), std::sin(ang) };
    std::vector<std::complex<double>> y(a.size());
    std::complex<double> w = 1.0;
    for (i64 i = 0; i < y0.size(); i++, w *= wn)
    {
        y[i] = y0[i] + w * y1[i];
        y[i + y0.size()] = y0[i] - w * y1[i];
    }
    return y;
}

std::vector<i64> mul(const std::vector<i64>& a, const std::vector<i64>& b)
{
    auto at = fft(a, false);
    auto bt = fft(b, false);
    for (int i = 0; i < at.size(); i++)
    {
        at[i] *= bt[i];
    }
    at = fft(at, true);
    std::vector<i64> ans(at.size());
    for (i64 i = 0; i < at.size(); i++)
    {
        ans[i] = (i64)std::round(at[i].real() / a.size());
    }
    return ans;
}

template<typename T>
T nextPow2(T n)
{
    T r = 1;
    while (r < n) { r <<= 1; }
    return r;
}

int main()
{
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);
    i64 n, m; std::cin >> n >> m;
    std::vector<i64> a(n), b(m);
    i64 maxA = 0, maxB = 0;
    for (auto& ai : a) { std::cin >> ai; maxA = std::max(maxA, ai); }
    for (auto& bi : b) { std::cin >> bi; maxB = std::max(maxB, bi); }
    i64 l = nextPow2(maxA + maxB + 1);
    std::vector<i64> p1(l), p2(l);
    for (auto& ai : a) { p1[ai]++; }
    for (auto& bi : b) { p2[bi]++; }

    auto c = mul(p1, p2);
    for (i64 i = 0; i < l; i++)
    {
        if (c[i] == 0) { continue; }
        std::cout << i << ' ' << c[i] << '\n';
    }
}
