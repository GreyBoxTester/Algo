#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <limits>
#include <numeric>
#include <bit>
#include <map>
#include <set>
#include <cmath>


using i64 = int64_t;
using u64 = uint64_t;

constexpr u64 log2Floor(u64 n) { return (u64)63 - std::countl_zero<u64>(n); }
constexpr u64 log2Ceil(u64 n) { return (u64)64 - std::countl_zero<u64>(n - 1); }

constexpr u64 maxSize = (u64)16;
constexpr u64 logSize = log2Ceil(maxSize) + 1;

u64 st[logSize][maxSize] = {};

void calcST(const std::vector<u64>& a)
{
    for (u64 i = 0; i < a.size(); i++)
    {
        st[0][i] = a[i];
    }

    for (u64 p = 1; p < logSize; p++)
    {
        for (u64 l = 0; l + ((u64)1 << p) <= a.size(); l++)
        {
            st[p][l] = std::min(st[p - 1][l], st[p - 1][l + ((u64)1 << (p - 1))]);
        }
    }
}

u64 getST(u64 l, u64 r)
{
    u64 p = log2Floor(r - l);
    return std::min(st[p][l], st[p][r - ((u64)1 << p)]);
}
