#include <vector>
#include <string>

using i64 = int64_t;

std::vector<i64> zFunc(const std::string& s)
{
    std::vector<i64> z(s.size());
    i64 l = 0, r = 0;
    for (i64 i = 1; i < s.size(); i++)
    {
        if (i <= r) { z[i] = std::min(z[i - l], r - i + 1); }
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) { z[i]++; }
        i64 nr = i + z[i] - 1;
        if (nr > r) { l = i; r = nr; }
    }
    return z;
}
