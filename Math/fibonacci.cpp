#include <cstdint>
#include <utility>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;


constexpr i64 mod = (i64)1e9 + 7;

template<typename T = i64>
class Mat2
{
public:
    Mat2() = default;

    Mat2(T v)
    {
        m[0][0] = m[1][1] = v;
    }

    Mat2(T m00, T m01, T m10, T m11)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[1][0] = m10;
        m[1][1] = m11;
    }

    Mat2 operator*(const Mat2& other) const
    {
        Mat2 r;
        r.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0];
        r.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1];
        r.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0];
        r.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1];
        return r;
    }

    Mat2& operator%=(i64 v)
    {
        m[0][0] %= v;
        m[0][1] %= v;
        m[1][0] %= v;
        m[1][1] %= v;
        return *this;
    }
public:
    T m[2][2] = {};
};

template<typename T>
constexpr std::pair<T, T> operator*(const std::pair<T, T>& a, const Mat2<T>& b)
{
    return {
        a.first * b.m[0][0] + a.second * b.m[1][0],
        a.first * b.m[0][1] + a.second * b.m[1][1]
    };
}

template<typename T>
constexpr std::pair<T, T>& operator%=(std::pair<T, T>& a, T v)
{
    a.first %= v;
    a.second %= v;
    return a;
}

template<typename T>
constexpr std::pair<T, T> operator%(const std::pair<T, T>& a, T v)
{
    std::pair<T, T> r = a;
    r %= v;
    return r;
}

template<typename T>
std::pair<T, T> operator+(const std::pair<T, T>& a, const std::pair<T, T>& b)
{
    return { a.first + b.first, a.second + b.second };
}


template<typename T>
constexpr T powmod(T a, i64 b)
{
    T res = 1;
    while (b)
    {
        if (b & 1) { res = (res * a); res %= mod; }
        a = (a * a);
        a %= mod;
        b >>= 1;
    }
    return res;
}

template<typename T>
constexpr Mat2<T> fibStepMat(T n)
{
    if (n >= 0) { return powmod(Mat2<T>{ 0, 1, 1, 1 }, n); }
    else { return powmod(Mat2<T>{ -1, 1, 1, 0 }, -n); }
}

template<typename T>
constexpr std::pair<T, T> fibNthNum(T n)
{
    return std::pair<T, T>{ 0, 1 } * fibStepMat<T>(n - 1) % mod;
}