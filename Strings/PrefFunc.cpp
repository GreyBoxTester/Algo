#include <vector>
#include <string>

using i64 = int64_t;

std::vector<i64> prefFunc(const std::string& s)
{
    std::vector<i64> p(s.size());
    for (i64 i = 1; i < s.size(); i++)
    {
        i64 cur = p[i - 1];
        while (cur > 0 && s[cur] != s[i]) { cur = p[cur - 1]; }
        if (s[cur] == s[i]) { p[i] = cur + 1; }
    }
    return p;
}
