#include <vector>
#include <string>

using i64 = int64_t;

std::vector<i64> suffixArray(const std::string& s)
{
    constexpr i64 alph = 256;
    i64 n = s.size() + 1;
    std::vector<i64> p(n), c(n), cnt(std::max(n, alph));
    for (i64 i = 0; i < n; i++) { cnt[s[i]]++; }
    for (i64 i = 1; i < std::max(n, alph); i++) { cnt[i] += cnt[i - 1]; }
    for (i64 i = 0; i < n; i++) { p[--cnt[s[i]]] = i; }

    c[p[0]] = 0;
    i64 cls = 1;
    for (i64 i = 1; i < n; i++)
    {
        if (s[p[i]] != s[p[i - 1]]) { cls++; }
        c[p[i]] = cls - 1;
    }

    std::vector<i64> pn(n), cn(std::max(n, alph));
    for (i64 k = 0; ((i64)1 << k) < n; k++)
    {
        for (i64 i = 0; i < n; i++) { pn[i] = (p[i] - ((i64)1 << k) + n) % n; }
        std::fill(cnt.begin(), cnt.end(), 0);
        for (i64 i = 0; i < n; i++) { cnt[c[pn[i]]]++; }
        for (i64 i = 1; i < n; i++) { cnt[i] += cnt[i - 1]; }
        for (i64 i = n - 1; i >= 0; i--) { p[--cnt[c[pn[i]]]] = pn[i]; }

        cn[p[0]] = 0;
        cls = 1;
        for (i64 i = 1; i < n; i++)
        {
            if (c[p[i]] != c[p[i - 1]] || c[p[i] + ((i64)1 << k) % n] != c[p[i - 1] + ((i64)1 << k) % n]) { cls++; }
            cn[p[i]] = cls - 1;
        }

        std::swap(c, cn);
    }
    p.erase(p.begin());
    return p;
}

std::vector<i64> calcLcp(const std::string& s, const std::vector<i64>& sa)
{
    i64 n = s.size();
    std::vector<i64> pos(n);
    for (i64 i = 0; i < n; i++) { pos[sa[i]] = i; }

    std::vector<i64> lcp(n - 1);
    i64 k = 0;
    for (i64 i = 0; i < n; i++)
    {
        if (pos[i] == n - 1) { k = 0; continue; }
        i64 j = sa[pos[i] + 1];
        while (std::max(i, j) + k < n && s[i + k] == s[j + k]) { k++; }
        lcp[pos[i]] = k;
        if (k) { k--; }
    }
    return lcp;
}
