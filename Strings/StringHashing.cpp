#pragma once
#include <cstdint>
#include <vector>
#include <string>

using i64 = int64_t;
using u64 = uint64_t;

constexpr u64 hp = 31; //a-z

std::vector<u64> p;
void calcPowers()
{
	u64 val = 1;
	for (auto& vi : p)
	{
		vi = val;
		val *= hp;
	}
}

std::vector<u64> ph;
void hashPref(const std::string& s)
{
	ph[0] = (s[0] - 'a' + 1);
	for (int i = 1; i < s.size(); i++)
	{
		ph[i] = ph[i - 1] + p[i] * (s[i] - 'a' + 1);
	}
}

std::vector<u64> sh;
void hashSuff(const std::string& s)
{
	sh[s.size() - 1] = (s[s.size() - 1] - 'a' + 1);
	for (int i = s.size() - 2; i >= 0; i--)
	{
		sh[i] = sh[i + 1] + p[s.size() - 1 - i] * (s[i] - 'a' + 1);
	}
}

u64 substrHash(size_t b, size_t e)
{
	if (e == 0) { return 0; }
	e--;
	u64 hash = ph[e];
	if (b) { hash -= ph[b - 1]; }
	return hash;
}

u64 substrRevHash(size_t b, size_t e)
{
	u64 hash = sh[b];
	if (e != sh.size()) { hash -= sh[e]; }
	return hash;
}

bool isPal(size_t b, size_t e)
{
	u64 phash = substrHash(b, e);
	u64 shash = substrRevHash(b, e);
	e--;
	size_t d1 = b;
	size_t d2 = sh.size() - 1 - e;
	if (d1 < d2) { phash *= p[d2 - d1]; }
	else { shash *= p[d1 - d2]; }
	return phash == shash;
}

int findMaxPalOdd(int i)
{
	int l = 0, r = std::min<int>(ph.size() - 1 - i, i);
	while (r - l > 1)
	{
		int m = (l + r) / 2;
		if (isPal(i - m, i + m + 1)) { l = m; }
		else { r = m; }
	}
	if (isPal(i - r, i + r + 1)) { l = r; }
	return l;
}

int findMaxPalEven(int i)
{
	int l = 0, r = std::min<int>(ph.size() - 2 - i, i);
	while (r - l > 1)
	{
		int m = (l + r) / 2;
		if (isPal(i - m, i + m + 2)) { l = m; }
		else { r = m; }
	}
	if (isPal(i - r, i + r + 2)) { l = r; }
	return l;
}

//========================

constexpr u64 mod = 1e9 + 7;
std::vector<u64> pow5, pow7;

std::vector<u64> calcPower(u64 p, u64 size)
{
	std::vector<u64> powp(size);
	powp[0] = 1;
	for (u64 i = 1; i < powp.size(); i++)
	{
		powp[i] = (powp[i - 1] * p) % mod;
	}
	return powp;
}

u64 hash(const std::string& s, u64 p)
{
	u64 h = 0, m = 1;
	for (char c : s)
	{
		h += ((c - 'a' + 1) * m) % mod;
		h %= mod;
		m *= p;
		m %= mod;
	}
	return h;
}

struct Hash
{
	Hash(const std::string& s)
		: h5(hash(s, 5)), h7(hash(s, 7))
	{}
	void change(char c1, char c2, u64 i)
	{
		h5 = (h5 + mod - (((u64)c1 - 'a' + 1) * pow5[i]) % mod) % mod;
		h5 = (h5 + (((u64)c2 - 'a' + 1) * pow5[i]) % mod) % mod;

		h7 = (h7 + mod - (((u64)c1 - 'a' + 1) * pow7[i]) % mod) % mod;
		h7 = (h7 + (((u64)c2 - 'a' + 1) * pow7[i]) % mod) % mod;
	}
	bool operator<(const Hash& other) const
	{
		if (h5 == other.h5) { return h7 < other.h7; }
		return h5 < other.h5;
	}
	u64 h5, h7;
};

//=======================

constexpr u64 mod = 1e9 + 7;
std::vector<u64> pow31;

std::vector<u64> calcPowers(u64 p, u64 size)
{
	std::vector<u64> powp(size);
	powp[0] = 1;
	for (u64 i = 1; i < powp.size(); i++)
	{
		powp[i] = (powp[i - 1] * p) % mod;
	}
	return powp;
}

u64 hash(const std::string& s, u64 p)
{
	u64 h = 0, m = 1;
	for (char c : s)
	{
		h += (((u64)c - 'a' + 1) * m) % mod;
		h %= mod;
		m *= p;
		m %= mod;
	}
	return h;
}

std::vector<u64> prefHash(const std::string& s, u64 p)
{
	std::vector<u64> ph(s.size());
	ph[0] = ((u64)s[0] - 'a' + 1);
	for (u64 i = 1; i < s.size(); i++)
	{
		ph[i] = (ph[i - 1] + (pow31[i] * ((u64)s[i] - 'a' + 1)) % mod) % mod;
	}
	return ph;
}

u64 substrHash(const std::vector<u64>& ph, int l, int w, int maxPow)
{
	u64 h = ph[l + w - 1];
	if (l) { h = (h + mod - ph[l - 1]) % mod; }
	h = (h * pow31[maxPow - l]) % mod;
	return h;
}