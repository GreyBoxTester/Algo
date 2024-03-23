#include <cstdint>

constexpr int64_t mod = 1e9 + 7;

constexpr int64_t powmod(int64_t a, int64_t b)
{
	int64_t res = 1;
	while (b)
	{
		if (b & 1) { res = (res * a) % mod; }
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

constexpr int64_t invmod(int64_t a)
{
	return powmod(a, mod - 2);
}

constexpr int64_t divmod(int64_t a, int64_t b)
{
	return (a * invmod(b)) % mod;
}

constexpr int64_t combmod(int64_t n, int64_t k)
{
	int64_t res = 1;
	for (int64_t i = n - k + 1; i <= n; i++)
	{
		res = (res * (i % mod)) % mod;
	}
	for (int64_t i = 2; i <= k; i++)
	{
		res = divmod(res, i % mod);
	}
	return res;
}
